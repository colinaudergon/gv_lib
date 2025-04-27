#include "file_handler.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include <stdio.h>

directory_t *file_handler_create_directory()
{
    directory_t *dir = malloc(sizeof(directory_t));
    if (dir == NULL)
    {
        printf("Failed to allocate memory for dir");
        return NULL;
    }

    dir->directory = malloc(sizeof(DIR));
    if (dir->directory == NULL)
    {

        printf("Failed to allocate memory for directory variable");
        free(dir);
        return NULL;
    }

    memset(dir->files_info, 0, sizeof(dir->files_info));
    dir->num_files = 0;

    return dir;
}

int file_handler_destroy_directory(directory_t **dir)
{
    if (dir == NULL || *dir == NULL || (*dir)->directory == NULL)
    {
        return -EINVAL; // Invalid argument
    }

    // Free the dynamically allocated directory structure
    free((*dir)->directory);
    (*dir)->directory = NULL;

    // Free the directory_t structure itself
    free(*dir);
    *dir = NULL; // Set the caller's pointer to NULL to avoid dangling pointers

    return 0; // Success
}

int file_handler_ls_dir_content(const char *dir_path, directory_t *dest_directory)
{
    if (dir_path == NULL || dest_directory == NULL)
    {
        return -EINVAL;
    }

    FRESULT res = f_opendir(dest_directory->directory, dir_path);
    if (res != FR_OK)
    {
        printf("Failed to open directory: err: (%u)\n", res);
        return -1;
    }

    size_t nfile = 0;
    FILINFO file_info_tmp;
    while (nfile < NUM_FILE_MAX_IN_DIR)
    {
        res = f_readdir(dest_directory->directory, &file_info_tmp);
        if (res != FR_OK || file_info_tmp.fname[0] == 0)
        {
            break; /* Error or end of dir */
        }
        if (!(file_info_tmp.fattrib & AM_DIR))
        {
            printf("Path: %s\tName:%s\t size:%d\n", dir_path, file_info_tmp.fname, file_info_tmp.fsize);

            memcpy(&dest_directory->files_info[dest_directory->num_files], &file_info_tmp, sizeof(file_info_tmp));
            dest_directory->num_files++;
        }
    }
    f_closedir(dest_directory->directory);

    return res;
}

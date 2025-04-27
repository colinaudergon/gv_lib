#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_
#include "pico/stdlib.h"
#include "f_util.h"
#include "ff.h"

#define NUM_FILE_MAX_IN_DIR 256
typedef struct 
{
    /* data */
    FILINFO files_info;
}dir_content_t;

typedef struct 
{
    /* data */
    FILINFO files_info[NUM_FILE_MAX_IN_DIR];
    DIR *directory;
    size_t num_files;
}directory_t;


directory_t *file_handler_create_directory();
int file_handler_destroy_directory(directory_t **dir);
int file_handler_ls_dir_content(const char *dir_path, directory_t *dest_directory);

#endif /*_FILE_HANDLER_H_*/
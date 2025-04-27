#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "pico/stdlib.h"
#include <stdlib.h>

#include "wav_reader.h"
#include "file_handler.h"
#include "sd_card.h"
#include "hw_config.h"
// static FRESULT

static uint16_t to_little_endian_16(uint16_t value)
{
    return (value >> 8) | (value << 8);
}

static uint32_t to_little_endian_32(uint32_t value)
{
    return ((value >> 24) & 0xFF) |
           ((value >> 8) & 0xFF00) |
           ((value << 8) & 0xFF0000) |
           ((value << 24) & 0xFF000000);
}

// static uint16_t read_2_bytes_from_start(FILE *file, uint32_t offset)

#if 0
static uint16_t read_2_bytes_from_start(FILE *file, uint32_t offset)
{
    if (file == NULL)
    {
        printf("Invalid argument");
        return 0;
    }

    fseek(file, offset, SEEK_SET);
    uint16_t val;
    fread(&val, 2, 1, file);
    return val;
}

static uint16_t read_2_bytes_from_start(FILE *file, uint32_t offset)
{
        if (file == NULL)
    {
        printf("Invalid argument");
        return 0;
    }

    f_lseek(file, offset);
    uint16_t val;
    UINT br;
    f_read(file, &val, 2, &br);

    if (br < 2)
    {
            printf("End of file\n");
        }
        return val;
    }
#endif

static uint32_t read_4_bytes_from_start(FIL *file, uint32_t offset)
{
    if (file == NULL)
    {
        return -EINVAL;
    }

    f_lseek(file, offset);
    uint32_t val;
    UINT br;
    f_read(file, &val, 4, &br);
    if (br < 4)
    {
        printf("End of file\n");
    }
    return val;
}

static int read_4_bytes_ptr_from_start(FIL *file, uint32_t offset, char *data)
{
    if (file == NULL || data == NULL)
    {
        return -EINVAL; // Invalid argument
    }

    // Seek to the specified offset
    if (f_lseek(file, offset) != FR_OK)
    {
        printf("Error seeking to offset %u\n", offset);
        return -EIO; // Input/output error
    }

    UINT br; // Bytes read
    if (f_read(file, data, 4, &br) != FR_OK || br < 4)
    {
        printf("Error reading 4 bytes or end of file reached\n");
        return -EIO; // Input/output error
    }

    return 0; // Success
}
int wav_file_reader_init(wav_file_reader_t *reader, const char *filepath)
{
    if (reader == NULL || filepath == NULL)
    {
        fprintf(stderr, "Invalid argument: one or more argument NULL\n");
        return -EINVAL;
    }

    reader->wav_header = malloc(sizeof(wave_file_header_t));
    if (reader->wav_header == NULL)
    {
        printf("Failed to allocate memory for weav_header struct\n");
        return -ENOMEM;
    }

    reader->wav_header = malloc(sizeof(FATFS));
    if (reader->wav_header == NULL)
    {
        printf("Failed to allocate memory for FATFS struct\n");
        return -ENOMEM;
    }

    reader->file = malloc(sizeof(FIL));
    if (reader->file == NULL)
    {
        printf("Failed to allocate memory for file structure\n");
        return -ENOMEM; // Memory allocation error
    }

    memset(reader->filepath, 0, MAX_PATH_LENGTH);
    memcpy(reader->filepath, filepath, strlen(filepath));
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    // if (!sd_init_driver())
    // {
    //     printf("ERROR: Could not initialize SD card\r\n");
    //     return -1;
    // }

    // FRESULT err = f_mount(reader->fs, "0:", 1);
    if (fr != FR_OK)
    // if (err != FR_OK)
    {
        // printf("ERROR: Could not mount filesystem. FATFS fields: fs_type=%d, id=%d\r\n",
        //        reader->fs->fs_type, reader->fs->id);
        return -1;
    }

    return 0;
}

int wav_file_reader_open(wav_file_reader_t *reader)
{
    if (reader == NULL)
    {
        fprintf(stderr, "Reader is NULL\n");
        return -EINVAL;
    }

    FRESULT err = f_open(reader->file, reader->filepath, FA_READ);
    if (err != FR_OK)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return -errno;
    }
    return 0;
}

int wav_file_reader_close(wav_file_reader_t *reader)
{
    if (reader == NULL)
    {
        fprintf(stderr, "Reader is NULL\n");
        return -EINVAL;
    }

    if (reader->file == NULL)
    {
        fprintf(stderr, "File is not open\n");
        return -EINVAL;
    }

    if (reader->file != NULL)
    {
        f_close(reader->file);
        reader->file = NULL;
    }
    memset(reader->filepath, 0, MAX_PATH_LENGTH);

    free(reader->wav_header);
    reader->wav_header = NULL;

    free(reader->fs);
    reader->fs = NULL;

    return 0;
}



int wav_reader_read_wav_header(wav_file_reader_t *reader)
{
    if (reader == NULL)
    {
        fprintf(stderr, "Reader is NULL\n");
        return -EINVAL;
    }

    if (reader->file == NULL)
    {
        fprintf(stderr, "File is not open\n");
        return -EINVAL;
    }

    UINT br;
    FRESULT err = f_read(reader->file, reader->wav_header, 44, &br);
    if (err != FR_OK)
    {
        printf("Failed to read file");
        return -1;
    }
    return 0;
}



int wav_file_reader_read_data_init(wav_file_reader_t *reader)
{

    if (reader == NULL)
    {
        printf("Invalid argument: reader is null");
        return -EINVAL;
    }

    if (reader->file == NULL)
    {
        fprintf(stderr, "File is not open\n");
        return -EINVAL;
    }

    FRESULT err = f_lseek(reader->file, WAV_FILE_DATA_BASE_ADDR);
    if (err != FR_OK)
    {
        printf("Failed to read file");
        return -1;
    }

    return 0;
}

int wav_file_reader_read_data_chunk(wav_file_reader_t *reader, void *data, size_t size)
{
    if (reader == NULL)
    {
        fprintf(stderr, "Invalid argument: reader is null\n");
        return -EINVAL;
    }

    if (reader->file == NULL)
    {
        fprintf(stderr, "File is not open\n");
        return -EINVAL;
    }

    if (data == NULL)
    {
        fprintf(stderr, "Invalid data argument\n");
        return -EINVAL;
    }

    // Determine the size of each sample in bytes
    int read_size = reader->wav_header->bitsPerSample / 8; // 1/2/4
    if (read_size <= 0)
    {
        fprintf(stderr, "Invalid bits_per_sample value: %d\n", reader->wav_header->bitsPerSample);
        return -EINVAL;
    }

    printf("read_size: %d\n", read_size);

#if 0
    // Read the data
    size_t elements_read = fread(data, read_size, size, reader->file);
    if (elements_read != size)
    {
        if (feof(reader->file))
        {
            fprintf(stderr, "End of file reached while reading data chunk\n");
        }
        else if (ferror(reader->file))
        {
            fprintf(stderr, "Error reading file: %s\n", strerror(errno));
        }
        return -EIO; // Input/output error
    }

    // Handle endianness if necessary (for multi-byte samples)
    // if (read_size > 1)
    // {
    //     uint16_t *data16 = (uint16_t *)data;
    //     for (size_t i = 0; i < elements_read; i++)
    //     {
    //         data16[i] = to_little_endian_16(data16[i]);
    //     }
    // }
#endif
    return 0; // Success
}

int wav_file_reader_get_left_channel_data(void *data_out, size_t size_out, void *data_in, size_t size_in)
{
    if (data_in == NULL || data_out == NULL)
    {
        return -EINVAL;
    }

    uint16_t *input = (uint16_t *)data_in; // Assuming 16-bit samples
    uint16_t *output = (uint16_t *)data_out;

    size_t left_channel_count = 0;

    for (size_t i = 0; i < size_in; i += 2) // Process every second sample (left channel)
    {
        if (left_channel_count >= size_out) // Ensure we don't exceed the output buffer
        {
            return left_channel_count;
        }

        output[left_channel_count] = input[i]; // Copy left channel sample
        left_channel_count++;
    }

    return left_channel_count; // Return the number of left channel samples written
}

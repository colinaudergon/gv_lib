#include <stdio.h>
#include "pico/stdlib.h"

#include "wav_reader.h"
#include "file_handler.h"
#include "hw_config.h"
#include "ff.h"
#include <errno.h>

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    printf("Helllooooo\n");

    wav_file_reader_t reader;
    char *path = "/0.wav";

    int err;
    err = wav_file_reader_init(&reader, path);
    if(err <0)
    {
        printf("Failed to init the wav file reader: %d\n",err);
    }
    directory_t *dir = file_handler_create_directory();
    if (dir == NULL)
    {
        printf("Failed to create directory\n");
        return -1;
    }

    
    file_handler_ls_dir_content("/",dir);
    
    // Destroy the directory and set the pointer to NULL
    if (file_handler_destroy_directory(&dir) != 0)
    {
        printf("Failed to destroy directory\n");
    }

    err = wav_file_reader_open(&reader);
    if(err <0)
    {
        printf("Failed to open the wav file reader: %d\n",err);
    }
    err = wav_reader_read_wav_header(&reader);
    if(err <0)
    {
        printf("Failed to read the wav file header: %d\n",err);
    }

    printf("Header content:\n");
    printf("reader.wav_header->blockID: %c %c %c %c\n",
           reader.wav_header->blockID[0], reader.wav_header->blockID[1],
           reader.wav_header->blockID[2], reader.wav_header->blockID[3]);
    printf("reader.wav_header->totalSize: %u\n", reader.wav_header->totalSize);
    printf("reader.wav_header->typeHeader: %c %c %c %c\n",
           reader.wav_header->typeHeader[0], reader.wav_header->typeHeader[1],
           reader.wav_header->typeHeader[2], reader.wav_header->typeHeader[3]);
    printf("reader.wav_header->fmt: %c %c %c %c\n",
           reader.wav_header->fmt[0], reader.wav_header->fmt[1],
           reader.wav_header->fmt[2], reader.wav_header->fmt[3]);
    printf("reader.wav_header->typeOfFormat: %u\n", reader.wav_header->typeOfFormat);
    printf("reader.wav_header->numbeOfChannel: %u\n", reader.wav_header->numbeOfChannel);
    printf("reader.wav_header->sampleRate: %u\n", reader.wav_header->sampleRate);
    printf("reader.wav_header->byteRate: %u\n", reader.wav_header->byteRate);
    printf("reader.wav_header->blockAlign: %u\n", reader.wav_header->blockAlign);
    printf("reader.wav_header->bitsPerSample: %u\n", reader.wav_header->bitsPerSample);
    printf("reader.wav_header->dataHeader: %c %c %c %c\n",
           reader.wav_header->dataHeader[0], reader.wav_header->dataHeader[1],
           reader.wav_header->dataHeader[2], reader.wav_header->dataHeader[3]);
    printf("reader.wav_header->dataSize: %u\n", reader.wav_header->dataSize);

    while (1)
    {
        printf("hello\n");
        sleep_ms(1000);
    }
}


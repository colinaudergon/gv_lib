

#ifndef _WAV_READER_H_
#define _WAV_READER_H_

#include "pico/stdlib.h"
#include "f_util.h"
#include "ff.h"
#include "file_handler.h"

#define MAX_PATH_LENGTH 256

typedef struct
{
    char blockID[4];         // 4 bytes
    uint32_t totalSize;      // 4 bytes
    char typeHeader[4];      // 4 bytes
    char fmt[4];             // 4 bytes
    uint32_t headerLen;      // 4bytes
    uint16_t typeOfFormat;   // 2 bytes
    uint16_t numbeOfChannel; // 2bytes
    uint32_t sampleRate;     // 4 bytes
    uint32_t byteRate;       // 4 bytes
    uint16_t blockAlign;     // 2 bytes
    uint16_t bitsPerSample;  // 2 bytes
    char dataHeader[4];      // 4 bytes
    uint32_t dataSize;       // 4 bytes
} wave_file_header_t;        // 44 bytes total


typedef struct __wav_file_reader
{
    FIL *file;
    // wav_header_t wav_header;
    wave_file_header_t  *wav_header;
    FATFS *fs;
    char filepath[MAX_PATH_LENGTH];
} wav_file_reader_t;




int wav_file_reader_init(wav_file_reader_t *reader, const char *filepath);
int wav_file_reader_open(wav_file_reader_t *reader);
int wav_file_reader_close(wav_file_reader_t *reader);

int wav_reader_read_wav_header(wav_file_reader_t *reader);

int wav_file_reader_read_data_init(wav_file_reader_t *reader);
int wav_file_reader_read_data_chunk(wav_file_reader_t *reader, void *data, size_t size);

// int wav_file_reader_get_left_channel_data(void *data_out, size_t size_out, void *data_in, size_t size_in);




#endif /*_WAV_READER_H_*/
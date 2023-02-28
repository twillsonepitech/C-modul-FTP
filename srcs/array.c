/**
 * @file array.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Manage string to word array, free, ...
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include "define.h"

int32_t endswith(const uint8_t *str, const uint8_t *suffix)
{
    uint64_t str_len = strlen((const char *)str);
    uint64_t suffix_len = strlen((const char *)suffix);

    return (str_len >= suffix_len)
        && (!memcmp(str + str_len - suffix_len, suffix, suffix_len));
}

uint8_t *lineptr_to_upper_lineptr(uint8_t *lineptr)
{
    uint64_t index_per_iteration;

    index_per_iteration = INIT_INTEGER;
    while (index_per_iteration < strlen((const char *)lineptr)) {
        lineptr[index_per_iteration] = toupper(lineptr[index_per_iteration]);
        index_per_iteration++;
    }
    return lineptr;
}

uint64_t length_dbl_array_pointer(const uint8_t **dbl_lineptr)
{
    uint64_t dbl_lineptr_length;

    dbl_lineptr_length = INIT_INTEGER;
    while (dbl_lineptr[dbl_lineptr_length] != NULL) {
        dbl_lineptr_length++;
    }
    return dbl_lineptr_length;
}

void print_content_dbl_array_pointer(const int fd, const uint8_t **dbl_lineptr)
{
    int32_t index_per_iteration;

    index_per_iteration = INIT_INTEGER;
    while (dbl_lineptr[index_per_iteration] != NULL) {
        dprintf(fd, "%s\n", dbl_lineptr[index_per_iteration]);
        index_per_iteration++;
    }
}

uint8_t **lineptr_to_dbl_lineptr(uint8_t *lineptr, const uint8_t *delim)
{
    int32_t index_per_iteration;
    uint8_t **dbl_lineptr;
    uint8_t *token_lineptr_delim;

    dbl_lineptr = INIT_POINTER;
    dbl_lineptr = (uint8_t **)malloc(sizeof(uint8_t *) * (strlen((const char *)lineptr) + 1));
    if (NULL == dbl_lineptr) {
        LOG_ERROR("malloc() function: FAILURE.");
        return NULL;
    }
    index_per_iteration = INIT_INTEGER;
    token_lineptr_delim = (uint8_t *)strtok((char *)lineptr, (const char *)delim);
    while (token_lineptr_delim != NULL) {
        dbl_lineptr[index_per_iteration] = (uint8_t *)strdup((const char *)token_lineptr_delim);
        token_lineptr_delim = (uint8_t *)strtok(NULL, (const char *)delim);
        index_per_iteration++;
    }
    dbl_lineptr[index_per_iteration] = INIT_POINTER;
    return dbl_lineptr;
}

void free_dbl_array_pointer(uint8_t **dbl_ptr)
{
    int32_t index_per_iteration;

    index_per_iteration = INIT_INTEGER;
    while (dbl_ptr[index_per_iteration] != NULL) {
        free(dbl_ptr[index_per_iteration]);
        index_per_iteration++;
    }
    free(dbl_ptr);
}

uint8_t xstrtoul(uint64_t *ulong, const uint8_t *lineptr, int32_t base)
{
    uint8_t *endptr;

    *ulong = strtoul((const char *)lineptr, (char **)&endptr, base);
    if ((errno == ERANGE && *ulong == ULONG_MAX) || (errno != ZERO && *ulong == ZERO)) {
        LOG_ERROR("strtoul() function: FAILURE.");
        return EXIT_FAILURE;
    }
    if (endptr == lineptr) {
        LOG_ERROR("strtoul() function: No digits were found.");
        return EXIT_FAILURE;
    }
    if (*endptr != '\0') {
        LOG_ERROR("strtoul() function: Characters were found.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

uint64_t count_number_c_in_lineptr(const uint8_t *lineptr, const uint8_t c)
{
    int32_t index_per_iteration;
    uint64_t counter;

    counter = INIT_INTEGER;
    index_per_iteration = INIT_INTEGER;
    while (lineptr[index_per_iteration] != '\0') {
        if (lineptr[index_per_iteration] == c) {
            counter++;
        }
        index_per_iteration++;
    }
    return counter;
}

uint8_t *make_message(const char *__restrict __fmt, ...)
{
    int64_t size = 0;
    uint8_t *fmt = INIT_POINTER;
    va_list list;

    va_start(list, __fmt);
    size = vsnprintf((char *__restrict)fmt, size, __fmt, list);
    if (size < 0) {
        LOG_ERROR("vsnprintf() function: FAILURE.");
        return NULL;
    }
    va_end(list);
    fmt = (uint8_t *)malloc(++size);
    if (NULL == fmt) {
        LOG_ERROR("malloc() function: FAILURE.");
        return NULL;
    }
    va_start(list, __fmt);
    size = vsnprintf((char *__restrict)fmt, size, __fmt, list);
    if (size < 0) {
        LOG_ERROR("vsnprintf() function: FAILURE.");
        free(fmt);
        return NULL;
    }
    va_end(list);
    return fmt;
}

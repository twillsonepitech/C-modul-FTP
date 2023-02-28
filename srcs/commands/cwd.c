/**
 * @file cwd.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief CWD FTP command.
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"
#include "define.h"
#include "functions.h"

uint8_t cwd(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    uint8_t *new_path;

    if (TWO != dbl_lineptr_length) {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, lineptr, NO_SUCH_FILE);
        return EXIT_FAILURE_FTP;
    }
    free(client->path);
    new_path = xgetcwd(lineptr);
    if (NULL == new_path) {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, lineptr, NO_SUCH_FILE);
        return EXIT_FAILURE_FTP;
    }
    client->path = (uint8_t *)strdup((const char *)new_path);
    WRITE_CODE(client->socket.fd, FTP_CODE_250, NULL);
    free(new_path);
    return EXIT_SUCCESS;
}

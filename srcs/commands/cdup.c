/**
 * @file cdup.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief CDUP FTP command.
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "struct.h"
#include "define.h"
#include "functions.h"

uint8_t cdup(const uint64_t dbl_lineptr_length, __attribute__((unused)) const uint8_t *lineptr, struct clients_s *client)
{
    uint8_t *new_path;

    if (ONE != dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    free(client->path);
    new_path = xgetcwd((const uint8_t *)"..");
    if (NULL == new_path)
    {
        return EXIT_FAILURE;
    }
    client->path = (uint8_t *)strdup((const char *)new_path);
    WRITE_CODE(client->socket.fd, FTP_CODE_250, NULL);
    free(new_path);
    return EXIT_SUCCESS;    
}

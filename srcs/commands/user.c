/**
 * @file user.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief USER FTP command.
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "struct.h"

uint8_t user(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    if (TWO != dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    if (client->name != NULL)
    {
        free(client->name);
    }
    client->name = (uint8_t *)strdup((const char *)lineptr);
    WRITE_CODE(client->socket.fd, FTP_CODE_331, NULL);
    return EXIT_SUCCESS;
}

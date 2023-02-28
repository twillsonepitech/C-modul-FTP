/**
 * @file quit.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief QUIT FTP command.
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include "define.h"
#include "struct.h"

uint8_t quit(const uint64_t dbl_lineptr_length, __attribute__((unused)) const uint8_t *lineptr, struct clients_s *client)
{
    if (ONE != dbl_lineptr_length) {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    client->quitted = true;
    WRITE_CODE(client->socket.fd, FTP_CODE_221, NULL);
    return EXIT_SUCCESS;
}

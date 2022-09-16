/**
 * @file pass.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief PASS FTP command.
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "define.h"

uint8_t pass(const uint64_t dbl_lineptr_length, __attribute__((unused)) const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;

    if (dbl_lineptr_length >= THREE)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    if (client->name == NULL)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_503, NULL);
        return EXIT_FAILURE_FTP;
    }
    return_from_function = strcmp((const char *)client->name, "Anonymous");
    if (EXIT_SUCCESS != return_from_function)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_530_2, NULL);
        return EXIT_FAILURE_FTP;
    }
    client->connected = true;
    WRITE_CODE(client->socket.fd, FTP_CODE_230, NULL);
    return EXIT_SUCCESS;
}

/**
 * @file dele.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief DELE FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include "struct.h"
#include "define.h"
#include "functions.h"

uint8_t error_handling_dele(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    if (ONE == dbl_lineptr_length) {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    if (THREE <= dbl_lineptr_length) {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, lineptr, NO_SUCH_FILE);
        return EXIT_FAILURE_FTP;
    }
    if (false == FILE_EXIST((const char *)lineptr)) {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, lineptr, NO_SUCH_FILE);
        return EXIT_FAILURE_FTP;
    }
    if (false == FILE_PERMISSION((const char *)lineptr)) {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, lineptr, PERMISSION_DENIED);
        return EXIT_FAILURE_FTP;
    }
    return EXIT_SUCCESS;
}

uint8_t dele(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;

    return_from_function = error_handling_dele(dbl_lineptr_length, lineptr, client);
    if (EXIT_FAILURE_FTP == return_from_function) {
        return EXIT_FAILURE_FTP;
    }
    return_from_function = remove((const char *)lineptr);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, NULL);
        return EXIT_FAILURE;
    }
    WRITE_CODE(client->socket.fd, FTP_CODE_250, NULL);
    return EXIT_SUCCESS;
}

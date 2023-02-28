/**
 * @file retr.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief RETR FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "define.h"
#include "functions.h"
#include "../../Lib-IO/includes/io_stream.h"

uint8_t error_handling_retr(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    if (false == client->pasv.activated && false == client->port.activated) {
        WRITE_CODE(client->socket.fd, FTP_CODE_425, NULL);
        return EXIT_FAILURE_FTP;
    }
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

uint8_t download_file(const uint8_t *lineptr, struct clients_s *client)
{
    int32_t data_socket;
    int32_t return_from_function;
    uint8_t **dbl_ptr_dir_list_content;

    data_socket = true == client->port.activated ? client->port.socket.fd : accept(client->pasv.socket.fd, NULL, NULL);
    return_from_function = io_stream_init((char ***)&dbl_ptr_dir_list_content, (const char *)lineptr, "r", &fopen, &fclose);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        return_from_function = close(data_socket);
        if (FUNCTION_RETURN_ERROR == return_from_function) {
            LOG_ERROR("close() function: FAILURE.");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    WRITE_CODE(client->socket.fd, FTP_CODE_150, NULL);
    print_content_dbl_array_pointer(data_socket, (const uint8_t **)dbl_ptr_dir_list_content);
    WRITE_CODE(client->socket.fd, FTP_CODE_226, NULL);
    return_from_function = close(data_socket);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("close() function: FAILURE.");
        return EXIT_FAILURE;
    }
    free_dbl_array_pointer(dbl_ptr_dir_list_content);
    return EXIT_SUCCESS;
}

uint8_t retr(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;
    void *ptr_return_from_function;

    return_from_function = error_handling_retr(dbl_lineptr_length, lineptr, client);
    if (EXIT_FAILURE_FTP == return_from_function) {
        return EXIT_FAILURE_FTP;
    }
    return_from_function = download_file(lineptr, client);
    if (EXIT_FAILURE_FTP == return_from_function) {
        return EXIT_FAILURE_FTP;
    }
    ptr_return_from_function = INIT_POINTER;
    if (true == client->pasv.activated) {
        return_from_function = close(client->pasv.socket.fd);
        if (FUNCTION_RETURN_ERROR == return_from_function) {
            LOG_ERROR("close() function: FAILURE.");
            return EXIT_FAILURE;
        }
        ptr_return_from_function = memset(&client->pasv, INIT_STRUCT, sizeof(struct pasv_s));
        if (NULL == ptr_return_from_function) {
            LOG_ERROR("memset() function: FAILURE.");
            return EXIT_FAILURE;
        }
    }
    else {
        return_from_function = close(client->port.socket.fd);
        if (FUNCTION_RETURN_ERROR == return_from_function) {
            LOG_ERROR("close() function: FAILURE.");
            return EXIT_FAILURE;
        }
        ptr_return_from_function = memset(&client->port, INIT_STRUCT, sizeof(struct port_s));
        if (NULL == ptr_return_from_function) {
            LOG_ERROR("memset() function: FAILURE.");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

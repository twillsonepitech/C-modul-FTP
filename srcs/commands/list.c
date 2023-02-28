/**
 * @file list.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief LIST FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "struct.h"
#include "define.h"
#include "functions.h"
#include "../../Lib-IO/includes/io_stream.h"

void print_dir_list_content_file(const uint32_t data_socket, const uint8_t **dbl_ptr_dir_list_content, const uint8_t *lineptr)
{
    int8_t marker = false;
    int32_t index_per_iteration;
    int32_t return_from_function;

    index_per_iteration = INIT_INTEGER;
    while (dbl_ptr_dir_list_content[index_per_iteration] != NULL) {
        return_from_function = endswith(dbl_ptr_dir_list_content[index_per_iteration], lineptr);
        if (true == return_from_function) {
            dprintf(data_socket, "%s\n", dbl_ptr_dir_list_content[index_per_iteration]);
            marker = true;
        }
        index_per_iteration++;
    }
    if (false == marker) {
        dprintf(data_socket, IO_FILE_ERR, lineptr);
    }
}

uint8_t directory_listing(const uint8_t *lineptr, struct clients_s *client, const int8_t is_file)
{
    int32_t data_socket;
    int32_t return_from_function;
    uint8_t **dbl_ptr_dir_list_content;

    data_socket = true == client->port.activated ? client->port.socket.fd : accept(client->pasv.socket.fd, NULL, NULL);
    return_from_function = io_stream_init((char ***)&dbl_ptr_dir_list_content, "ls -la", "r", &popen, &pclose);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        return EXIT_FAILURE;
    }
    WRITE_CODE(client->socket.fd, FTP_CODE_150, NULL);
    if (true == is_file) {
        print_dir_list_content_file(data_socket, (const uint8_t **)dbl_ptr_dir_list_content, lineptr);
    }
    else {
        print_content_dbl_array_pointer(data_socket, (const uint8_t **)dbl_ptr_dir_list_content);
    }
    WRITE_CODE(client->socket.fd, FTP_CODE_226, NULL);
    return_from_function = close(data_socket);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("close() function: FAILURE.");
        return EXIT_FAILURE;
    }
    free_dbl_array_pointer(dbl_ptr_dir_list_content);
    return EXIT_SUCCESS;
}

uint8_t list(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;
    void *ptr_return_from_function;

    if (false == client->pasv.activated && false == client->port.activated) {
        WRITE_CODE(client->socket.fd, FTP_CODE_425, NULL);
        return EXIT_FAILURE_FTP;
    }
    return_from_function = directory_listing(lineptr, client, ONE == dbl_lineptr_length ? false : true);
    if (EXIT_FAILURE == return_from_function || EXIT_FAILURE_FTP == return_from_function) {
        return return_from_function;
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
        ptr_return_from_function = memset(&client->port, INIT_STRUCT, sizeof(struct port_s));
        if (NULL == ptr_return_from_function) {
            LOG_ERROR("memset() function: FAILURE.");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

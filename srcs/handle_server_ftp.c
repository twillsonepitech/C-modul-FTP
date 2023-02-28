/**
 * @file handle_server_ftp.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Handle incoming client connection and messages.
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include "object.h"
#include "define.h"
#include "functions.h"

static volatile sig_atomic_t RUNNING = true;

static void sig_handler(__attribute__((unused)) int32_t __unused__)
{
    RUNNING = false;
}

uint8_t handle_incoming_client(fd_set *rfds, struct clients_s **clients, struct socket_s socket, const uint8_t *path)
{
    int32_t return_from_function;

    FD_SET(socket.fd, rfds);
    return_from_function = add_incoming_client_in_linked_list(clients, socket, path);
    if (EXIT_FAILURE == return_from_function) {
        LOG_ERROR("Client: unsuccessfully added to list.");
        return EXIT_FAILURE;
    }
    else {
        LOG_INFO("Client: successfully added to list.");
    }
    return EXIT_SUCCESS;
}

uint8_t client_quitting_server(struct clients_s **clients, struct clients_s *client, fd_set *rfds)
{
    int32_t return_from_function;

    return_from_function = close(client->socket.fd);
    if (EXIT_FAILURE == return_from_function) {
        LOG_ERROR("close() function: FAILURE.");
        return EXIT_FAILURE;
    }
    FD_CLR(client->socket.fd, rfds);
    free_clients_linked_list_by_key(clients, client->socket.fd);
    return EXIT_SUCCESS;
}

uint8_t handle_message_client(struct clients_s **clients, const int32_t fd, fd_set *rfds)
{
    int32_t return_from_function;
    struct clients_s *client;

    client = *clients;
    while (client != NULL) {
        if (true == RESPONDING_CLIENT(client->socket.fd, fd)) {
            return_from_function = manage_responding_client(client);
            if (EXIT_FAILURE == return_from_function) {
                return EXIT_FAILURE;
            }
            if (client->quitted == true) {
                return_from_function = client_quitting_server(clients, client, rfds);
                if (EXIT_FAILURE == return_from_function) {
                    return EXIT_FAILURE;
                }
            }
            break;
        }
        client = client->next;
    }
    return EXIT_SUCCESS;
}

uint8_t manage_clients(struct server_ftp_s *server_ftp, struct clients_s **clients, const int32_t fd, const uint8_t *path)
{
    int32_t return_from_function;
    struct socket_s socket = {
        .address_length = sizeof(socket.address),
    };

    if (true == RESPONDING_CLIENT(server_ftp->socket.fd, fd)) {
        socket.fd = accept(fd, (struct sockaddr *)&socket.address, &socket.address_length);
        if (FUNCTION_RETURN_ERROR == socket.fd) {
            LOG_ERROR("accept() function: FAILURE.");
            return EXIT_FAILURE;
        }
        else {
            LOG_WARN("accept() function: SUCCESS.");
        }
        return_from_function = handle_incoming_client(&server_ftp->rfds[0], clients, socket, path);
        if (EXIT_FAILURE == return_from_function) {
            return EXIT_FAILURE;
        }
        else {
            WRITE_CODE(socket.fd, FTP_CODE_220, NULL);
        }
    }
    else {
        return_from_function = handle_message_client(clients, fd, &server_ftp->rfds[0]);
        if (EXIT_FAILURE == return_from_function) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

uint8_t handle_clients(struct server_ftp_s *server_ftp, struct clients_s **clients, const uint8_t *path)
{
    int32_t return_from_function;
    int32_t fd;

    fd = INIT_INTEGER;
    while (fd < FD_SETSIZE) {
        if (true == FD_ISSET(fd, &server_ftp->rfds[1])) {
            return_from_function = manage_clients(server_ftp, clients, fd, path);
            if (EXIT_FAILURE == return_from_function) {
                LOG_ERROR("Managing client: FAILURE.");
                return EXIT_FAILURE;
            }
            else {
                LOG_WARN("Managing client: SUCCESS.");
            }
        }
        fd++;
    }
    return EXIT_SUCCESS;
}

uint8_t setup_signal_and_server_socket(const int32_t server_fd, fd_set *rfds)
{
    FD_ZERO(rfds);
    FD_SET(server_fd, rfds);
    if (SIG_ERR == signal(SIGINT, sig_handler)) {
        LOG_ERROR("Setup CTRL-C handler: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_WARN("Setup CTRL-C handler: SUCCESS.");
    }
    return EXIT_SUCCESS;
}

uint8_t handle_server_ftp(struct server_ftp_s *server_ftp, const uint8_t *path)
{
    int32_t return_from_function;

    return_from_function = setup_signal_and_server_socket(server_ftp->socket.fd, &server_ftp->rfds[0]);
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    while (RUNNING) {
        server_ftp->rfds[1] = server_ftp->rfds[0];
        return_from_function = select(FD_SETSIZE, &server_ftp->rfds[1], NULL, NULL, NULL);
        if (false == RUNNING) {
            break;
        }
        if (FUNCTION_RETURN_ERROR == return_from_function) {
            LOG_ERROR("select() function: FAILURE.");
            return EXIT_FAILURE;
        }
        else {
            LOG_INFO("select() function: SUCCESS.");
        }
        return_from_function = handle_clients(server_ftp, &server_ftp->clients, path);
        if (EXIT_FAILURE == return_from_function) {
            return EXIT_FAILURE;
        }
    }
    free_clients_linked_list(&server_ftp->clients);
    return EXIT_SUCCESS;
}

/**
 * @file client_linked_list.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Add incoming client in a linked list with own informations.
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include <string.h>
#include "object.h"
#include "define.h"

struct clients_s *create_client_node(struct socket_s socket, const uint8_t *path)
{
    struct clients_s *node;

    node = (struct clients_s *)malloc(sizeof(struct clients_s));
    if (NULL == node)
    {
        LOG_ERROR("malloc(): Failed to create client node.");
        return NULL;
    }
    (void) memcpy(&node->socket, &socket, sizeof(struct socket_s));
    (void) memset(&node->pasv, INIT_STRUCT, sizeof(struct pasv_s));
    (void) memset(&node->port, INIT_STRUCT, sizeof(struct port_s));
    node->path = (uint8_t *)strdup((const char *)path);
    node->connected = false;
    node->quitted = false;
    node->name = INIT_POINTER;
    node->next = INIT_POINTER;
    return node;
}

uint8_t add_incoming_client_in_linked_list(struct clients_s **clients, struct socket_s socket, const uint8_t *path)
{
    struct clients_s *f_client;
    struct clients_s *t_client;

    if (NULL == *clients)
    {
        f_client = create_client_node(socket, path);
        if (NULL == f_client)
        {
            return EXIT_FAILURE;
        }
        *clients = f_client;
    }
    else
    {
        f_client = *clients;
        while (f_client->next != NULL)
        {
            f_client = f_client->next;
        }
        t_client = create_client_node(socket, path);
        if (NULL == t_client)
        {
            return EXIT_FAILURE;
        }
        f_client->next = t_client;
    }
    return EXIT_SUCCESS;
}

void free_clients_linked_list(struct clients_s **clients)
{
    struct clients_s *client;

    while (*clients != NULL)
    {
        client = *clients;
        *clients = (*clients)->next;
        if (client->name != NULL)
        {
            free(client->name);
        }
        free(client->path);
        free(client);
    }
}

void free_clients_linked_list_by_key(struct clients_s **clients, const int32_t fd_key)
{
    struct clients_s *client;

    if (NULL == *clients)
    {
        return;
    }
    client = INIT_POINTER;
    if ((*clients)->socket.fd == fd_key)
    {
        client = *clients;
        *clients = (*clients)->next;
        if (client->name != NULL)
        {
            free(client->name);
        }
        free(client->path);
        free(client);
        return;
    }
    free_clients_linked_list_by_key(&(*clients)->next, fd_key);
}
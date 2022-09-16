/**
 * @file struct.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Regroup all struct needed to handle server and clients.
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdint.h>
#include <arpa/inet.h>

struct buffer_s {
    int64_t readline;
    struct _IO_FILE *__stream;
    uint64_t __n;
    uint8_t *__lineptr;
};

struct socket_s {
    int32_t fd;
    struct sockaddr_in address;
    socklen_t address_length;
};

struct port_s {
    int8_t activated;
    struct socket_s socket;
};

struct pasv_s {
    int8_t activated;
    struct socket_s socket;
};

struct clients_s {
    struct socket_s socket;
    int8_t connected;
    int8_t quitted;
    uint8_t *name;
    uint8_t *path;
    struct pasv_s pasv;
    struct port_s port;
    struct clients_s *next;
};

struct server_ftp_s {
    struct socket_s socket;
    fd_set rfds[2];
    struct clients_s *clients;
};

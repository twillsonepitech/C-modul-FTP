/**
 * @file functions.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief All functions are here, they are all managing the creation
 * of the ftp server.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdint.h>
#include "object.h"

uint32_t activate_ftp_server(const uint32_t port, const uint8_t *path);

uint32_t get_port(Ftp *this);
const uint8_t *get_path(Ftp *this);
Ftp *set_port(Ftp *this, const uint32_t port);
Ftp *set_path(Ftp *this, const uint8_t *path);

/**
 * @file getter_and_setter.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Getter and Setter for port and path.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "object.h"

uint32_t Get_port(Ftp *this)
{
    return this->port;
}

const uint8_t *Get_path(Ftp *this)
{
    return this->path;
}

Ftp *Set_port(Ftp *this, const uint32_t port)
{
    this->port = port;
    return this;
}

Ftp *Set_path(Ftp *this, const uint8_t *path)
{
    this->path = path;
    return this;
}

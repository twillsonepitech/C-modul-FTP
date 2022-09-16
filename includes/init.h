/**
 * @file init.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Init ctor and dtor of Ftp class.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "object.h"

void Ctor(Ftp *this, va_list va_arg);
void Dtor(Ftp *this);

uint32_t Get_port(Ftp *this);
const uint8_t *Get_path(Ftp *this);
Ftp *Set_port(Ftp *this, const uint32_t port);
Ftp *Set_path(Ftp *this, const uint8_t *path);

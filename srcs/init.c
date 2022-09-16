/**
 * @file init.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Init ctor and dtor of Ftp class.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "object.h"
#include "init.h"

void Ctor(Ftp *this, va_list va_list_args)
{
    if (NULL == this || NULL == va_list_args)
        raise("The class is empty.");
    this->port = va_arg(va_list_args, uint32_t);
    this->path = va_arg(va_list_args, const uint8_t *);
}

void Dtor(__attribute__((unused)) Ftp *this)
{
}

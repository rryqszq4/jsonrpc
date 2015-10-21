/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: rryqszq4                                                     |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
#include "jsr_epoll.h"

jsr_epoll_t *
jsr_epoll_init()
{
    jsr_epoll_t *self = (jsr_epoll_t *)malloc(sizeof(jsr_epoll_t));

    self->epoll_fd = epoll_create(1024);

    return self;
}

int
jsr_epoll_add_fd(jsr_epoll_t *self, int fd)
{
    struct epoll_event ev;

    ev.events = 0;
    ev.data.fd = fd;

    if (epoll_ctl(self->epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1)
        return -1;

    return 0;
}

int 
jsr_epoll_del_fd(jsr_epoll_t *self, int fd)
{
    if (epoll_ctl(self->epoll_fd, EPOLL_CTL_DEL, fd, NULL) ==-1)
        return -1;

    return 0;
}

int 
jsr_epoll_set_in(jsr_epoll_t *self, int fd)
{
    struct epoll_event ev;

    ev.events |= EPOLLIN;
    ev.data.fd = fd;

    if (epoll_ctl(self->epoll_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
        return -1;

    return 0; 
}

int
jsr_epoll_set_out(jsr_epoll_t *self, int fd)
{
    struct epoll_event ev;

    ev.events |= EPOLLOUT;
    ev.data.fd = fd;

    if (epoll_ctl(self->epoll_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
        return -1;

    return 0;
}

void
jsr_epoll_loop(jsr_epoll_t *self, int timeout)
{
    int res;
    
    while (1){
        res = epoll_wait(self->epoll_fd, self->events, JSR_MAX_EVENTS, timeout);
        if (res == -1 && errno == EINTR)
            continue;
        break;
    }
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
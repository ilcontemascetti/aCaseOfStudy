/*
 * sock_util.h: useful socket macros and structures
 *
 * 2008-2011, Razvan Deaconescu, razvan.deaconescu@cs.pub.ro
 * 2016, Călin Cruceru, calin.cruceru@stud.acs.upb.ro, 335CB
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SOCK_UTIL_H_
#define SOCK_UTIL_H_ 1

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

/* default backlog for listen(2) system call */
#define DEFAULT_LISTEN_BACKLOG 5

extern int tcp_connect_to_server(const char *name, unsigned short port);
extern int tcp_close_connection(int sockfd);
extern int tcp_create_listener(unsigned short port, int backlog);
extern int get_peer_address(int sockfd, char *buf, size_t len);

/* Wrappers over system calls send/recv/sendfile.
 *
 * They abstract the fact that the sockets are nonblocking, so each
 * send/receive is done until EAGAIN (or EWOULDBLOCK) error is set in errno.
 *
 * Note that this is *required* by the AWS as all these socket fds are added
 * to EPOLL using edge-triggered notifications, so not reading/sending until
 * EAGAin/EWOULDBLOCK could make the connection with which this socket fd is
 * associated starve.
 */
extern ssize_t recv_nonblock(int sockfd, void *buffer, off_t *offset,
			     size_t count);
extern ssize_t send_nonblock(int sockfd, void *buffer, off_t *offset,
			     size_t count);
extern ssize_t sendfile_nonblock(int sockfd, int fd, off_t *offset,
				 size_t count);

#endif /* SOCK_UTIL_H_ */


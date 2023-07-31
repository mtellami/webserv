/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:42:14 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/31 18:12:00 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

// Create the Server listening socket
Cluster::Cluster(Config _conf) : _config(_conf) {
    int option = 1;
    _addrlen = sizeof(_address);
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd == FAIL)
        throw System();

    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    // _address.sin_addr.s_addr = inet_addr("27.0.0.1");
    _address.sin_port = htons(8080);
    memset(_address.sin_zero, 0, sizeof(_address.sin_zero));
    setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR , &option, sizeof(option));
    if (bind(_socket_fd, (struct sockaddr*)&_address, _addrlen) == FAIL) {
        close(_socket_fd);
        throw System();
    }
    if (listen(_socket_fd, SOMAXCONN) == FAIL) {
        close(_socket_fd);
        throw System();
    }
}

Cluster::~Cluster(void) {
    close(_socket_fd);
}

//Getters
SOCK_FD Cluster::get_listen_fd() {
    return _socket_fd;
}

struct sockaddr_in  *Cluster::get_address(void) {
    return &_address;
}

socklen_t *Cluster::get_addrlen(void) {
    return &_addrlen;
}

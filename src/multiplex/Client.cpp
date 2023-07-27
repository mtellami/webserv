/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:42:38 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/27 15:54:37 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client(Cluster *cluster) : _cluster(cluster) {
    _done_recv = false;
    _done_send = false;
    _socket = accept(_cluster->get_listen_fd(), (struct sockaddr *)_cluster->get_address(), (socklen_t*)_cluster->get_addrlen());
    _req = new Request;
    _req->_fd = -1;
    _req->_recv_header = false;
    _req->_body_size = 0;
    _res = new Response; 
}

Client::~Client(void) {
    delete _req;
    delete _res;
}

SOCK_FD Client::get_connect_fd() {
    return _socket;
}

void    Client::parse_header(std::string buffer) {
    // Start parsing the request ..............
    (void)buffer;
    _req->_header["Content-Length"] = "123";
    _req->_method = "GET";
}

void    Client::recv_body(void) {
    // in POST request recv the posted file by chunks ...
}

// call this function when the client is readyToWrite in 
void    Client::recieve(void) {
    _req->_i = recv(_socket, _req->_buffer, SIZE, 0);
    if (_req->_i == -1)
        throw System();
    if (!_req->_i) {
        _done_recv = true;
        return;
    }
    _recv_buffer += std::string(_req->_buffer, _req->_i);
    if (_recv_buffer.find("\r\n\r\n") != std::string::npos) {
        if (!_req->_recv_header) {
            _req->_recv_header = true;
            parse_header(_recv_buffer.substr(0, _recv_buffer.find("\r\n\r\n")));
            if (_req->_method == "GET")
                _done_recv = true;
            std::cout << "Request header recieved ........" << std::endl;
        } else {
            // if (_req->_header.find("Content-Length") == _req->_header.end())
            // to be continued ......
            recv_body();
            std::cout << "Still reading ......" << std::endl;
        }
    }
}

// Static response for testing ........
void    Client::sending(void) {
    std::string res("HTTP/1.1 200 OK\n\
    Content-Type: text/html\n\
    Content-Length: 20\n\n\
    <h1>Webserv: Server is Running ...</h1>");

    if (!_done_recv)
        return;
    send(_socket, res.c_str(), strlen(res.c_str()), 0);
    _done_send = true;
    std::cout << "Done sending ......." << std::endl;
}

bool    Client::done_send(void) {
    return _done_send;
}

// <========= REQUEST EXAMPLE ===========>

// POST / HTTP/1.1
// User-Agent: PostmanRuntime/7.32.3
// Accept: */*
// Postman-Token: 9d62d6b6-0004-4bcf-b00d-dd4f835a6697
// Host: localhost:8080
// Accept-Encoding: gzip, deflate, br
// Connection: keep-alive
// Content-Length: 41
// Content-Type: application/octet-stream
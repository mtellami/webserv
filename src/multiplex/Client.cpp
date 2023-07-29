/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:42:38 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/29 19:18:21 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client(Cluster *cluster) : _cluster(cluster) {
    _done_recv = false;
    _done_send = false;
    _socket = accept(_cluster->get_listen_fd(), (struct sockaddr *)_cluster->get_address(), (socklen_t*)_cluster->get_addrlen());
    _req = new Request;
    _req->_fd = -1;
    _req->_i = 0;
    _req->_recv_header = false;
    _req->_downloading = false;
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

void    Client::parse_header() {
    std::string header(_recv_buffer.substr(0, _recv_buffer.find("\r\n\r\n")));
    // std::cout << header << std::endl;
    // exit(0);

    std::istringstream iss(header);
    std::string line;

    iss >> line;
    _req->_method = line;
    iss >> line;
    _req->_path = line;
    std::getline(iss, line);
    while (1) {
        if (!std::getline(iss, line))
            break;
        _req->_header.insert(_req->_header.end(), std::make_pair(line.substr(0, line.find(":")), line.substr(line.find(" "))));
    }
    std::cout << "Request header recieved ........" << std::endl;
    if (_req->_method == "GET")
        _done_recv = true;
}

void    Client::recv_body(void) {
    if (_done_recv)
        return;
    _req->_fd = open("upload.jpg", O_CREAT | O_RDWR, 0666);
    write(_req->_fd, _recv_buffer.c_str(), strlen(_recv_buffer.c_str()));
    close(_req->_fd);
}

// call this function when the client is readyToWrite in 
void    Client::recieve(void) {
    if (_done_recv)
        return ;
    if (!_req->_recv_header) {
        while (_recv_buffer.find("\r\n\r\n") == std::string::npos) {
            _req->_i = recv(_socket, _req->_buffer, 1, 0);
            if (_req->_i == -1)
                throw System();
            if (!_req->_i) {
                _done_recv = true;
                return;
            }
            _recv_buffer += std::string(_req->_buffer, _req->_i);
        }
        parse_header();
        _req->_recv_header = true;
    }else {
        int i = 0;
        while (i < stoi(_req->_header.find("Content-Length")->second) && i < SIZE) {
            _req->_i = recv(_socket, _req->_buffer, 1, 0);
            if (_req->_i == -1)
                throw System();
            if (!_req->_i) {
                _done_recv = true;
                return;
            }
            _recv_buffer += std::string(_req->_buffer, _req->_i);
            i++;
        }
        std::cout << "Uploading .............." << std::endl;
        if (i == stoi(_req->_header.find("Content-Length")->second)) { // never be here ..
            _done_recv = true;
            recv_body();
        }
    }

    _recv_buffer += std::string(_req->_buffer, _req->_i);
    if (!_req->_recv_header) {
        if (_recv_buffer.find("\r\n\r\n") != std::string::npos) {
            _req->_recv_header = true;
            _req->_i = _recv_buffer.substr(_recv_buffer.find("\r\n\r\n")).length();
        }
    } else {
        recv_body();
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
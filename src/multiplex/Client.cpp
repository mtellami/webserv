/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:42:38 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/01 11:43:46 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// Client constructor
Client::Client(Cluster *cluster) : _cluster(cluster) {
    _done_recv = false;
    _done_send = false;
    _socket = accept(_cluster->get_listen_fd(), (struct sockaddr *)_cluster->get_address(), (socklen_t*)_cluster->get_addrlen());
    _req = new Request;
    _res = new Response(cluster); 
}

// Destructor
Client::~Client(void) {
    delete _req;
    delete _res;
}

// Getter
SOCK_FD Client::get_connect_fd() {
    return _socket;
}

// Parse the request header
void    Client::parse_header() {
    std::string         header(_recv_buffer.substr(0, _recv_buffer.find("\r\n\r\n")));
    std::istringstream  iss(header);
    std::string         line;

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
    _recv_buffer = "";
    if (_req->_method != "POST") {
        _done_recv = true;
        return ;
    }
    _buffer_size = 0;
    _req->_body_size = stoi(_req->_header.find("Content-Length")->second);
}

// Generate random file name
std::string rand_name(void) {
    char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string name;
    srand(time(0));

    for (int i = 0; i < 20; i++) {
        name += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return name;
}

// Recieve the request body
void    Client::recv_body(void) {
    if (_done_recv)
        return;
    std::string suffix(_req->_header.find("Content-Type")->second.substr(_req->_header.find("Content-Type")->second.find("/") + 1));
    std::ofstream out("upload/" + _req->_filename + "." + suffix, std::ios::binary | std::ios::app);
    out << _recv_buffer;
    out.close();
    _recv_buffer = "";
}

// Recive from the ready client
void    Client::recieve(void) {
    if (_done_recv)
        return ;
    if (!_req->_recv_header) {
        while (_recv_buffer.find("\r\n\r\n") == std::string::npos) {
            _req->_i = recv(_socket, _req->_buffer, 1, 0);
            if (_req->_i == FAIL)
                throw System();
            if (!_req->_i) {
                _done_recv = true;
                return;
            }
            _recv_buffer += std::string(_req->_buffer, _req->_i);
        }
        parse_header();
        _req->_filename = rand_name();
        _req->_recv_header = true;
    }else {
        int i = 0;
        while (_buffer_size < (size_t)_req->_body_size && i < SIZE) {
            _req->_i = recv(_socket, _req->_buffer, 1, 0);
            if (_req->_i == FAIL)
                throw System();
            if (!_req->_i) {
                _done_recv = true;
                return;
            }
            _recv_buffer += std::string(_req->_buffer, _req->_i);
            i++;
            _buffer_size++;
        }
        recv_body();
        if (_buffer_size == (size_t)_req->_body_size)
            _done_recv = true;
    }
}

// Static response for testing ........
void    Client::sending(void) {
    std::string res("HTTP/1.1 200 OK\n\
    Content-Type: text/html\n\
    Content-Length: 20\n\n\
    <h1>" + _req->_method + " request Accepted and served</h1>");

    if (!_done_recv)
        return;
    send(_socket, res.c_str(), strlen(res.c_str()), 0);
    _done_send = true;
}

bool    Client::done_send(void) {
    return _done_send;
}

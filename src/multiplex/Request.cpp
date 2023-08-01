/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:12:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/01 14:55:59 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// Constructor
Request::Request() {
    _i = 0;
    _recv_header = false;
    _body_size = 0;
    _filename = "";
    _bad_request = true;
}

// Destructor
Request::~Request() {
}

// Getter
std::string Request::get_method(void) {
    return _method;
}

bool Request::recieve_header(void) {
    return _recv_header;
}

// parse the client request header
void    Request::parse_request_header(bool & _done_recv) {
    std::string         header(_recv_buffer.substr(0, _recv_buffer.find("\r\n\r\n")));
    std::istringstream  iss(header);
    std::string         line;

    iss >> line;
    _method = line;
    iss >> line;
    _path = line;
    std::getline(iss, line);
    while (1) {
        if (!std::getline(iss, line))
            break;
        _header.insert(_header.end(), std::make_pair(line.substr(0, line.find(":")), line.substr(line.find(" "))));
    }
    _recv_buffer = "";
    if (_method != "POST") {
        _done_recv = true;
        return ;
    }
    _buffer_size = 0;
    _body_size = stoi(_header.find("Content-Length")->second);
}

// get the client request header
void    Request::get_request_header(SOCK_FD & _socket, bool & _done_recv) {
    while (_recv_buffer.find("\r\n\r\n") == std::string::npos) {
        _i = recv(_socket, _buffer, 1, 0);
        if (_i == FAIL)
            throw System();
        if (!_i) {
            _done_recv = true;
            return;
        }
        _recv_buffer += std::string(_buffer, _i);
    }
    parse_request_header(_done_recv);
    _recv_header = true;
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

// write the readed chunk to the file
void Request::write_body_chunk(bool & _done_recv) {
    if (_done_recv)
        return;
    std::string suffix(_header.find("Content-Type")->second.substr(_header.find("Content-Type")->second.find("/") + 1));
    std::ofstream out("upload/" + _filename + "." + suffix, std::ios::binary | std::ios::app);
    out << _recv_buffer;
    out.close();
    _recv_buffer = "";
}

// get the client request body by chunks
void Request::get_request_body(SOCK_FD & _socket, bool & _done_recv) {
    if (_filename == "")
        _filename = rand_name();
    int i = 0;
    while (_buffer_size < (size_t)_body_size && i < SIZE) {
        _i = recv(_socket, _buffer, 1, 0);
        if (_i == FAIL)
            throw System();
        if (!_i) {
            _done_recv = true;
            return;
        }
        _recv_buffer += std::string(_buffer, _i);
        i++;
        _buffer_size++;
    }
    write_body_chunk(_done_recv);
    if (_buffer_size == (size_t)_body_size)
        _done_recv = true;
}


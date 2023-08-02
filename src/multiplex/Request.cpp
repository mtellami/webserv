/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:12:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/02 16:08:50 by mtellami         ###   ########.fr       */
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
    return _start_line[0];
}

bool Request::recieve_header(void) {
    return _recv_header;
}

// parse the client request header
void    Request::parse_request_header(bool & _done_recv) {
    _recv_buffer = _recv_buffer.substr(0, _recv_buffer.find("\r\n\r\n"));
    std::istringstream  iss(_recv_buffer);
    std::string         line;

    std::getline(iss, line);
    std::istringstream  _ss(_recv_buffer);
    std::string         buff;

    while (_ss >> buff)
        _start_line.push_back(std::string(buff));
    // print here ......
    while (1) {
        if (!std::getline(iss, line))
            break;
        _req_header.insert(_req_header.end(), std::make_pair(line.substr(0, line.find(":")), line.substr(line.find(" "))));
    }
    _recv_buffer = "";
    if (_start_line[0] != "POST") {
        _done_recv = true;
        return ;
    }
    _buffer_size = 0;
    _body_size = stoi(_req_header.find("Content-Length")->second);
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
    std::string suffix(_req_header.find("Content-Type")->second.substr(_req_header.find("Content-Type")->second.find("/") + 1));
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

void Request::print(void) {
    std::cout << _start_line[0] <<std::endl;
    std::cout << _start_line[1] <<std::endl;
    std::cout << _start_line[2] <<std::endl;
    std::map<std::string, std::string>::iterator it;
    for (it = _req_header.begin(); it != _req_header.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

// ----------- REQUEST HEADER EXAMPLE -------------------

// POST /cgi-bin/process.cgi HTTP/1.1
// User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
// Host: www.tutorialspoint.com
// Content-Type: application/x-www-form-urlencoded
// Content-Length: length
// Accept-Language: en-us
// Accept-Encoding: gzip, deflate
// Connection: Keep-Alive

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:11:54 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/01 14:56:13 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "include.hpp"

class Request {
    private:
        std::string       _recv_buffer;
        size_t            _buffer_size;
        std::map<std::string, std::string>  _header;
        std::string       _method;
        std::string       _path;
        std::string       _version;
        char              _buffer[SIZE];
        int               _i;
        bool              _bad_request;
        int               _body_size;
        std::string       _filename;
        bool              _recv_header;

    public:
        Request();
        ~Request();

        void    get_request_header(SOCK_FD & _socket, bool & _done_recv);
        void    parse_request_header(bool & _done_recv);

        void    get_request_body(SOCK_FD & _socket, bool & _done_recv);
        void    write_body_chunk(bool & _done_recv);

        std::string get_method(void);
        bool        recieve_header(void);
};

#endif
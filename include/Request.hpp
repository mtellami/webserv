/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:11:54 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/30 10:30:24 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "include.hpp"

class Request {
    public:
        std::map<std::string, std::string>  _header;
        std::string       _method;
        std::string       _path;
        std::string       _version;
        char              _buffer[SIZE];
        int               _i;
        bool              _recv_header;
        int               _body_size;

        Request();
        ~Request();
};

#endif
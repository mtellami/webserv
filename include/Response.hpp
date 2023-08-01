/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:11:00 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/01 10:14:37 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "include.hpp"
#include "Cluster.hpp"

class Response {
    public:
        Cluster *_cluster;

        int         _status_code;
        std::string http_version;
        std::string _content_type;
        std::string _content_len;

        Response(Cluster *cluster);
        ~Response(void);
};

#endif

// ----- RESPONSE EXAMPL -----

// HTTP/1.1 200 OK
// Date: Mon, 27 Jul 2009 12:28:53 GMT
// Server: Apache/2.2.14 (Win32)
// Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
// ETag: "34aa387-d-1568eb00"
// Vary: Authorization,Accept
// Accept-Ranges: bytes
// Content-Length: 88
// Content-Type: text/html
// Connection: Closed
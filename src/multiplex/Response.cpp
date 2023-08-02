/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:15:03 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/02 09:53:40 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(Cluster *cluster) : _cluster(cluster) {
}

Response::~Response() {
}

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
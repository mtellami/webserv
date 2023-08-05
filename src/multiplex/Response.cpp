/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamer <maamer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:15:03 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/05 14:29:15 by maamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(Cluster *cluster) : _cluster(cluster) {
}

Response::~Response() {
}


//The purpose of this function is to determine the appropriate Content-Type 
//The code extracts the file extension from the _path variable of the Request class
std::string Request::getContentType()
{
    std::map<std::string, std::string> content;
    content["txt"] = "text/plain";
    content["html"] = "text/html";
    content["css"] = "text/css";
    content["js"] = "text/javascript";
    content["json"] ="application/json";
    content["xml"] = "application/xml";
    content["pdf"] = "application/pdf";
    content["zip"] = "application/zip";
    content["jpeg"] = "image/jpeg";
    content["png"] = "image/png";
    content["gif"] = "image/gif";
    content["ogg"] = "audio/ogg";
    content["wav"] = "audio/wav";
    content["mp3"] = "audio/mp3";
    content["webm"] = "video/webm";
	content["mp4"] = "video/mp4";
    content[""] = "application/octet-stream";
    if (content.find(_start_line[1].substr(_start_line[1].find_last_of(".") + 1)) != content.end())
		return content[_start_line[1].substr(_start_line[1].find_last_of(".") + 1)];
	else
		return content[""];

}

// int Response:: get_methode(Config &config_file)
// {

// }

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
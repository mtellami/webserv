/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamer <maamer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:11:00 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/05 11:16:22 by maamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "include.hpp"
#include "Cluster.hpp"
#include "Request.hpp"
class Response {
    public:
        Cluster *_cluster;

        int                 _status_code;
        std::string         _http_version;
        std::string         _status_message;
        std::map<std::string, std::string>  _res_header;
      
        std::string _content_type;
        std::string _content_len;
        //Response(Cluster *cluster);
        void response_pages(Config &config_file);
        // int get_methode(Config &config_file);
       
        

        Response(Cluster *cluster);
        ~Response(void);
};

#endif
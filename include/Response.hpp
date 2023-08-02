/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:11:00 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/02 10:51:02 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "include.hpp"
#include "Cluster.hpp"

class Response {
    public:
        Cluster *_cluster;

        int                 _status_code;
        std::string         _http_version;
        std::string         _status_message;
        std::map<std::string, std::string>  _res_header
        ;

        Response(Cluster *cluster);
        ~Response(void);
};

#endif
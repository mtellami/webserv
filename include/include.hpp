/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:25:47 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/31 19:09:56 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
#define INCLUDE_HPP

// Headers
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <sstream>

// Macros
#define FAIL -1
#define SIZE 1024

// Typedefs
typedef int SOCK_FD; // socket file descriptor

// Exceptions
class System : public std::exception {
    public:
        virtual const char* what() const throw() {
            return std::string("System call function failed: " + std::string(strerror(errno))).c_str();
        }
};

#endif

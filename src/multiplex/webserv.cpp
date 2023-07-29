/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:24:24 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/27 18:51:05 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char **argv)
{
    Server http;

    try {
        if (argc > 2) {
            std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
            return EXIT_FAILURE;
        }
        // signal(SIGINT, stop);
        http.init(argv[1]);
        http.run();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

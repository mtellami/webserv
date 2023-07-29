/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:19:04 by mtellami          #+#    #+#             */
/*   Updated: 2023/07/28 09:29:48 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "include.hpp"
#include "Cluster.hpp"
#include "Client.hpp"

class Server {
    private:
        std::vector<Cluster*>   _clusters;
        std::list<Client*>      _clients;
        SOCK_FD                 _nfds;
        fd_set                  _readfds;
        fd_set                  _writefds;
        fd_set                  _copy_readfds;
        fd_set                  _copy_writefds; 

    public:
        Server(void);
        ~Server(void);

        SOCK_FD get_nfds(void);
        SOCK_FD get_readfds(void);
        SOCK_FD get_writefds(void);
        void    init(char *filename);
        void    run(void);
        void    set_fds(void);
        void    accept_connection(void);
        void    drop_client(Client *client);
        void    handle_requests(void);
        void    responsing(void);
        void    clear(void);
};

void    contexts_count(std::vector<Config> &srvs, std::string path);
void    clear(int sig);

#endif
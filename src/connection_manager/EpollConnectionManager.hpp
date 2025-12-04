/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollConnectionManager.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:23:08 by capapes           #+#    #+#             */
/*   Updated: 2025/12/04 19:22:24 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/time.h>   //gettimeofday
#include <sys/wait.h>   // waitpid
#include <sys/epoll.h>  //epoll
#include <cstring>      //memset
#include <algorithm>  // for std::replace, std::transform
#include <cctype>     // for ::toupper

// project
#include <colors.hpp>
#include <Log.hpp>
#include <Request.hpp>
#include <Schemas.hpp>
#include <ServerManager.hpp>
#include <Socket.hpp>

struct Connection {
    int          fd;
    std::string  readBuffer;
    Request      request;
    Response     response;
    std::string  writeBuffer;
    bool         keepAlive;
    double       lastActive;
};

struct CgiData {
    std::map<std::string, std::string>   envStrings; 
    std::vector<char*>          envp;            
    std::string                 body;
};

struct CGIConnections {
    int         stdIn;
    int         stdOut;
    CgiData     data;
    double      lastActive;
	int			pid;
};

typedef std::map<int, Connection>::iterator     ConnectionIterator;
typedef std::map<int, CGIConnections>::iterator CGIIterator;

typedef int clientFd;
typedef int pipeFd;

class EpollConnectionManager {
    public:
        EpollConnectionManager(std::map<int, Socket*>, ServerManager);

    private:
        int                             epfd;
        std::map<int, Socket*>          listeningSockets;
        ServerManager                   serverManager;
        std::map<int, Connection>       connections;
        std::map<int, CGIConnections>   CGIConn;

        void    run();
        void    setInstance(int fd, uint32_t events, int op);

        void    handleEvent(epoll_event &ev);
        void    handleNewConnection(Socket *sock);
        void    handleRead(int clientfd);
        void    handleWrite(int clientfd);
        void    handlePipeRead(int fd);
        void    handlePipeWrite(int pipefd);

        void    cleanupIdleConnections(const double &now);
        void    closeConnection(int fd);

        // Request handler things
        void    badRequest(const int fd);
        void    requestHandler(const int clientfd);
        
        // Utils
        void    exitWithError(const std::string& message);
        bool    isClient(int fd);
        int     findClientByPipe(int pipefd);
        void    CGIHandler(const int fd, const std::string& path);
};

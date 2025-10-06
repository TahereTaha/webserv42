/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:17:08 by capapes           #+#    #+#             */
/*   Updated: 2025/10/06 19:40:49 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

extern pthread_mutex_t logMutex;
enum EventType {
    SERVER_START,
    SOCKET_BIND,
    EPOLL_ADD_SOCKET,
    EPOLL_ADD_CONNECTION,
    EPOLL_EVENT_CLOSE,
    EPOLL_EVENT_READING,
    EPOLL_EVENT_WRITING,
    EPOLL_EVENT_ERROR,
    NEW_CONNECTION,
    INFO,
    ERROR
};

struct Event {
    EventType   type;
    int         code;
    std::string timestamp;

    Event(EventType t, int code = 0);
    std::string toString() const;
};

class EventLog {
public:
    static void init(const std::string& filename);
    static void log(const Event& event);
	static void log(EventType type, int code);
    static void shutdown();
};

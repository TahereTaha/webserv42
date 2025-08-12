/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:17:08 by capapes           #+#    #+#             */
/*   Updated: 2025/08/07 13:08:31 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

static pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;

enum EventType {
    SERVER_START,
    SOCKET_BIND,
    EPOLL_ADD,
    EPOLL_EVENT,
    NEW_CONNECTION,
    INFO,
    ERROR
};

struct Event {
    EventType type;
    std::string message;
    std::string timestamp;

    Event(EventType t, const std::string& msg);
    std::string toString() const;
};

class EventLog {
public:
    static void init(const std::string& filename);
    static void log(const Event& event);
	static void log(EventType type, const std::string& message);
    static void shutdown();
};

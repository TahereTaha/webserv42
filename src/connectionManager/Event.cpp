/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:17:47 by capapes           #+#    #+#             */
/*   Updated: 2025/10/06 19:41:04 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;
static std::ofstream logFile;

// Utility function to get the current time as a string
std::string getCurrentTimestamp() {
	time_t now = time(NULL);
	char buffer[64];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
	return std::string(buffer);
}


Event::Event(EventType t, int code)
    : type(t), code(code), timestamp(getCurrentTimestamp()) {}

std::string Event::toString() const {
    std::string typeStr;

    switch (type) {
        case SERVER_START:              typeStr = "\n\n\n[SERVER] Server started"; break;
        case SOCKET_BIND:               typeStr = "[SOCKET] Socket created on port:"; break;
        case EPOLL_ADD_CONNECTION:      typeStr = "[EPOLL] Added connection to epoll: "; break;
        case EPOLL_ADD_SOCKET:          typeStr = "[EPOLL] Added socket to epoll: "; break;
        case EPOLL_EVENT_CLOSE:         typeStr = "[EVENT] Closing idle connection: "; break;
        case EPOLL_EVENT_READING:       typeStr = "[EVENT] Handling read event for client: "; break;
        case EPOLL_EVENT_WRITING:       typeStr = "[EVENT]"; break;
        case EPOLL_EVENT_ERROR:         typeStr = "[EVENT] Request error for client: "; break;
        case NEW_CONNECTION:            typeStr = "[CONNECTION] New connection from: "; break;
        case INFO:                      typeStr = "[INFO]"; break;
        case ERROR:                     typeStr = "[ERROR]"; break;
    }
    std::ostringstream oss;
    oss << code;
    return "[" + timestamp + "] " + typeStr + oss.str();
}

void EventLog::init(const std::string& filename) {
	pthread_mutex_lock(&logMutex);
    logFile.open(filename.c_str(), std::ios::app);
    if (!logFile.is_open())
	{
        std::cerr << "Failed to open event log file.\n";
	};
	pthread_mutex_unlock(&logMutex);
	EventLog::log(SERVER_START, 0);
}

void EventLog::log(const Event& event) {
   	pthread_mutex_lock(&logMutex);
    if (logFile.is_open()) {
        logFile << event.toString() << std::endl;
	};
	pthread_mutex_unlock(&logMutex);
}

void EventLog::log(EventType type, int code)
{
	Event event(type, code);
	EventLog::log(event);
}

void EventLog::shutdown() {
    pthread_mutex_lock(&logMutex);
    if (logFile.is_open())
	{
        logFile.close();
	};
	pthread_mutex_unlock(&logMutex);
}
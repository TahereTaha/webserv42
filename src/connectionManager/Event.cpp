/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:17:47 by capapes           #+#    #+#             */
/*   Updated: 2025/08/07 13:44:27 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

static std::ofstream logFile;

// Utility function to get the current time as a string
std::string getCurrentTimestamp() {
	time_t now = time(NULL);
	char buffer[64];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
	return std::string(buffer);
}


Event::Event(EventType t, const std::string& msg)
    : type(t), message(msg), timestamp(getCurrentTimestamp()) {}

std::string Event::toString() const {
    std::string typeStr;

    switch (type) {
        case SERVER_START:    typeStr = "\n\n\n[SERVER]"; break;
        case SOCKET_BIND:     typeStr = "[SOCKET]"; break;
        case EPOLL_ADD:       typeStr = "[EPOLL]"; break;
        case EPOLL_EVENT:     typeStr = "[EVENT]"; break;
        case NEW_CONNECTION:  typeStr = "[CONNECTION]"; break;
        case INFO:            typeStr = "[INFO]"; break;
        case ERROR:           typeStr = "[ERROR]"; break;
    }

    return "[" + timestamp + "] " + typeStr + " " + message;
}

void EventLog::init(const std::string& filename) {
	pthread_mutex_lock(&logMutex);
    logFile.open(filename.c_str(), std::ios::app);
    if (!logFile.is_open())
	{
		
        std::cerr << "Failed to open event log file.\n";
	};
	pthread_mutex_unlock(&logMutex);
	EventLog::log(SERVER_START, "Server started");
}

void EventLog::log(const Event& event) {
   	pthread_mutex_lock(&logMutex);
    if (logFile.is_open()) {
        logFile << event.toString() << std::endl;
	};
	pthread_mutex_unlock(&logMutex);
}

void EventLog::log(EventType type, const std::string& message)
{
	Event event(type, message);
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
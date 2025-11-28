
#pragma once

#include "EpollConnectionManager.hpp"
#include "Socket.hpp"
#include <iostream>
#include "Log.hpp"
#include <map>
#include <vector>
#include <intermediate_representation.hpp>

std::map<int, Socket *>	set_up_sockets(std::vector<t_server> servers);




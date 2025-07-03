#pragma once

#include <iostream>
#include "Terminal.hpp"

class Server : public Terminal
{
	private:
	protected:
	public:
		Server(void);
		Server(std::string str);
		Server(const Server& other);
		Server& operator=(const Server& other);
};


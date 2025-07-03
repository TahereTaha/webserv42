#pragma once

#include <iostream>
#include "Terminal.hpp"

class ServerName : public Terminal
{
	private:
	protected:
	public:
		ServerName(void);
		ServerName(std::string str);
		ServerName(const ServerName& other);
		ServerName& operator=(const ServerName& other);
		virtual Symbol* clone() const;
		void setText(const std::string& str);
};


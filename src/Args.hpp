#pragma once

#include <string>

class Args
{
	private:
		std::string	_configFileName;
	protected:
	public:
		Args(int argc, char **argv);
		~Args(void);

		std::string	getConfigFileName(void) const ;
};

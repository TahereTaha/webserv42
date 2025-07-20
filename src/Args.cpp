#include <Args.hpp>
#include <string>
#include <stdexcept>

Args::Args(int argc, char **argv)
{
	if (argc < 2)
		throw std::invalid_argument("Please provide a configuration file on the arguments.");
	if (argc > 2)
		throw std::invalid_argument("Please provide only one configuration file on the arguments.");
	this->_configFileName = argv[1];
}

Args::~Args(void)
{
}

std::string	Args::getConfigFileName(void) const
{
	return (this->_configFileName);
}


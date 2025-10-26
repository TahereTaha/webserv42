#include <IpLiteral.hpp>

#include <stdexcept>

IpLiteral::IpLiteral(void)
{
}

IpLiteral::IpLiteral(std::string text)
{
	this->_text = text;
	this->identify_type();
	if (this->_type == IP_V_FUTURE)
		throw (std::invalid_argument("ip literal unsuported"));
}

IpLiteral::~IpLiteral(void)
{
}

void	IpLiteral::identify_type(void)
{
	this->_type = IP_V_4;
	if (this->_text.size < 3)
		return ;
	if (this->_text[0] == '[')
		this->_type = IP_V_6;
	if (this->_text[0] == '[' && this->_text[1] == 'v')
		this->_type = IP_V_FUTURE;
	if (this->_text[0] != '[')
		this->_type = IP_V_4;
}

//	127.0.0.1
//	[223:234::233:24]


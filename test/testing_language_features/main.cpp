#include <iostream>
#include <stdint.h>

int main(void)
{
	uint16_t	num = 0x23a;
	std::cout << "hola" << std::endl;
	std::cout << std::hex << (int)num << std::endl;
	std::cout << std::hex << (int)(num >> 8) << std::endl;
}


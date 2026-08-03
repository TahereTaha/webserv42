#include <Scheme.hpp>

#include <string>
#include <vector>
#include <stdexcept>

// simple test with no scheme

int main(void)
{
	Scheme	test;

	if (test.getSchemeType() != scheme_UNOFFICIAL)
		return (1);
	
	return (1);
}

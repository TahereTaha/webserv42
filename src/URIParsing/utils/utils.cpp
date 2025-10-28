#include "utils.hpp"

#include <limits>
#include <stdexcept>

int	stoi(std::string num_str, size_t *pos, int base)
{
	size_t	i = 0;
	long	num = 0;
	int		digit = 0;
	int		sign = 1;

	//	skip all the spaces.
	while (i < num_str.size() && isspace(num_str[i]))
		i++;
	if (i < num_str.size() && num_str[i] == '+')
		i++;
	else if (i < num_str.size() && num_str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (i == num_str.size() || !isalnum(num_str[i]))
		throw (std::invalid_argument("not a int"));
	while (i < num_str.size() && isalnum(num_str[i]))
	{
		num_str[i] = std::tolower(num_str[i]);
		digit = std::string(digit_char).find(num_str[i]);
		digit *= sign;
		num *= base;
		num += digit;
		if (num > std::numeric_limits<int>::max())
			throw (std::out_of_range("more than max int"));
		if (num < std::numeric_limits<int>::min())
			throw (std::out_of_range("less than min int"));
		i++;
	}
	if (pos != NULL)
		*pos = i;
	return (num);
}

int	stricter_unsigned_stoi(std::string num_str, size_t *pos, int base)
{
	int		num;
	size_t	local_pos;

	if (isspace(num_str[0]))
		throw (std::invalid_argument("can't be preceded by space."));
	if (num_str[0] == '-' || num_str[0] == '+')
		throw (std::invalid_argument("can't contain sign"));
	num = stoi(num_str, &local_pos, base);
	if ((size_t)pos == std::string::npos && local_pos != num_str.size())
		throw (std::invalid_argument("not a int"));
	if (pos != NULL)
		*pos = local_pos;
	return (num);
}


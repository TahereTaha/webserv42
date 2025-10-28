#pragma once

#include <string>

#define digit_char	"0123456789abcdefghijklmnopqrstuvwxyz"


int	stoi(std::string num_str, size_t *pos = 0, int base = 10);

int	stricter_unsigned_stoi(std::string num_str, size_t *pos = 0, int base = 10);


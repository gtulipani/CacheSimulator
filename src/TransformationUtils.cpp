#include <ios>
#include <sstream>
#include <algorithm>
#include <string>
#include "TransformationUtils.h"

bool str_to_bool(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::istringstream is(str);
	bool b;
	is >> std::boolalpha >> b;
	return b;
}

unsigned long hex_to_ulong(std::string hex) {
	return std::stoul(hex, nullptr, 16);
}

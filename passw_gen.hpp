#pragma once
#include <string>

class PasswordGenerator {
	int max_c;
	std::string symbols;

public:
	PasswordGenerator(int max_characters)
		: max_c(max_characters) {
		symbols = "abcdefghijklmnopqrstuvwxyz";
	}

	std::string Generate(int idx);
};
#pragma once
#include <string>

class PasswordGenerator {
	int max_c;

public:
	PasswordGenerator(int max_characters)
		: max_c(max_characters) {
		
	}

	std::string Generate(int idx);

	static std::string GetSymbols() {
		return "abcdefghijklmnopqrstuvwxyz";
	}
};
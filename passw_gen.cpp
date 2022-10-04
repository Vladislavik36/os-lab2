#include "passw_gen.hpp"

std::string PasswordGenerator::Generate(int idx)
{
	std::string out;
	auto symbols = GetSymbols();
	for (int i = 0; i < max_c; i++)
	{
		out += symbols[idx % symbols.size()];
		idx /= (symbols.size());
	}
	std::reverse(out.begin(), out.end());
	return out;
}

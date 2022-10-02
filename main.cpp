#include <iostream>
#include <vector>
#include <chrono>

#include "cracker.hpp"
#include "hashers.hpp"

void CrackSha256() {
	auto start_t = std::chrono::steady_clock::now();

	std::vector<std::string> hashes = {
		"1115dd800feaacefdf481f1f9070374a2a81e27880f187396db67958b207cbad",
		"3a7bd3e2360a3d29eea436fcfb7e44c735d117c42d1c1835420b6b9942dd4f1b",
		"74e1bb62f8dabb8125a58852b63bdf6eaef667cb56ac7f7cdba6d7305c50a22f"
	};

	std::cout << "Enter threads count for sha256: " << std::endl;
	int n_threads = 0;
	std::cin >> n_threads;

	HashCracker<Sha256Hasher> cracker;
	cracker.Crack(hashes, n_threads);

	auto end_t = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t);

	std::cout << "elapsed: " << elapsed.count() << "ms" << std::endl;
}

int main() {
	CrackSha256();
	return 0;
}
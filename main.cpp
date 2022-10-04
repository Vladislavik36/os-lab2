#include <iostream>
#include <vector>
#include <chrono>

#include "cracker.hpp"
#include "hashers.hpp"

void CrackSha256() {
	std::vector<std::string> hashes = {
		"1115dd800feaacefdf481f1f9070374a2a81e27880f187396db67958b207cbad",
		"3a7bd3e2360a3d29eea436fcfb7e44c735d117c42d1c1835420b6b9942dd4f1b",
		"74e1bb62f8dabb8125a58852b63bdf6eaef667cb56ac7f7cdba6d7305c50a22f"
	};

	std::cout << "Enter threads count for SHA256: " << std::endl;
	int n_threads = 0;
	std::cin >> n_threads;

	if (n_threads == 0)
		throw std::runtime_error("You should enter threads more then 0.");

	auto max_threads = std::thread::hardware_concurrency();
	if (n_threads > std::thread::hardware_concurrency())
		throw std::runtime_error("You should enter threads less or equal " + std::to_string(max_threads) + ".");

	auto start_t = std::chrono::steady_clock::now();
	auto cracker = HashCracker<Sha256Hasher>(5);
	cracker.Crack(hashes, n_threads);

	auto end_t = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t);

	std::cout << "elapsed: " << elapsed.count() << "ms" << std::endl;
}

void CrackMD5() {
	std::vector<std::string> hashes = {
		"81d45c9cf678fbaa8d64a6f29a6f97e3",
		"1f3870be274f6c49b3e31a0c6728957f",
		"d9308f32f8c6cf370ca5aaaeafc0d49b"
	};

	std::cout << "Enter threads count for MD5: " << std::endl;
	int n_threads = 0;
	std::cin >> n_threads;

	if (n_threads == 0)
		throw std::runtime_error("You should enter threads more then 0.");

	auto max_threads = std::thread::hardware_concurrency();
	if (n_threads > std::thread::hardware_concurrency())
		throw std::runtime_error("You should enter threads less or equal " + std::to_string(max_threads) + ".");

	auto start_t = std::chrono::steady_clock::now();
	auto cracker = HashCracker<MD5Hasher>(5);
	cracker.Crack(hashes, n_threads);

	auto end_t = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t);

	std::cout << "elapsed: " << elapsed.count() << "ms" << std::endl;
}

int main() {
	try {
		CrackSha256();
		CrackMD5();
	}
	catch (std::runtime_error ex) {
		std::cout << "Error occured: " << ex.what() << std::endl;
	}
	return 0;
}
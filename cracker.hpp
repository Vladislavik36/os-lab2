#pragma once

#include <vector>
#include <atomic>
#include <iostream>
#include <thread>

#include "hashers.hpp"
#include "passw_gen.hpp"

template<class T>
class HashCracker {
	std::vector<std::thread> threads;
	std::atomic<bool> found;

	void CrackInternal(const std::string& hash, int from, int to);
public:
	void Crack(const std::vector<std::string>& hashes, int n_threads);

	HashCracker();
	~HashCracker();
};

template<class T>
void HashCracker<T>::CrackInternal(const std::string& hash, int from, int to)
{
	PasswordGenerator gen(5);
	T hasher;

	for (int i = from; i < to; i++) {
		auto generated = gen.Generate(i);

		if (hasher.Verify(generated, hash))
		{
			std::cout << "found password for hash \"" << hash << "\" :" << generated << std::endl;
			found.store(true);
			break;
		}
		else if (found.load())
			break;
	}
}

template<class T>
void HashCracker<T>::Crack(const std::vector<std::string>& hashes, int n_threads)
{
	int max_n = static_cast<int>(std::pow(26, 5)) - 1;
	int per_thread = max_n / n_threads;

	for (const auto& h : hashes) {
		std::cout << "Finding password for hash \"" << h << "\"" << std::endl;
		int start_on = 0;

		for (int i = 0; i < n_threads; i++) {
			int end_on = start_on + per_thread;
			threads.emplace_back(std::thread(&HashCracker::CrackInternal, this, h, start_on, end_on));
			start_on = end_on;
		}

		for (auto& t : threads) {
			if (t.joinable())
				t.join();
		}
		threads.clear();
		found.store(false);
	}
}

template<class T>
HashCracker<T>::~HashCracker()
{
	for (auto& t : threads) {
		if (t.joinable())
			t.join();
	}
}

template<class T>
HashCracker<T>::HashCracker() : found(false)
{
}

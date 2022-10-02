#pragma once
#include <string>

// CryptoPP includes
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

class Hasher {
public:
	virtual bool Verify(const std::string_view msg, const std::string_view hex_digest) = 0;
	virtual std::string Hash(const std::string_view msg) = 0;
};

class Sha256Hasher : public Hasher {
private:
	CryptoPP::SHA256 hash;
public:
	virtual bool Verify(const std::string_view msg, const std::string_view hex_digest)
		override;

	virtual std::string Hash(const std::string_view msg) override;
};
#pragma once
#include <string>

// CryptoPP includes
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/md5.h"
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

class MD5Hasher : public Hasher {
	CryptoPP::Weak::MD5 hash;
public:
	virtual bool Verify(const std::string_view msg, const std::string_view hex_digest)
		override;

	virtual std::string Hash(const std::string_view msg) override;
};
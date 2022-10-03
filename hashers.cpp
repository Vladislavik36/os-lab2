#include "hashers.hpp"

inline std::string HexToDigest(const std::string_view hex_digest) {
	std::string digest;
	CryptoPP::HexDecoder decoder;
	decoder.Put((CryptoPP::byte*)hex_digest.data(), hex_digest.size());
	decoder.MessageEnd();

	auto size = decoder.MaxRetrievable();
	if (size && size <= SIZE_MAX)
	{
		digest.resize(size);
		decoder.Get((CryptoPP::byte*)&digest[0], digest.size());
	}
	return digest;
}

bool Sha256Hasher::Verify(const std::string_view msg, const std::string_view hex_digest)
{
	auto digest = HexToDigest(hex_digest);
	hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
	return hash.Verify((const CryptoPP::byte*)digest.data());
}

std::string Sha256Hasher::Hash(const std::string_view msg)
{
	std::string hex;
	CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hex));

	std::string digest;

	hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);

	CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));

	return hex;
}

bool MD5Hasher::Verify(const std::string_view msg, const std::string_view hex_digest)
{
	auto digest = HexToDigest(hex_digest);
	hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
	return hash.Verify((const CryptoPP::byte*)digest.data());
}

std::string MD5Hasher::Hash(const std::string_view msg)
{
	std::string hex;
	CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hex));

	std::string digest;

	hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoPP::byte*)&digest[0]);

	CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));

	return hex;
}

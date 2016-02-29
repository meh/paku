#include "packet/ip"

namespace paku {
	namespace packet {
		std::string
		ip::address(const in_addr* addr)
		{
			std::ostringstream ss;

			ss << ( addr->s_addr        & 0xff) << '.';
			ss << ((addr->s_addr >> 8)  & 0xff) << '.';
			ss << ((addr->s_addr >> 16) & 0xff) << '.';
			ss << ((addr->s_addr >> 24) & 0xff);

			return ss.str();
		}

		uint16_t
		ip::checksum(const void* dat, size_t length)
		{
			const char*  data   = reinterpret_cast<const char*>(dat);
			uint64_t     acc    = 0xffff;
			unsigned int offset = reinterpret_cast<uintptr_t>(data) & 3;

			if (offset) {
				size_t count = 4 - offset;

				if (count > length) {
					count = length;
				}

				uint32_t word = 0;
				std::memcpy(offset + reinterpret_cast<char*>(&word), data, count);

				acc    += ntohl(word);
				data   += count;
				length -= count;
			}

			const char* end = data + (length & ~3);
			while (data != end) {
				uint32_t word;
				std::memcpy(&word, data, 4);

				acc  += ntohl(word);
				data += 4;
			}

			length &= 3;

			if (length) {
				uint32_t word = 0;
				std::memcpy(&word, data, length);

				acc += ntohl(word);
			}

			acc = (acc & 0xffffffff) + (acc >> 32);
			while (acc >> 16) {
				acc = (acc & 0xffff) + (acc >> 16);
			}

			if (offset & 1) {
				acc = ((acc & 0xff00) >> 8) | ((acc & 0x00ff) << 8);
			}

			return htons(~acc);
		}

		uint8_t
		ip::version() const
		{
			return packet->version_and_header >> 4;
		}

		uint8_t
		ip::header() const
		{
			return packet->version_and_header & 0xf;
		}

		uint8_t
		ip::dscp() const
		{
			return packet->dscp_and_ecn >> 2;
		}

		uint8_t
		ip::ecn() const
		{
			return packet->dscp_and_ecn & 0x3;
		}

		uint16_t
		ip::length() const
		{
			return ntohs(packet->length);
		}

		uint16_t
		ip::id() const
		{
			return ntohs(packet->id);
		}

		uint16_t
		ip::flags() const
		{
			return ntohs(packet->flags_and_offset) >> 13;
		}

		uint16_t
		ip::offset() const
		{
			return ntohs(packet->flags_and_offset) & 0x1fff;
		}

		uint8_t
		ip::ttl() const
		{
			return packet->ttl;
		}

		enum ip::protocol
		ip::protocol() const
		{
			return static_cast<enum ip::protocol>(packet->protocol);
		}

		uint16_t
		ip::checksum() const
		{
			return packet->checksum;
		}

		std::string
		ip::source() const
		{
			return ip::address(&packet->source);
		}

		std::string
		ip::destination() const
		{
			return ip::address(&packet->destination);
		}
	}
}

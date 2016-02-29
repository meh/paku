#include <paku/packet/ether>

namespace paku {
	namespace packet {
		std::string
		ether::address(const uint8_t* addr)
		{
			std::ostringstream ss;

			ss << std::hex << std::setfill('0');

			for (int i = 1; i < ADDR_LEN; i++) {
				ss << std::setw(2) << static_cast<unsigned>(addr[i - 1]) << ':';
			}

			ss << std::setw(2) << static_cast<unsigned>(addr[ADDR_LEN - 1]);

			return ss.str();
		};

		std::string
		ether::destination() const
		{
			return ether::address(packet->destination);
		}

		std::string
		ether::source() const
		{
			return ether::address(packet->source);
		}

		enum ether::type
		ether::type() const
		{
			return static_cast<enum ether::type>(ntohs(packet->type));
		}
	}
}

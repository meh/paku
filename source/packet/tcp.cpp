#include "packet/tcp"

namespace paku {
	namespace packet {
		uint16_t
		tcp::source() const
		{
			return ntohs(packet->source);
		}

		uint16_t
		tcp::destination() const
		{
			return ntohs(packet->destination);
		}

		uint32_t
		tcp::sequence() const
		{
			return ntohl(packet->sequence);
		}

		uint32_t
		tcp::acknowledgement() const
		{
			return ntohl(packet->acknowledgement);
		}

		uint8_t
		tcp::offset() const
		{
			return ntohs(packet->offset_and_flags) >> 12;
		}

		std::bitset<6>
		tcp::flags() const
		{
			return ntohs(packet->offset_and_flags) & 0x3f;
		}

		bool
		tcp::urg() const
		{
			return flags().test(5);
		}

		bool
		tcp::ack() const
		{
			return flags().test(4);
		}

		bool
		tcp::psh() const
		{
			return flags().test(3);
		}

		bool
		tcp::rst() const
		{
			return flags().test(2);
		}

		bool
		tcp::syn() const
		{
			return flags().test(1);
		}

		bool
		tcp::fin() const
		{
			return flags().test(0);
		}

		uint16_t
		tcp::window() const
		{
			return ntohs(packet->window);
		}

		uint16_t
		tcp::checksum() const
		{
			return ntohs(packet->checksum);
		}

		uint16_t
		tcp::urgent() const
		{
			return ntohs(packet->urgent);
		}

		const char*
		tcp::data() const
		{
			return reinterpret_cast<const char*>(packet) + (offset() * 4);
		}
	}
}

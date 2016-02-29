#include "packet/ether"
#include "packet/arp"
#include "packet/ip"

namespace paku {
	namespace packet {
		enum arp::hardware
		arp::hardware() const
		{
			return static_cast<enum arp::hardware>(ntohs(packet->hardware_type));
		}

		enum arp::protocol
		arp::protocol() const
		{
			return static_cast<enum arp::protocol>(ntohs(packet->protocol_type));
		}

		enum arp::operation
		arp::operation() const
		{
			return static_cast<enum arp::operation>(ntohs(packet->operation));
		}

		arp::result
		arp::sender() const
		{
			return part(reinterpret_cast<const uint8_t*>(packet->payload));

		}

		arp::result
		arp::target() const
		{
			return part(reinterpret_cast<const uint8_t*>(packet->payload)
				+ packet->hardware_length + packet->protocol_length);
		}

		arp::result
		arp::part(const uint8_t* pointer) const
		{
			arp::result::type hardware;
			arp::result::type protocol;

			switch (this->hardware()) {
				case arp::ETHERNET:
					hardware = ether::address(pointer);
					break;

				default:
					hardware = std::vector<uint8_t>(pointer, pointer + packet->hardware_length);
			}

			pointer += packet->hardware_length;

			switch (this->protocol()) {
				case arp::IPv4:
					protocol = ip::address(reinterpret_cast<const in_addr*>(pointer));
					break;

				default:
					protocol = std::vector<uint8_t>(pointer, pointer + packet->protocol_length);
			}

			return { hardware, protocol };
		}
	}
}

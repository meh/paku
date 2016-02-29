#include <paku/packet/ip>
#include <paku/packet/icmp>

namespace paku {
	namespace packet {
		uint16_t
		icmp::echo::identifier() const
		{
			return ntohs(packet->identifier);
		}

		uint16_t
		icmp::echo::sequence() const
		{
			return ntohs(packet->sequence);
		}

		const char*
		icmp::echo::data() const
		{
			return packet->data;
		}

		uint16_t
		icmp::timestamp::identifier() const
		{
			return ntohs(packet->identifier);
		}

		uint16_t
		icmp::timestamp::sequence() const
		{
			return ntohs(packet->sequence);
		}

		uint32_t
		icmp::timestamp::originate() const
		{
			return ntohl(packet->originate);
		}

		uint32_t
		icmp::timestamp::receive() const
		{
			return ntohl(packet->receive);
		}

		uint32_t
		icmp::timestamp::transmit() const
		{
			return ntohl(packet->transmit);
		}

		uint16_t
		icmp::information::identifier() const
		{
			return ntohs(packet->identifier);
		}

		uint16_t
		icmp::information::sequence() const
		{
			return ntohs(packet->sequence);
		}

		uint8_t
		icmp::parameter_problem::pointer() const
		{
			return packet->pointer;
		}

		ip
		icmp::parameter_problem::header() const
		{
			return reinterpret_cast<const ip::raw*>(packet->payload);
		}

		const char*
		icmp::parameter_problem::data() const
		{
			return packet->payload + (header().header() * 4);
		}

		std::string
		icmp::redirect_message::gateway() const
		{
			return ip::address(&packet->gateway);
		}

		ip
		icmp::redirect_message::header() const
		{
			return reinterpret_cast<const ip::raw*>(packet->payload);
		}

		const char*
		icmp::redirect_message::data() const
		{
			return packet->payload + (header().header() * 4);
		}

		ip
		icmp::previous::header() const
		{
			return reinterpret_cast<const ip::raw*>(packet->payload);
		}

		const char*
		icmp::previous::data() const
		{
			return packet->payload + (header().header() * 4);
		}

		enum icmp::type
		icmp::type() const
		{
			return static_cast<enum icmp::type>(packet->type);
		}

		template<>
		icmp::code::destination_unreachable
		icmp::code() const
		{
			if (type() != icmp::DESTINATION_UNREACHABLE) {
				throw std::domain_error("wrong packet type");
			}

			return static_cast<enum icmp::code::destination_unreachable>(packet->code);
		}

		template<>
		icmp::code::redirect_message
		icmp::code() const
		{
			if (type() != icmp::REDIRECT_MESSAGE) {
				throw std::domain_error("wrong packet type");
			}

			return static_cast<enum icmp::code::redirect_message>(packet->code);
		}

		template<>
		icmp::code::parameter_problem
		icmp::code() const
		{
			if (type() != icmp::PARAMETER_PROBLEM) {
				throw std::domain_error("wrong packet type");
			}

			return static_cast<enum icmp::code::parameter_problem>(packet->code);
		}

		uint16_t
		icmp::checksum() const
		{
			return ntohs(packet->checksum);
		}

		template<>
		icmp::echo
		icmp::details() const
		{
			if (type() != icmp::ECHO_REQUEST && type() != icmp::ECHO_REPLY) {
				throw std::domain_error("wrong packet type");
			}

			return reinterpret_cast<const icmp::echo::raw*>(
				reinterpret_cast<const char*>(packet) + sizeof(icmp::raw));
		}

		template<>
		icmp::timestamp
		icmp::details() const
		{
			if (type() != icmp::TIMESTAMP_REQUEST && type() != icmp::TIMESTAMP_REPLY) {
				throw std::domain_error("wrong packet type");
			}

			return reinterpret_cast<const icmp::timestamp::raw*>(
				reinterpret_cast<const char*>(packet) + sizeof(icmp::raw));
		}

		template<>
		icmp::information
		icmp::details() const
		{
			if (type() != icmp::INFORMATION_REQUEST && type() != icmp::INFORMATION_REPLY) {
				throw std::domain_error("wrong packet type");
			}

			return reinterpret_cast<const icmp::information::raw*>(
				reinterpret_cast<const char*>(packet) + sizeof(icmp::raw));
		}

		template<>
		icmp::parameter_problem
		icmp::details() const
		{
			if (type() != icmp::PARAMETER_PROBLEM) {
				throw std::domain_error("wrong packet type");
			}

			return reinterpret_cast<const icmp::parameter_problem::raw*>(
				reinterpret_cast<const char*>(packet) + sizeof(icmp::raw));
		}

		template<>
		icmp::redirect_message
		icmp::details() const
		{
			if (type() != icmp::REDIRECT_MESSAGE) {
				throw std::domain_error("wrong packet type");
			}

			return reinterpret_cast<const icmp::redirect_message::raw*>(
				reinterpret_cast<const char*>(packet) + sizeof(icmp::raw));
		}

		template<>
		icmp::previous
		icmp::details() const
		{
			if (type() != icmp::SOURCE_QUENCH &&
			    type() != icmp::DESTINATION_UNREACHABLE &&
			    type() != icmp::TIME_EXCEEDED &&
			    type() != icmp::PARAMETER_PROBLEM &&
			    type() != icmp::REDIRECT_MESSAGE)
			{
				throw std::domain_error("wrong packet type");
			}

			return reinterpret_cast<const icmp::previous::raw*>(
				reinterpret_cast<const char*>(packet) + sizeof(icmp::raw));
		}
	}

	optional<std::string>
	to_string(enum packet::icmp::type type)
	{
		switch (type) {
			case packet::icmp::ECHO_REPLY:
				return std::string("echo-reply");

			case packet::icmp::DESTINATION_UNREACHABLE:
				return std::string("destination-unreachable");

			case packet::icmp::SOURCE_QUENCH:
				return std::string("source-quench");

			case packet::icmp::REDIRECT_MESSAGE:
				return std::string("redirect-message");

			case packet::icmp::ECHO_REQUEST:
				return std::string("echo-request");

			case packet::icmp::ROUTER_ADVERTISEMENT:
				return std::string("router-advertisement");

			case packet::icmp::ROUTER_SOLICITATION:
				return std::string("router-solicitation");

			case packet::icmp::TIME_EXCEEDED:
				return std::string("time-exceeded");

			case packet::icmp::PARAMETER_PROBLEM:
				return std::string("parameter-problem");

			case packet::icmp::TIMESTAMP_REQUEST:
				return std::string("timestamp-request");

			case packet::icmp::TIMESTAMP_REPLY:
				return std::string("timestamp-reply");

			case packet::icmp::INFORMATION_REQUEST:
				return std::string("information-request");

			case packet::icmp::INFORMATION_REPLY:
				return std::string("information-reply");

			case packet::icmp::ADDRESS_MASK_REQUEST:
				return std::string("address-mask-request");

			case packet::icmp::ADDRESS_MASK_REPLY:
				return std::string("address-mask-reply");

			case packet::icmp::TRACEROUTE:
				return std::string("traceroute");

			default:
				return nullopt;
		}
	}

	optional<std::string>
	to_string(enum packet::icmp::code::destination_unreachable code)
	{
		switch (code) {
			case packet::icmp::code::DESTINATION_NETWORK_UNREACHABLE:
				return std::string("destination-network-unreachable");

			case packet::icmp::code::DESTINATION_HOST_UNREACHABLE:
				return std::string("destination-host-unreachable");

			case packet::icmp::code::DESTINATION_PROTOCOL_UNREACHABLE:
				return std::string("destination-protocol-unreachable");

			case packet::icmp::code::DESTINATION_PORT_UNREACHABLE:
				return std::string("destination-port-unreachable");

			case packet::icmp::code::FRAGMENTATION_REQUIRED:
				return std::string("fragmentation-required");

			case packet::icmp::code::SOURCE_ROUTE_FAILED:
				return std::string("source-route-failed");

			case packet::icmp::code::DESTINATION_NETWORK_UNKNOWN:
				return std::string("destination-network-unknown");

			case packet::icmp::code::DESTINATION_HOST_UNKNOWN:
				return std::string("destination-host-unknown");

			case packet::icmp::code::SOURCE_HOST_ISOLATED:
				return std::string("source-host-isolated");

			case packet::icmp::code::NETWORK_ADMINISTRATIVELY_PROHIBITED:
				return std::string("network-administratively-prohibited");

			case packet::icmp::code::HOST_ADMINISTRATIVELY_PROHIBITED:
				return std::string("host-administratively-prohibited");

			case packet::icmp::code::NETWORK_UNREACHABLE_FOR_TOS:
				return std::string("network-unreachable-for-tos");

			case packet::icmp::code::HOST_UNREACHABLE_FOR_TOS:
				return std::string("host-unreachable-for-tos");

			case packet::icmp::code::COMMUNICATION_ADMINISTRATIVELY_PROHIBITED:
				return std::string("communication-administratively-prohibited");

			case packet::icmp::code::HOST_PRECEDENCE_VIOLATION:
				return std::string("host-precedence-violation");

			case packet::icmp::code::PRECEDENT_CUTOFF_IN_EFFECT:
				return std::string("precedent-cutoff-in-effect");

			default:
				return nullopt;
		}
	}

	optional<std::string>
	to_string(enum packet::icmp::code::redirect_message code)
	{
		switch (code) {
			case packet::icmp::code::REDIRECT_DATAGRAM_FOR_NETWORK:
				return std::string("redirect-datagram-for-network");

			case packet::icmp::code::REDIRECT_DATAGRAM_FOR_HOST:
				return std::string("redirect-datagram-for-host");

			case packet::icmp::code::REDIRECT_DATAGRAM_FOR_TOS_AND_NETWORK:
				return std::string("redirect-datagram-for-tos-and-network");

			case packet::icmp::code::REDIRECT_DATAGRAM_FOR_TOS_AND_HOST:
				return std::string("redirect-datagram-for-tos-and-host");

			default:
				return nullopt;
		}
	}

	optional<std::string>
	to_string(enum packet::icmp::code::parameter_problem code)
	{
		switch (code) {
			case packet::icmp::code::POINTER_INDICATES_ERROR:
				return std::string("pointer-indicates-error");

			case packet::icmp::code::MISSING_REQUIRED_OPTION:
				return std::string("missing-required-option");

			case packet::icmp::code::BAD_LENGTH:
				return std::string("bad-length");

			default:
				return nullopt;
		}
	}
}

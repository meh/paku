#include <cstddef>
#include <amirite>

#include <paku/packet/limits>

using namespace paku;

int
main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	return amirite("packet/limits", {
		{ "ether", []{
			amiequal(packet::limits<packet::ether>::max(), 14U);
			amiequal(packet::limits<packet::ether>::min(), 14U);
		}},

		{ "arp", []{
			amiequal(packet::limits<packet::arp>::min(), 28U);
			amiequal(packet::limits<packet::arp>::max(), 28U);
		}},

		{ "ip", []{
			amiequal(packet::limits<packet::ip>::min(), 20U);
			amiequal(packet::limits<packet::ip>::max(), 60U);
		}},

		{ "icmp", []{
			amiequal(packet::limits<packet::icmp>::min(), 8U);
			amiequal(packet::limits<packet::icmp>::max(), 76U);
		}},

		{ "tcp", []{
			amiequal(packet::limits<packet::tcp>::min(), 20U);
			amiequal(packet::limits<packet::tcp>::max(), 60U);
		}},
	});
}

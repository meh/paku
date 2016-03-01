#include <cstddef>
#include <amirite>
#include <paku/layer>

using namespace paku;

int
main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	return amirite("layer", {
		{ "ether", []{
			amithrown([]{
				layer<packet::ether> test(NULL, 0);
			});

			amiokay([]{
				layer<packet::ether> test(NULL, 14);
			});
		}},

		{ "ip", []{
			amithrown([]{
				layer<packet::ip> test(NULL, 0);
			});
		}},

		{ "icmp", []{
			amithrown([]{
				layer<packet::icmp> test(NULL, 3);
			});
		}},

		{ "tcp", []{
			amithrown([]{
				layer<packet::tcp> test(NULL, 12);
			});
		}},
	});
}

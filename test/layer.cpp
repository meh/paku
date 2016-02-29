#include <cstddef>
#include <amirite>
#include <paku/layer>

int
main (int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	return amirite("layer", {
		{ "ether", []{
			amithrown([]{
				paku::layer<paku::packet::ether> test(NULL, 0);
			});

			amiokay([]{
				paku::layer<paku::packet::ether> test(NULL, 14);
			});
		}},
	});
}

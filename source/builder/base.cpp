#include <paku/builder/base>

namespace paku {
	namespace builder {
		base::base(std::shared_ptr<builder::buffer> buf)
		{
			_buffer = buf;
		}

		base::base() : base(std::shared_ptr<builder::buffer>(new builder::buffer))
		{ }

		std::shared_ptr<builder::buffer>
		base::buffer()
		{
			return _buffer;
		}
	}
}

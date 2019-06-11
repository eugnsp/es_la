#include <mkl_service.h>

namespace es_la::internal
{
[[gnu::destructor]] void mkl_destructor()
{
	::mkl_free_buffers();
}
}

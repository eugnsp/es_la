#pragma once

namespace es_la::internal
{
void mkl_destructor();

[[gnu::used]] inline void mkl_destructor_dummy()
{
	auto force_include = mkl_destructor;
	(void)force_include;
}
}

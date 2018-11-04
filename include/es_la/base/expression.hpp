#pragma once
#include "traits.hpp"
#include "expr_base.hpp"

namespace la
{
template<class T_Derived>
class Expression : public internal::Expr_base<T_Derived, typename internal::Traits<T_Derived>::Access_tag>
{ };
}

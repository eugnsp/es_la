#pragma once

#if __has_include(<boost/type_index.hpp>)
	#include <boost/type_index.hpp>
#endif

#include <regex>
#include <string>
#include <typeinfo>

template<typename T>
std::string type_string()
{
	std::string str;
#if __has_include(<boost/type_index.hpp>)
	str = boost::typeindex::type_id_with_cvr<T>().pretty_name();
#else
	str = typeid(T).name();
#endif
	str = std::regex_replace(str, std::regex{"es_la::(internal::)?"}, "");
	str = std::regex_replace(str, std::regex{"\\(Dynamic_extent\\)0"}, "dynamic");
	return str;
}

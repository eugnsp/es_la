#pragma once
#include <es_la/io/la_file.hpp>
#include <es_la/dense.hpp>
#include <es_util/time.hpp>
#include <cassert>
#include <cstddef>
#include <string>
#include <fstream>

namespace la
{
class La_file_reader
{
public:
	explicit La_file_reader(const std::string& file_name)
	{
		file_.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		file_.open(file_name, std::ios_base::binary);

		read_header();
	}

	template<typename T, std::size_t rows, std::size_t cols>
	void read(Matrix<T, rows, cols>& matrix)
	{
		std::uint32_t l, r, c;
		read_raw(l);
		file_.seekg(l, std::ios_base::cur);

		read_raw(r);
		read_raw(c);

		assert(matrix.rows() == r && matrix.cols() == c);
		file_.read(reinterpret_cast<char*>(matrix.data()), matrix.size() * sizeof(T));
	}

	void close()
	{
		file_.close();
	}

private:
	template<typename T>
	void read_raw(T& x)
	{
		file_.read(reinterpret_cast<char*>(&x), sizeof(T));
	}

	void read_header()
	{
		file_.seekg(la_file_header_length);

		std::uint32_t version;
		read_raw(version);
		assert(version == 1);
	}

private:
	std::ifstream file_;
};
} // namespace la
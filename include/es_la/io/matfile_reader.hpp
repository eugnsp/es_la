#pragma once
#include <es_la/io/matfile_base.hpp>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>

namespace es_la
{
class Matfile_reader : private internal::Matfile_base
{
public:
	explicit Matfile_reader(const std::string& file_name)
	{
		file_.open(file_name, std::ofstream::binary);
		if (!file_)
			throw std::runtime_error("MAT-file '" + file_name + "' cannot be opened for reading");

		read_header();
	}

	const std::string& header_text() const
	{
		return header_text_;
	}

	std::string read_string(const std::string& var_name)
	{}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void read(const std::string& var_name, T& scalar)
	{
		file_.seekg(sizeof(Header));

		while (true)
		{
			Tag tag;
			read_raw(tag);
			if (!file_)
				break;

			switch (tag.data_type)
			{
			case internal::Matfile_data_types::MATRIX:
				//				read_array_flags_subelement();
				break;

			default:
				file_.seekg(tag.n_bytes, std::ifstream::cur);
			}
		}
	}

	template<class T, std::size_t rows, std::size_t cols>
	void read(const std::string& var_name, const Matrix<T, rows, cols>& matrix)
	{}

	void close()
	{
		file_.close();
	}

private:
	template<typename T>
	void read_raw(T& data)
	{
		file_.read(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<typename T>
	void read_raw(T* data, std::size_t n_elements)
	{
		file_.read(reinterpret_cast<char*>(data), n_elements * sizeof(T));
	}

	void read_header()
	{
		Header header;
		read_raw(header);
		if (!file_)
			throw std::runtime_error("Error while reading MAT-file");

		if (header.version != 0x0100)
			throw std::runtime_error("Unsupported MAT-file version");
		if (header.endian != (('M' << 8) | 'I'))
			throw std::runtime_error("Unsupported MAT-file endianness");

		header_text_.assign(header.text, sizeof(header.text));
		header_text_.erase(
			std::find_if(
				header_text_.rbegin(), header_text_.rend(), [](char ch) { return ch != ' '; })
				.base(),
			header_text_.end());
	}

	void read_array_flags_subelement(
		internal::Matfile_class_types& class_type, Flags& flags, std::size_t& nnz)
	{
		Array_flags array_flags;
		read_raw(array_flags);
		if (!file_)
			throw std::runtime_error("Error while reading MAT-file");

		class_type = static_cast<internal::Matfile_class_types>(array_flags.class_type);
		flags.from_uint8(array_flags.flags);
		//		nnz
		// 		array_flags.class_type = static_cast<std::uint8_t>(class_type);
		// 		array_flags.nnz = static_cast<std::uint32_t>(nnz);
		// 		array_flags.flags = 0;
		// 		if (is_complex)
		// 			array_flags.flags |= complex_flag;
	}

private:
	static constexpr std::size_t padding_size = 8;

	std::ifstream file_;
	std::string header_text_;
};
} // namespace la

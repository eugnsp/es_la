#pragma once
#include <cstdint>

namespace la::internal
{
enum class Matfile_data_types : std::uint32_t
{
	INT8 = 1,
	UINT8 = 2,
	INT16 = 3,
	UINT16 = 4,
	INT32 = 5,
	UINT32 = 6,
	INT64 = 12,
	UINT64 = 13,
	SINGLE = 7,
	DOUBLE = 9,
	MATRIX = 14,
	COMPRESSED = 15,
	UTF8 = 16,
	UTF16 = 17,
	UTF32 = 18
};

template<typename>
struct Matfile_data_type;
template<>
struct Matfile_data_type<char>
{
	static constexpr auto value = Matfile_data_types::UTF8;
};
template<>
struct Matfile_data_type<signed char>
{
	static constexpr auto value = Matfile_data_types::INT8;
};
template<>
struct Matfile_data_type<unsigned char>
{
	static constexpr auto value = Matfile_data_types::UINT8;
};
template<>
struct Matfile_data_type<std::int16_t>
{
	static constexpr auto value = Matfile_data_types::INT16;
};
template<>
struct Matfile_data_type<std::uint16_t>
{
	static constexpr auto value = Matfile_data_types::UINT16;
};
template<>
struct Matfile_data_type<std::int32_t>
{
	static constexpr auto value = Matfile_data_types::INT32;
};
template<>
struct Matfile_data_type<std::uint32_t>
{
	static constexpr auto value = Matfile_data_types::UINT32;
};
template<>
struct Matfile_data_type<std::int64_t>
{
	static constexpr auto value = Matfile_data_types::INT64;
};
template<>
struct Matfile_data_type<std::uint64_t>
{
	static constexpr auto value = Matfile_data_types::UINT64;
};
template<>
struct Matfile_data_type<float>
{
	static constexpr auto value = Matfile_data_types::SINGLE;
};
template<>
struct Matfile_data_type<double>
{
	static constexpr auto value = Matfile_data_types::DOUBLE;
};

// MAT-file class types
enum class Matfile_class_types : std::uint8_t
{
	CELL = 1,
	STRUCT = 2,
	OBJECT = 3,
	CHAR = 4,
	SPARSE = 5,
	DOUBLE = 6,
	SINGLE = 7,
	INT8 = 8,
	UINT8 = 9,
	INT16 = 10,
	UINT16 = 11,
	INT32 = 12,
	UINT32 = 13,
	INT64 = 14,
	UINT64 = 15
};

template<typename>
struct Matfile_class_type;
template<>
struct Matfile_class_type<std::int8_t>
{
	static constexpr auto value = Matfile_class_types::INT8;
};
template<>
struct Matfile_class_type<std::uint8_t>
{
	static constexpr auto value = Matfile_class_types::UINT8;
};
template<>
struct Matfile_class_type<std::int16_t>
{
	static constexpr auto value = Matfile_class_types::INT16;
};
template<>
struct Matfile_class_type<std::uint16_t>
{
	static constexpr auto value = Matfile_class_types::UINT16;
};
template<>
struct Matfile_class_type<std::int32_t>
{
	static constexpr auto value = Matfile_class_types::INT32;
};
template<>
struct Matfile_class_type<std::uint32_t>
{
	static constexpr auto value = Matfile_class_types::UINT32;
};
template<>
struct Matfile_class_type<std::int64_t>
{
	static constexpr auto value = Matfile_class_types::INT64;
};
template<>
struct Matfile_class_type<std::uint64_t>
{
	static constexpr auto value = Matfile_class_types::UINT64;
};
template<>
struct Matfile_class_type<float>
{
	static constexpr auto value = Matfile_class_types::SINGLE;
};
template<>
struct Matfile_class_type<double>
{
	static constexpr auto value = Matfile_class_types::DOUBLE;
};
template<>
struct Matfile_class_type<char>
{
	static constexpr auto value = Matfile_class_types::CHAR;
};

class Matfile_base
{
protected:
#pragma pack(push, 1)
	struct Header
	{
		char text[116];
		std::uint32_t reserved1;
		std::uint32_t reserved2;
		std::uint16_t version;
		std::uint16_t endian;
	};

	struct Tag
	{
		Matfile_data_types data_type;
		std::uint32_t n_bytes;
	};

	struct Array_flags
	{
		const Tag tag = {Matfile_data_types::UINT32, 8};
		std::uint8_t class_type;
		std::uint8_t flags;
		const std::uint16_t reserved = 0;
		std::uint32_t nnz;
	};

	struct Dimensions
	{
		const Tag tag = {Matfile_data_types::INT32, 8};
		std::uint32_t rows;
		std::uint32_t cols;
	};
#pragma pack(pop)

	struct Flags
	{
		bool is_complex;
		bool is_global;
		bool is_logical;

		void from_uint8(std::uint8_t flags)
		{
			is_complex = flags & complex_flag;
			is_global = flags & global_flag;
			is_logical = flags & logical_flag;
		}

		std::uint8_t to_uint8()
		{
			std::uint8_t flags = 0;
			if (is_complex)
				flags |= complex_flag;
			if (is_global)
				flags |= global_flag;
			if (is_logical)
				flags |= logical_flag;
			return flags;
		}

	private:
		static constexpr std::uint8_t logical_flag = 0b0010;
		static constexpr std::uint8_t global_flag = 0b0100;
		static constexpr std::uint8_t complex_flag = 0b1000;
	};
};

} // namespace la::internal

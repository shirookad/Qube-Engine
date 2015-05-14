#ifndef __QUBE_PROJECTDEFINES_H__
#define __QUBE_PROJECTDEFINES_H__

#pragma once

#ifdef QUBE_EXPORTS
#	define QUBE_API __declspec(dllexport)
#else
#	define QUBE_API __declspec(dllimport)
#endif

#ifdef _WIN32
#	define QUBE_OS_WINDOWS
#	ifdef _WIN64
#		define QUBE_OS_64
#	else
#		define QUBE_OS_32
#	endif
#endif

#include <cstdint>
namespace qube {
	using int8 = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;

	using uint8 = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;

	using float32 = float;
	using float64 = double;

	// 32bit or 64bit
	using sfloat = float32;
}

#define QUBE_ENUM_ELEMENT_COUNT(e) (static_cast<int32>(e::__COUNT))

#endif

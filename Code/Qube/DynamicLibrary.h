#ifndef __QUBE_DYNAMICLIBRARY_H__
#define __QUBE_DYNAMICLIBRARY_H__

#pragma once

#include "ProjectDefines.h"

#define QUBE_LIB_FUNC_DECL(name, ret, ...) using name ## _t = ret(*)(__VA_ARGS__); QUBE_API extern name ## _t name
#define QUBE_LIB_FUNC_DEF(name) name ## _t name
#define QUBE_LIB_LOAD(name, lib) name = (name ## _t)lib.loadFunction(#name)

namespace qube {
	class DynamicLibrary {
	private:
		using Handle = void *;
		Handle m_handle{ nullptr };

	public:
		using Function = void *;

		QUBE_API DynamicLibrary();
		QUBE_API DynamicLibrary(const char *name);
		QUBE_API ~DynamicLibrary();

		QUBE_API void load(const char *name);
		QUBE_API void close() noexcept;

		QUBE_API auto loadFunction(const char *name)->Function;
	};
}

#endif
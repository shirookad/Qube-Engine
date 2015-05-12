#include "stdafx.h"
#include "DynamicLibrary.h"

#include <stdexcept>

#ifdef QUBE_OS_WINDOWS
#	include <Windows.h>
#endif

namespace qube {
	DynamicLibrary::DynamicLibrary(const char *name) {
#ifdef QUBE_OS_WINDOWS
		m_handle = LoadLibraryA(name);
		if (!m_handle) { throw std::runtime_error{ std::string("Failed to load library with name \"") + name + "\"" }; }
#endif
	}

	DynamicLibrary::~DynamicLibrary() {
#ifdef QUBE_OS_WINDOWS
		if (m_handle) { FreeLibrary(static_cast<HMODULE>(m_handle)); }
#endif
	}

	auto DynamicLibrary::loadFunction(const char *name)->Function {
#ifdef QUBE_OS_WINDOWS
		return GetProcAddress(static_cast<HMODULE>(m_handle), name);
#endif
	}
}
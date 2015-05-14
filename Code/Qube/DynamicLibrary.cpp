#include "stdafx.h"
#include "DynamicLibrary.h"

#include "ErrorHandler.h"

#include <stdexcept>

#ifdef QUBE_OS_WINDOWS
#	include <Windows.h>
#endif

namespace qube {
	DynamicLibrary::DynamicLibrary() {
	}

	DynamicLibrary::DynamicLibrary(const char *name) {
		load(name);
	}

	DynamicLibrary::~DynamicLibrary() {
		close();
	}

	void DynamicLibrary::load(const char *name) {
		if (m_handle) { close(); }

#ifdef QUBE_OS_WINDOWS
		m_handle = LoadLibraryA(name);
		if (!m_handle) { QUBE_PUSH_ERROR(g_errorHandler, std::string("Failed to load library with name \"") + name + "\""); }
#endif
	}

	void DynamicLibrary::close() noexcept {
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
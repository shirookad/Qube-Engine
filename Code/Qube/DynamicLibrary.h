#ifndef __QUBE_DYNAMICLIBRARY_H__
#define __QUBE_DYNAMICLIBRARY_H__

#pragma once

#include "ProjectDefines.h"

namespace qube {
	class DynamicLibrary {
	private:
		using Handle = void *;
		Handle m_handle{ nullptr };

	public:
		using Function = void *;

		QUBE_API DynamicLibrary(const char *name);
		QUBE_API ~DynamicLibrary();

		QUBE_API auto loadFunction(const char *name)->Function;
	};
}

#endif
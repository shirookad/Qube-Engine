#ifndef __QUBE_ERRORHANDLER_H__
#define __QUBE_ERRORHANDLER_H__

#pragma once

#include "ProjectDefines.h"

#include <vector>
#include <assert.h>

namespace qube {
	struct Error {
		std::string description;
		inline Error(std::string _description) : description{ std::move(_description) } {  }
	};

	class ErrorHandler {
	private:
		std::vector<Error> m_errorStack;

	public:
		QUBE_API ErrorHandler();

		QUBE_API void push(const Error& error);
		QUBE_API void push(Error&& error);

		QUBE_API Error pop();
	};

	QUBE_API extern ErrorHandler g_errorHandler;
}

#ifdef QUBE_DEBUG
#	define QUBE_PUSH_ERROR(errh, ...) errh.push({ __VA_ARGS__ })
#else
#	define QUBE_PUSH_ERROR(...) assert(0)
#endif

#endif
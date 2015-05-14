#include "stdafx.h"
#include "ErrorHandler.h"

namespace qube {
	ErrorHandler g_errorHandler;

	ErrorHandler::ErrorHandler() {
		m_errorStack.reserve(16);
	}

	void ErrorHandler::push(const Error& error) {
		m_errorStack.push_back(error);
	}

	void ErrorHandler::push(Error&& error) {
		m_errorStack.push_back(error);
	}

	Error ErrorHandler::pop() {
		auto error = *(--m_errorStack.end());
		m_errorStack.pop_back();
		return error;
	}
}
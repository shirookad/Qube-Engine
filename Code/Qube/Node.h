#ifndef __QUBE_NODE_H__
#define __QUBE_NODE_H__

#pragma once

#include "ProjectDefines.h"

#include <string>

namespace qube {
	class Node {
	private:
		std::string m_name;

	public:
		QUBE_API Node(std::string name);

		template <class String, class = std::enable_if_t<!std::is_same<std::decay_t<String>, std::string>::value>>
		inline void setName(String&& name) noexcept(std::is_nothrow_assignable<std::string&, String>::value) { m_name = std::forward<String>(name); }

		inline const std::string& name() const { return m_name; }
	};
}

#endif
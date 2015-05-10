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

		inline const std::string& name() const { return m_name; }
	};
}

#endif
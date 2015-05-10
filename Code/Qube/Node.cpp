#include "stdafx.h"
#include "Node.h"

qube::Node::Node(std::string name)
	: m_name(std::move(name)) {
}
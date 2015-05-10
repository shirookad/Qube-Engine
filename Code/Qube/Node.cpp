#include "stdafx.h"
#include "Node.h"

namespace qube {
	Node::Node(std::string name)
		: m_name(std::move(name)) {
	}

	Node::Node(std::string name, Node *parent)
		: m_name(std::move(name))
		, m_parent(parent) {
	}

	std::shared_ptr<Node> Node::addChild(const std::string& name) {
		auto child = std::make_shared<Node>(name, this);
		m_children.push_back(child);
		return child;
	}

	std::shared_ptr<Node> Node::addChild(std::string&& name) {
		auto child = std::make_shared<Node>(name, this);
		m_children.push_back(child);
		return child;
	}

	void Node::iterateThroughChildHierarchy(std::function<void(const std::shared_ptr<Node>&)> func) const {
		for (const auto& child : m_children) {
			func(child);
			child->iterateThroughChildHierarchy(func);
		}
	}
}
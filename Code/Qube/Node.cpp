#include "stdafx.h"
#include "Node.h"

#include <stdexcept>
#include <algorithm>

namespace qube {
	Node::ConstNodeIterator Node::childIterator(const std::string& name) const {
		return std::find_if(std::begin(m_children), std::end(m_children), [name](const std::shared_ptr<Node>& child) { return child->name() == name; });
	}

	Node::NodeIterator Node::childIterator(const std::string& name) {
		return std::find_if(std::begin(m_children), std::end(m_children), [name](const std::shared_ptr<Node>& child) { return child->name() == name; });
	}

	Node::Node(std::string name)
		: m_name(std::move(name)) {
	}

	Node::Node(std::string name, Node *parent)
		: m_name(std::move(name))
		, m_parent(parent) {
	}

	Node::~Node() {
		for (const auto& child : m_children) {
			child->m_parent = nullptr;
		}
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

	void Node::removeFromParent() {
		if (!m_parent) { throw std::runtime_error(std::string("Failed to remove node \"") + m_name + "\" from parent: Node has no parent"); }
		m_parent->m_children.erase(std::find_if(std::begin(m_parent->m_children), std::end(m_parent->m_children), [this](const auto& child) { return child.get() == this; }));
		m_parent = nullptr;
	}

	std::shared_ptr<Node> Node::removeChild(const std::string& name) {
		auto childIter = childIterator(name);
		if (childIter == std::end(m_children)) throw std::runtime_error("Failed to find the given name of the child to be removed");
		auto removed = *childIter;
		removed->m_parent = nullptr;
		m_children.erase(childIter);
		return removed;
	}

	void Node::removeAllChildren() noexcept {
		for (const auto& child : m_children) { child->m_parent = nullptr; }
		m_children.clear();
	}

	std::shared_ptr<Node> Node::child(const std::string& name) const {
		auto childIter = childIterator(name);
		if (childIter == std::end(m_children)) return nullptr;
		return *childIter;
	}

	void Node::iterateThroughChildHierarchy(std::function<void(const std::shared_ptr<Node>&)> func) const {
		for (const auto& child : m_children) {
			func(child);
			child->iterateThroughChildHierarchy(func);
		}
	}
}
#ifndef __QUBE_NODE_H__
#define __QUBE_NODE_H__

#pragma once

#include "ProjectDefines.h"

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace qube {
	class Node {
	private:
		std::string m_name;
		std::vector<std::shared_ptr<Node>> m_children;
		Node *m_parent{ nullptr };

	public:
		QUBE_API Node(std::string name);
		QUBE_API Node(std::string name, Node *parent);

		QUBE_API std::shared_ptr<Node> qube::Node::addChild(const std::string& name);
		QUBE_API std::shared_ptr<Node> qube::Node::addChild(std::string&& name);

		QUBE_API void iterateThroughChildHierarchy(std::function<void(const std::shared_ptr<Node>&)> func) const;

		template <class String, class = std::enable_if_t<!std::is_same<std::decay_t<String>, std::string>::value>>
		inline void setName(String&& name) noexcept(std::is_nothrow_assignable<std::string&, String>::value) { m_name = std::forward<String>(name); }

		inline const auto& name() const { return m_name; }
		inline const auto& children() const { return m_children; }
		inline Node *parent() const { return m_parent; }
	};
}

#endif
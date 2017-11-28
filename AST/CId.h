#pragma once

#include "INode.h"
#include <memory>
#include <string>

namespace AST {

	class CId : public INode {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		CId(std::string name)
			:name(name)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		const std::string name;
	};
}
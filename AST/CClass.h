#pragma once

#include "INode.h"
#include "CVarSequence.h"
#include "CMethodSequence.h"
#include <memory>
#include <string>
#include <vector>

namespace AST {

	class CClass : public INode {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker;

	public:
		CClass(
			CId* class_name,
			CId* extends,
			CVarSequence* class_variables,
			CMethodSequence* class_methods
		)
			:name(class_name), extends_name(extends),
			variables(class_variables), methods(class_methods)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CId> name;
		std::unique_ptr<CId> extends_name;
		std::unique_ptr<CVarSequence> variables;
		std::unique_ptr<CMethodSequence> methods;
	};
}
#pragma once

#include "INode.h"
#include "CId.h"
#include "IStatement.h"
#include <memory>
#include <string>
#include <vector>

namespace AST {

	class CMain : public INode {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker;

	public:
		CMain(
			CId* class_name,
			CId* string_name,
			IStatement* state
		)
			:class_name(class_name), string_name(string_name),
			state(state)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CId> class_name;
		std::unique_ptr<CId> string_name;
		std::unique_ptr<IStatement> state;
	};
}
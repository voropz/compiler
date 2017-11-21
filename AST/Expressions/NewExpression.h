#pragma once

#include "IExpression.h"

#include <memory>

namespace AST {

	class NewExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;
		friend class Visitor::TableMaker;

	public:
		NewExpression(
			CId* left
		)
			:left(left)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CId> left;
	};
}
#pragma once

#include "IExpression.h"
#include "CId.h"
#include <memory>

namespace AST {

	class ArrayAssignStatement : public IStatement {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		ArrayAssignStatement(
			CId* left,
			IExpression* in_bracket,
			IExpression* right
		) : left(left), right(right), in_bracket(in_bracket)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> right;
		std::unique_ptr<IExpression> in_bracket;
		std::unique_ptr<CId> left;
	};
}
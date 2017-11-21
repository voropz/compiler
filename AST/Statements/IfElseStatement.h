#pragma once

#include "IExpression.h"
#include "IStatement.h"
#include <memory>

namespace AST {

	class IfElseStatement : public IStatement {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		IfElseStatement(
			IExpression* condition,
			IStatement* body_true,
			IStatement* body_false
		) : condition(condition), body_false(body_false), body_true(body_true)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> condition;
		std::unique_ptr<IStatement> body_true;
		std::unique_ptr<IStatement> body_false;
	};
}
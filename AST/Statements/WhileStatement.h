#pragma once

#include "IExpression.h"
#include "IStatement.h"
#include <memory>

namespace AST {

	class WhileStatement : public IStatement {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		WhileStatement(
			IExpression* condition,
			IStatement* body
		) : condition(condition), body(body)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> condition;
		std::unique_ptr<IStatement> body;
	};
}
#pragma once

#include "IExpression.h"
#include <memory>

namespace AST {

	class PrintStatement : public IStatement {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		PrintStatement(
			IExpression* body
		) : body(body)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> body;
	};
}
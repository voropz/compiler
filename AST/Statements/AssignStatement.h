#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include "CId.h"
#include <memory>

namespace AST {

	class AssignStatement : public IStatement {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		AssignStatement(
			CId* left,
			IExpression* right
		) : left(left), right(right)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> right;
		std::unique_ptr<CId> left;
	};
}
#pragma once

#include "IExpression.h"
#include <memory>

namespace AST {

	class AndExpression : public IExpression {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker; 
		friend class Visitor::TypeChecker;

	public:
		AndExpression(
			IExpression* left,
			IExpression* right
		)
			:left(left), right(right)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> left;
		std::unique_ptr<IExpression> right;

	};
}
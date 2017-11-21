#pragma once

#include "IExpression.h"
#include <memory>

namespace AST {

	class PlusExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		PlusExpression(
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
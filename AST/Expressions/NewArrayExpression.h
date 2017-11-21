#pragma once

#include "IExpression.h"

#include <memory>

namespace AST {

	class NewArrayExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		NewArrayExpression(
			IExpression* left
		)
			:left(left)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> left;
	};
}
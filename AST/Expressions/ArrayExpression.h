#pragma once

#include "IExpression.h"
#include <memory>

namespace AST {

	class ArrayExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		ArrayExpression(
			IExpression* left,
			IExpression* element
		)
			:left(left), element(element)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> left;
		std::unique_ptr<IExpression> element;

	};
}
#pragma once

#include "IExpression.h"

#include <memory>

namespace AST {

	class LengthExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		LengthExpression(
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
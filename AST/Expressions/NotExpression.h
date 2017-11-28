#pragma once

#include "IExpression.h"

#include <memory>

namespace AST {

	class NotExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		NotExpression(
			IExpression* right
		)
			:right(right)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> right;
	};
}
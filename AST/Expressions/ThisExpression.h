#pragma once

#include "IExpression.h"

#include <memory>

namespace AST {

	class ThisExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		ThisExpression(
		)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
	};
}
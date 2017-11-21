#pragma once

#include "IExpression.h"
#include <memory>

namespace AST {

	class IntegerExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		IntegerExpression(
			int integer
		)
			:integer(integer)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		int integer;
	};
}
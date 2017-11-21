#pragma once

#include "IExpression.h"
#include <memory>

namespace AST {

	class BoolExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		BoolExpression(bool b)
			:b(b)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		bool b;
	};
}
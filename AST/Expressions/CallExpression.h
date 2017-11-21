#pragma once

#include "IExpression.h"
#include "CExpressionSequence.h"
#include "CId.h"
#include <memory>

namespace AST {

	class CallExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		CallExpression(
			IExpression* left,
			CId* element,
			CExpressionSequence* arguments
		)
			:left(left), element(element), arguments(arguments)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IExpression> left;
		std::unique_ptr<CId> element;
		std::unique_ptr<CExpressionSequence> arguments;

	};
}
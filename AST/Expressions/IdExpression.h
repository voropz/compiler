#pragma once

#include "IExpression.h"
#include "CId.h"
#include <memory>

namespace AST {

	class IdExpression : public IExpression {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		IdExpression(CId* id)
			:id(id)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CId> id;
	};
}
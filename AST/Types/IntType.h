#pragma once

#include "IType.h"

namespace AST {

	class IntType : public IType {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		IntType()
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
	};
}
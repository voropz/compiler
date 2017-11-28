#pragma once

#include "IType.h"

namespace AST {

	class IntArrayType : public IType {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		IntArrayType()
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
	};
}
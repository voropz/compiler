#pragma once

#include "IType.h"

namespace AST {

	class BoolType : public IType {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker; 
		friend class Visitor::TypeChecker;

	public:
		BoolType() 
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
	};
}
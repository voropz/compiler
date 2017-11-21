#pragma once

#include "IType.h"

namespace AST {

	class ClassType : public IType {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker;

	public:
		ClassType(
			CId* class_name)
			:class_name(class_name)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CId> class_name;
	};
}
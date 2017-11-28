#pragma once

#include "INode.h"
#include "IType.h"
#include "CId.h"
#include <memory>
#include <string>

namespace AST {

	class CVar : public INode {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	public:
		CVar(
			IType* type,
			CId* id)
			:type(type), id(id)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IType> type;
		std::unique_ptr<CId> id;
	};
}
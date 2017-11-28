#pragma once
#include <list>
#include "INode.h"
#include "CVar.h"

namespace AST {
	class CVarSequence : public INode
	{
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;
	private:
		std::list<std::unique_ptr<CVar>> list;

	public:
		CVarSequence(CVarSequence* sequence, CVar* appendix)
		{
			if (!appendix) { return; }

			if (sequence) {
				list = std::move(std::unique_ptr<CVarSequence>(sequence)->list);
				list.emplace_back(appendix);
			}
			else {
				list.push_back(std::move(std::unique_ptr<CVar>(appendix)));
			}
		}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}
	};

}
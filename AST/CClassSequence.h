#pragma once
#include <list>
#include "INode.h"
#include "CClass.h"

namespace AST {
	class CClassSequence : public INode
	{
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker; 
		friend class Visitor::TypeChecker;
	private:
		std::list<std::unique_ptr<CClass>> list;

	public:
		CClassSequence(CClassSequence* sequence, CClass* appendix)
		{
			if (sequence) {
				list = std::move(sequence->list);
				list.emplace_back(appendix);
			}
			else {
				list.push_back(std::move(std::unique_ptr<CClass>(appendix)));
			}
		}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}
	};

}
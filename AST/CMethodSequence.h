#pragma once
#include <list>
#include "INode.h"
#include "CMethod.h"

namespace AST {
	class CMethodSequence : public INode
	{
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;
	private:
		std::list<std::unique_ptr<CMethod>> list;

	public:
		CMethodSequence(CMethodSequence* sequence, CMethod* appendix)
		{
			if (sequence) {
				list = std::move(std::unique_ptr<CMethodSequence>(sequence)->list);
				list.emplace_back(appendix);
			}
			else {
				list.push_back(std::move(std::unique_ptr<CMethod>(appendix)));
			}
		}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}
	};

}
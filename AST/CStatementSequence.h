#pragma once
#include <list>
#include "INode.h"
#include "IStatement.h"

namespace AST {
	class CStatementSequence : public INode
	{
		friend class Visitor::Printer; friend class Visitor::TableMaker;
	private:
		std::list<std::unique_ptr<IStatement>> list;

	public:
		CStatementSequence(CStatementSequence* sequence, IStatement* appendix)
		{
			if (sequence) {
				list = std::move(std::unique_ptr<CStatementSequence>(sequence)->list);
				list.emplace_back(appendix);
			}
			else {
				list.push_back(std::move(std::unique_ptr<IStatement>(appendix)));
			}
		}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}
	};

}
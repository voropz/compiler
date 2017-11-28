#pragma once
#include <list>
#include "INode.h"
#include "IExpression.h"

namespace AST {
	class CExpressionSequence : public INode
	{
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;
	private:
		std::list<std::unique_ptr<IExpression>> list;

	public:
		CExpressionSequence(CExpressionSequence* sequence, IExpression* appendix)
		{
			if (sequence) {
				list = std::move(sequence->list);
				list.emplace_back(appendix);
			}
			else {
				list.push_back(std::move(std::unique_ptr<IExpression>(appendix)));
			}
		}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}
	};

}

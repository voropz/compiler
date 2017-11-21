#pragma once

#include "INode.h"
#include "CId.h"
#include "IType.h"
#include "CVarSequence.h"
#include "CStatementSequence.h"
#include "IExpression.h"
#include <memory>
#include <string>
#include <vector>

namespace AST {

	class CMethod : public INode {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker;

	public:
		CMethod(
			IType* type,
			CId* name,
			CVarSequence* parameters,
			CVarSequence* vars,
			CStatementSequence* statements,
			IExpression* return_expr
			)
			:type(type), name(name), parameters(parameters),
			vars(vars), statements(statements), return_expr(return_expr)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<IType> type;
		std::unique_ptr<CId> name;
		std::unique_ptr<CVarSequence> parameters;
		std::unique_ptr<CVarSequence> vars;
		std::unique_ptr<CStatementSequence> statements;
		std::unique_ptr<IExpression> return_expr;
	};
}
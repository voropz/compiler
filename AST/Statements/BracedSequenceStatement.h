#pragma once

#include "CStatementSequence.h"
#include <memory>

namespace AST {

	class BracedSequenceStatement : public IStatement {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	public:
		BracedSequenceStatement(
			CStatementSequence* sequence
		) : sequence(sequence)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CStatementSequence> sequence;
	};
}
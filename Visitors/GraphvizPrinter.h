#pragma once

#include <fstream>
#include <string>

#include "IncludeList.h"

#include <iostream>

namespace Visitor {
	class Printer;
}

using namespace AST;
class Visitor::Printer : IVisitor {

private:
	std::ofstream out;

	void printVertex(INode* node, std::string name) {
		out << "node" << node << "[label=\"" << name << "\"]\n";
	}

	void printEdge(INode* from, INode* to, std::string descr = "") {
		out << "node" << from << "->" << "node" << to;
		if (!descr.empty()) {
			out << "[label=\"" << descr << "\"]";
		}
		out << std::endl;
	}

public:
	Printer(std::string path)
	{
		out.open(path);
		out << "digraph g {\n";
	}

	~Printer()
	{
		out << "}";
		out.close();
	}
		void Visit(CProgram* node);
		void Visit(CClass* node);
		void Visit(CClassSequence* node);
		void Visit(CId* node);
		void Visit(CMain* node);
		void Visit(CMethod* node);
		void Visit(CMethodSequence* node);
		void Visit(CStatementSequence* node);
		void Visit(CExpressionSequence* node);
		void Visit(CVar* node);
		void Visit(CVarSequence* node);
		void Visit(CallExpression* node);
		void Visit(ArrayExpression* node);
		void Visit(AsterExpression* node);
		void Visit(LowerExpression* node);
		void Visit(MinusExpression* node);
		void Visit(PlusExpression* node);
		void Visit(AndExpression* node);
		void Visit(NewArrayExpression* node);
		void Visit(NotExpression* node);
		void Visit(ParenExpression* node);
		void Visit(NewExpression* node);
		void Visit(LengthExpression* node);
		void Visit(IdExpression* node);
		void Visit(IntegerExpression* node);
		void Visit(BoolExpression* node);
		void Visit(ThisExpression* node);
		void Visit(WhileStatement* node);
		void Visit(PrintStatement* node);
		void Visit(IfElseStatement* node);
		void Visit(BracedSequenceStatement* node);
		void Visit(AssignStatement* node);
		void Visit(ArrayAssignStatement* node);
		void Visit(BoolType* node);
		void Visit(ClassType* node);
		void Visit(IntArrayType* node);
		void Visit(IntType* node);
	};


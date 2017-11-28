#pragma once

#include <fstream>
#include <string>
#include <unordered_set>
#include "IncludeList.h"
#include "Symbol.h"
#include "Table.h"

#include <iostream>

namespace Visitor {
	class TypeChecker;
}

using namespace AST;
using namespace SymbolTable;
class Visitor::TypeChecker : IVisitor {

private:
	enum class Scope {
		outside,
		class_body,
		method_args,
		method_body
	};

	Table* table;
	TypeInfo current_type;
	Scope scope = Scope::outside;
	ClassInfo* current_class = nullptr;
	MethodInfo* current_method = nullptr;

	void print_operator_error(const std::string& operator_name, const std::string expected_type, const std::string type) {
		std::cout << "Operator " << operator_name << " should be applied to " << expected_type << " not " << type << std::endl;
	}


public:
	TypeChecker(Table* table)
		: table(table), current_type(Type::Void)
	{}

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


#pragma once
namespace AST {
	class CProgram;
	class CClass;
	class CClassSequence;
	class CId;
	class CMain;
	class CMethod;
	class CMethodSequence;
	class CStatementSequence;
	class CExpressionSequence;
	class CVar;
	class CVarSequence;
	class IExpression;
	class IStatement;
	class IType;

	class CallExpression;
	class ArrayExpression;
	class AsterExpression;
	class LowerExpression;
	class MinusExpression;
	class PlusExpression;
	class AndExpression;
	class NewArrayExpression;
	class NotExpression;
	class ParenExpression;
	class NewExpression;
	class LengthExpression;
	class IdExpression;
	class IntegerExpression;
	class BoolExpression;
	class ThisExpression;

	class WhileStatement;
	class PrintStatement;
	class IfElseStatement;
	class BracedSequenceStatement;
	class AssignStatement;
	class ArrayAssignStatement;

	class BoolType;
	class ClassType;
	class IntArrayType;
	class IntType;

}
namespace Visitor {
	class IVisitor;
	class Printer;
	class TableMaker;
	class TypeChecker;
}

#define VISIT(NOD) virtual void Visit(AST::NOD* node) = 0;

class Visitor::IVisitor {
public:
	    VISIT(CProgram)
		VISIT(CClass)
		VISIT(CClassSequence)
		VISIT(CExpressionSequence)
		VISIT(CId)
		VISIT(CMain)
		VISIT(CMethod)
		VISIT(CMethodSequence)
		VISIT(CStatementSequence)
		VISIT(CVar)
		VISIT(CVarSequence)

		VISIT(CallExpression)
		VISIT(ArrayExpression)
		VISIT(AsterExpression)
		VISIT(LowerExpression)
		VISIT(MinusExpression)
		VISIT(PlusExpression)
		VISIT(AndExpression)
		VISIT(NewArrayExpression)
		VISIT(NotExpression)
		VISIT(ParenExpression)
		VISIT(NewExpression)
		VISIT(LengthExpression)
		VISIT(IdExpression)
		VISIT(IntegerExpression)
		VISIT(BoolExpression)
		VISIT(ThisExpression)

		VISIT(WhileStatement)
		VISIT(PrintStatement)
		VISIT(IfElseStatement)
		VISIT(BracedSequenceStatement)
		VISIT(AssignStatement)
		VISIT(ArrayAssignStatement)

		VISIT(BoolType)
		VISIT(ClassType)
		VISIT(IntArrayType)
		VISIT(IntType)
};
#pragma once

#include "INode.h"
namespace AST {

	class IExpression : public INode {
		friend class Visitor::Printer; friend class Visitor::TableMaker; friend class Visitor::TypeChecker;

	};
}
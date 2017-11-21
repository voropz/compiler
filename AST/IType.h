#pragma once

#include "INode.h"
namespace AST {

	class IType : public INode {
		friend class Visitor::Printer; friend class Visitor::TableMaker;

	};
}
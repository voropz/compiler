#pragma once

#include "INode.h"
namespace AST {

	class IStatement : public INode {
		friend class Visitor::Printer;

	};
}
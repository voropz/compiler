#pragma once

#include <vector>
#include <memory>
#include "IVisitor.h"


namespace AST {

	class INode {
	public:

		virtual ~INode() {}

		virtual void Visit(Visitor::IVisitor* visitor) = 0;
	};

}


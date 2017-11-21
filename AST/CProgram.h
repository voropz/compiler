#pragma once

#include "INode.h"
#include "CMain.h"
#include "CClassSequence.h"
#include <memory>

namespace AST {

	class CProgram : public INode {
		friend class Visitor::Printer; 
		friend class Visitor::TableMaker;

	public:
		CProgram(
			CMain* main,
			CClassSequence* classes
		)
			:main(main), classes(classes)
		{}

		void Visit(Visitor::IVisitor* visitor) {
			visitor->Visit(this);
		}

	private:
		std::unique_ptr<CMain> main;
		std::unique_ptr<CClassSequence> classes;

	};
}
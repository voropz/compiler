#include "SymbolTableMaker.h"
#include <iostream>

void Visitor::TableMaker::Visit(CProgram* node) {
	node->main->Visit(this);

	if (node->classes.get()) {
		node->classes->Visit(this);
	}
}

void Visitor::TableMaker::Visit(CClass* node) {
	// add class with parent or not
	if (node->extends_name.get()) {
		current_class = table->add_class(node->name->name, node->extends_name->name);
	} else {
		current_class = table->add_class(node->name->name);
	}
	if (current_class == nullptr) {
		std::cout << "Class redefinition: " << node->name->name << std::endl;
		return;
	}

	scope = Scope::class_body;
	if (node->variables.get()) {
		node->variables->Visit(this);
	}

	if (node->methods.get()) {
		node->methods->Visit(this);
	}
	scope = Scope::outside;
}

void Visitor::TableMaker::Visit(CClassSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
}

void Visitor::TableMaker::Visit(CId* node) {}

void Visitor::TableMaker::Visit(CMain* node) {

	// do we need info about "public static void main"? seems no...
	current_class = table->add_class(node->class_name->name);

}

void Visitor::TableMaker::Visit(CMethod* node) {
	assert(scope == Scope::class_body);

	// type is determined inside this call:
	node->type->Visit(this);
	//3.a
	current_method = current_class->add_method(node->name->name, type);
	if (current_method == nullptr) {
		std::cout << "Method redefinition: " << node->name->name << std::endl;
		return;
	}


	scope = Scope::method_args;
	node->parameters->Visit(this);
	scope = Scope::method_body;
	if (node->vars.get()) {
		node->vars->Visit(this);
	}
	if (node->statements.get()) {
		//node->statements->Visit(this);
	}
	scope = Scope::class_body;
}

void Visitor::TableMaker::Visit(CMethodSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
}

void Visitor::TableMaker::Visit(CStatementSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
}

void Visitor::TableMaker::Visit(CExpressionSequence* node) {}

void Visitor::TableMaker::Visit(CVar* node) {

	if (scope == Scope::outside) {
		std::cout << "variable outside scope (" << node->id->name << ")\n";
		return;
	}

	node->type->Visit(this);

	if (scope == Scope::class_body) {
		if (current_class->add_variable(node->id->name, type) == nullptr) {
			std::cout << "Variable redefinition (" << node->id->name << ")\n";
		}
	}

	if (scope == Scope::method_body) {
		if (!current_method->add_variable(node->id->name, type)) {
			std::cout << "Variable redefinition (" << node->id->name << ")\n";
		}
	}

	if (scope == Scope::method_args) {
		if (!current_method->add_arg(node->id->name, type)) {
			std::cout << "Variable redefinition (" << node->id->name << ")\n";
		}
	}

}

void Visitor::TableMaker::Visit(CVarSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
}

void Visitor::TableMaker::Visit(CallExpression* node) {}

void Visitor::TableMaker::Visit(ArrayExpression* node) {}

void Visitor::TableMaker::Visit(AsterExpression* node) {}

void Visitor::TableMaker::Visit(LowerExpression* node) {

}

void Visitor::TableMaker::Visit(MinusExpression* node) {

}

void Visitor::TableMaker::Visit(PlusExpression* node) {

}

void Visitor::TableMaker::Visit(AndExpression* node) {

}

void Visitor::TableMaker::Visit(NewArrayExpression* node) {}

void Visitor::TableMaker::Visit(NotExpression* node) {}

void Visitor::TableMaker::Visit(ParenExpression* node) {}

void Visitor::TableMaker::Visit(NewExpression* node) {}

void Visitor::TableMaker::Visit(LengthExpression* node) {}

void Visitor::TableMaker::Visit(IdExpression* node) {}

void Visitor::TableMaker::Visit(IntegerExpression* node) {}

void Visitor::TableMaker::Visit(BoolExpression* node) {}

void Visitor::TableMaker::Visit(ThisExpression* node) {}

void Visitor::TableMaker::Visit(WhileStatement* node) {}

void Visitor::TableMaker::Visit(PrintStatement* node) {

}

void Visitor::TableMaker::Visit(IfElseStatement* node) {

}

void Visitor::TableMaker::Visit(BracedSequenceStatement* node) {}

void Visitor::TableMaker::Visit(AssignStatement* node) {

}

void Visitor::TableMaker::Visit(ArrayAssignStatement* node) {

}

void Visitor::TableMaker::Visit(BoolType* node) {
	type = { Type::Bool, nullptr };
}

void Visitor::TableMaker::Visit(ClassType* node) {
	Symbol* symbol = Symbol::get_intern(node->class_name->name);
	type = { Type::UserClass, symbol };
}

void Visitor::TableMaker::Visit(IntArrayType* node) {
	type = { Type::IntArray, nullptr };
}

void Visitor::TableMaker::Visit(IntType* node) {
	type = { Type::Int, nullptr };
}

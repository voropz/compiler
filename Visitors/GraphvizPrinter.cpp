#include "GraphvizPrinter.h"

	void Visitor::Printer::Visit(CProgram* node) {
		printVertex(node, "Program");
		printEdge(node, node->main.get());
		node->main->Visit(this);

		if (node->classes.get()) {
			printEdge(node, node->classes.get());
			node->classes->Visit(this);
		}
	}

void Visitor::Printer::Visit(CClass* node) {
	printVertex(node, "class");

	printEdge(node, node->name.get(), "name");
	node->name->Visit(this);

	if (node->extends_name.get()) {
		printEdge(node, node->extends_name.get(), "parent");
		node->extends_name->Visit(this);
	}

	if (node->variables.get()) {
		printEdge(node, node->variables.get());
		node->variables->Visit(this);
	}

	if (node->methods.get()) {
		printEdge(node, node->methods.get());
		node->methods->Visit(this);
	}
}

void Visitor::Printer::Visit(CClassSequence* node) { 
	printVertex(node, "list of classes");
	for (const auto& child : node->list) {
		printEdge(node, child.get());
		child->Visit(this);
	}
}

void Visitor::Printer::Visit(CId* node) {
	printVertex(node, "ID: " + node->name);
}

void Visitor::Printer::Visit(CMain* node) { 
	printVertex(node, "Main class");
	printEdge(node, node->class_name.get(), "name");
	node->class_name->Visit(this);
	printEdge(node, node->string_name.get(), "public static void main String[]");
	node->string_name->Visit(this);

	printEdge(node, node->state.get(), "Statement");
	node->state->Visit(this);

}

void Visitor::Printer::Visit(CMethod* node) { 
	printVertex(node, "Method");
	printEdge(node, node->type.get(), "return type");
	node->type->Visit(this);

	printEdge(node, node->name.get(), "name");
	node->name->Visit(this);

	if (node->parameters.get()) {
		printEdge(node, node->parameters.get(), "params");
		node->parameters->Visit(this);
	}

	if (node->vars.get()) {
		printEdge(node, node->vars.get(), "local vars");
		node->vars->Visit(this);
	}

	if (node->statements.get()) {
		printEdge(node, node->statements.get());
		node->statements->Visit(this);
	}

	printEdge(node, node->return_expr.get(), "returns");
	node->return_expr->Visit(this);

}

void Visitor::Printer::Visit(CMethodSequence* node) {
	printVertex(node, "list of methods");
	for (const auto& child : node->list) {
		printEdge(node, child.get());
		child->Visit(this);
	}
}

void Visitor::Printer::Visit(CStatementSequence* node) {
	printVertex(node, "list of statements");
	for (const auto& child : node->list) {
		printEdge(node, child.get());
		child->Visit(this);
	}
}

void Visitor::Printer::Visit(CExpressionSequence* node) {
	printVertex(node, "list of expressions");
	for (const auto& child : node->list) {
		printEdge(node, child.get());
		child->Visit(this);
	}
}

void Visitor::Printer::Visit(CVar* node) { 
	printVertex(node, "Var");

	printEdge(node, node->type.get(), "type");
	node->type->Visit(this);

	printEdge(node, node->id.get(), "name");
	node->id->Visit(this);
}

void Visitor::Printer::Visit(CVarSequence* node) {
	printVertex(node, "list of vars");
	for (const auto& child : node->list) {
		printEdge(node, child.get());
		child->Visit(this);
	}
}

void Visitor::Printer::Visit(CallExpression* node) { 
	printVertex(node, "call");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->element.get());
	node->element->Visit(this);

	if (node->arguments.get()) {
		printEdge(node, node->arguments.get(), "arguments");
		node->arguments->Visit(this);
	}
}

void Visitor::Printer::Visit(ArrayExpression* node) { 
	printVertex(node, "array");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->element.get());
	node->element->Visit(this);

}

void Visitor::Printer::Visit(AsterExpression* node) { 
	printVertex(node, "*");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->right.get());
	node->right->Visit(this);
}

void Visitor::Printer::Visit(LowerExpression* node) { 
	printVertex(node, "<");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->right.get());
	node->right->Visit(this);

}

void Visitor::Printer::Visit(MinusExpression* node) { 
	printVertex(node, "-");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->right.get());
	node->right->Visit(this);
}

void Visitor::Printer::Visit(PlusExpression* node) {
	printVertex(node, "+");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->right.get());
	node->right->Visit(this);
}

void Visitor::Printer::Visit(AndExpression* node) { 
	printVertex(node, "&");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->right.get());
	node->right->Visit(this);
}

void Visitor::Printer::Visit(NewArrayExpression* node) { 
	printVertex(node, "new[]");

	printEdge(node, node->left.get());
	node->left->Visit(this);
}

void Visitor::Printer::Visit(NotExpression* node) { 
	printVertex(node, "!");

	printEdge(node, node->right.get());
	node->right->Visit(this);
}

void Visitor::Printer::Visit(ParenExpression* node) { 
	printVertex(node, "(...)");

	printEdge(node, node->left.get());
	node->left->Visit(this);
}

void Visitor::Printer::Visit(NewExpression* node) { 
	printVertex(node, "new");

	printEdge(node, node->left.get());
	node->left->Visit(this);

}

void Visitor::Printer::Visit(LengthExpression* node) {
	printVertex(node, "length");

	printEdge(node, node->left.get());
	node->left->Visit(this);
}

void Visitor::Printer::Visit(IdExpression* node) {
	printVertex(node, "id");

	printEdge(node, node->id.get());
	node->id->Visit(this);
}

void Visitor::Printer::Visit(IntegerExpression* node) { 
	printVertex(node, std::to_string(node->integer));
}

void Visitor::Printer::Visit(BoolExpression* node) { 
	printVertex(node, std::to_string(node->b));
}

void Visitor::Printer::Visit(ThisExpression* node) { 
	printVertex(node, "this");
}

void Visitor::Printer::Visit(WhileStatement* node) { 
	printVertex(node, "while");

	printEdge(node, node->condition.get(), "condition");
	node->condition->Visit(this);

	printEdge(node, node->body.get(), "do");
	node->body->Visit(this);
}

void Visitor::Printer::Visit(PrintStatement* node) { 
	printVertex(node, "System.out.println()");

	printEdge(node, node->body.get());
	node->body->Visit(this);
}

void Visitor::Printer::Visit(IfElseStatement* node) { 
	printVertex(node, "if");

	printEdge(node, node->condition.get(), "condition");
	node->condition->Visit(this);

	printEdge(node, node->body_true.get(), "true");
	node->body_true->Visit(this);

	printEdge(node, node->body_false.get(), "false");
	node->body_false->Visit(this);
}

void Visitor::Printer::Visit(BracedSequenceStatement* node) { 
	printVertex(node, "{...}");

	printEdge(node, node->sequence.get());
	node->sequence->Visit(this);
}

void Visitor::Printer::Visit(AssignStatement* node) { 
	printVertex(node, "=");

	printEdge(node, node->left.get(), "left");
	node->left->Visit(this);

	printEdge(node, node->right.get(), "right");
	node->right->Visit(this);
}

void Visitor::Printer::Visit(ArrayAssignStatement* node) { 
	printVertex(node, "[]=");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->in_bracket.get());
	node->in_bracket->Visit(this);

	printEdge(node, node->right.get());
	node->right->Visit(this);
}

void Visitor::Printer::Visit(BoolType* node) { 
	printVertex(node, "bool");
}

void Visitor::Printer::Visit(ClassType* node) { 
	printVertex(node, "class");
}

void Visitor::Printer::Visit(IntArrayType* node) { 
	printVertex(node, "int[]");
}

void Visitor::Printer::Visit(IntType* node) { 
	printVertex(node, "int");
}
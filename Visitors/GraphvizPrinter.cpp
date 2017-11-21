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

	printEdge(node, node->name.get());
	node->name->Visit(this);

	if (node->extends_name.get()) {
		printEdge(node, node->extends_name.get());
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
	printVertex(node, node->name);
}

void Visitor::Printer::Visit(CMain* node) { 
	printVertex(node, "Main");
	printEdge(node, node->class_name.get());
	node->class_name->Visit(this);
	printEdge(node, node->string_name.get());
	node->string_name->Visit(this);
	printEdge(node, node->state.get());
	node->state->Visit(this);
}

void Visitor::Printer::Visit(CMethod* node) { 
	printVertex(node, "Method");
	printEdge(node, node->type.get());
	node->type->Visit(this);

	printEdge(node, node->name.get());
	node->name->Visit(this);

	printEdge(node, node->parameters.get());
	node->parameters->Visit(this);

	if (node->vars.get()) {
		printEdge(node, node->vars.get());
		node->vars->Visit(this);
	}

	if (node->statements.get()) {
		printEdge(node, node->statements.get());
		node->statements->Visit(this);
	}

	printEdge(node, node->return_expr.get());
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

	printEdge(node, node->id.get());
	node->id->Visit(this);

	printEdge(node, node->type.get());
	node->type->Visit(this);
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
		printEdge(node, node->arguments.get());
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
	printVertex(node, "[]");

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

	printEdge(node, node->condition.get());
	node->condition->Visit(this);

	printEdge(node, node->body.get());
	node->body->Visit(this);
}

void Visitor::Printer::Visit(PrintStatement* node) { 
	printVertex(node, "print");

	printEdge(node, node->body.get());
	node->body->Visit(this);
}

void Visitor::Printer::Visit(IfElseStatement* node) { 
	printVertex(node, "if/else");

	printEdge(node, node->condition.get());
	node->condition->Visit(this);

	printEdge(node, node->body_false.get());
	node->body_false->Visit(this);

	printEdge(node, node->body_true.get());
	node->body_true->Visit(this);
}

void Visitor::Printer::Visit(BracedSequenceStatement* node) { 
	printVertex(node, "{...}");

	printEdge(node, node->sequence.get());
	node->sequence->Visit(this);
}

void Visitor::Printer::Visit(AssignStatement* node) { 
	printVertex(node, "=");

	printEdge(node, node->left.get());
	node->left->Visit(this);

	printEdge(node, node->right.get());
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

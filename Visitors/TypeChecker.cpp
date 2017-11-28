#include "TypeChecker.h"

void Visitor::TypeChecker::Visit(CProgram* node) {

	node->main->Visit(this);

	if (node->classes.get()) {
		node->classes->Visit(this);
	}
	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(CClass* node) {
	if (node->extends_name.get()) {
		const Symbol* my_name = Symbol::get_intern(node->name->name);
		ClassInfo* curr_class = table->get_class(node->name->name);

		while (curr_class->get_super() != nullptr) {
			curr_class = table->get_class(curr_class->get_super()->get_text());

			if (curr_class->get_name() == my_name) {
				std::cout << "Cyclic dependency " << node->name->name << std::endl;
				break;
			}
		}
	}

	scope = Scope::class_body;
	current_class = table->get_class(node->name->name);
	if (node->variables.get()) {
		node->variables->Visit(this);
	}

	if (node->methods.get()) {
		node->methods->Visit(this);
	}

	scope = Scope::outside;
	current_class = nullptr;
	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(CClassSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
}

void Visitor::TypeChecker::Visit(CId* node) {
	Symbol* my_name = Symbol::get_intern(node->name);

	if (scope == Scope::method_body) {
		const auto& block = current_method->get_block();
		auto it = block.find(my_name);
		if (it != block.end()) {
			current_type = it->second.get()->get_type();
			return;
		}
	}

	if (scope == Scope::method_args) {
		std::cout << "well, its weird\n";
	}

	if (scope == Scope::class_body || scope == Scope::method_body) {
		const auto& block = current_class->get_var_block();
		auto it = block.find(my_name);
		if (it != block.end()) {
			current_type = it->second.get()->get_type();
			return;
		}
	}

	ClassInfo* class_info = table->get_class(node->name);
	if (class_info == nullptr) {
		std::cout << "Name " << node->name << " not found :(\n";
		current_type = TypeInfo(Type::Void);
		return;
	}

	current_type = TypeInfo(Type::UserClass, class_info->get_name());
}

void Visitor::TypeChecker::Visit(CMain* node) {

	node->state->Visit(this);
	current_type = TypeInfo(Type::Void);

}

void Visitor::TypeChecker::Visit(CMethod* node) {
	assert(scope == Scope::class_body);
	current_method = current_class->get_method(node->name->name);
	//3b

	node->type->Visit(this);
	if (current_type.type == Type::UserClass) {
		if (table->get_class(current_type.get_name()) == nullptr) {
			std::cout << "Method " << node->name->name << " returns unknown type " << current_type.get_name() << std::endl;
		}
	}
	TypeInfo return_type = current_type;

	scope = Scope::method_args;
	if (node->parameters.get()) {
		node->parameters->Visit(this);
	}
	scope = Scope::method_body;
	if (node->vars.get()) {
		node->vars->Visit(this);
	}

	if (node->statements.get()) {
		node->statements->Visit(this);
	}

	// todo: check type == return_type
	node->return_expr->Visit(this);
	scope = Scope::class_body;
	current_method = nullptr;
	current_type = return_type;
}

void Visitor::TypeChecker::Visit(CMethodSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(CStatementSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(CExpressionSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(CVar* node) {
	// 2a, 4a
	// set current_type:
	node->type->Visit(this);
	if (current_type.type == Type::UserClass) {
		if (table->get_class(current_type.get_name()) == nullptr) {
			std::cout << "Wrong type of variable: " << current_type.get_name() << " " << node->id->name << std::endl;
		}
	}
}

void Visitor::TypeChecker::Visit(CVarSequence* node) {
	for (const auto& child : node->list) {
		child->Visit(this);
	}
	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(CallExpression* node) {

	node->left->Visit(this);
	if (current_type.type != Type::UserClass) {
		std::cout << "Calling method " << node->element->name << " from non-class type " << current_type.get_name() << std::endl;
		return;
	}

	ClassInfo* call_class = table->get_class(current_type.user_class_name->get_text());
	Symbol* my_name = Symbol::get_intern(node->element->name);

	const auto& methods = call_class->get_method_block();
	auto me_in_class = methods.find(my_name);
	if (me_in_class == methods.end()) {
		std::cout << "Method " << node->element->name << " cannot be found in " << current_type.get_name() << std::endl;
		return;
	}

	const std::vector<Symbol*>& expected_args = me_in_class->second->get_args();
	if (node->arguments == nullptr) {
		if (!expected_args.empty()) {
			std::cout << "Wrong number of arguments in method " << current_type.get_name() << "::" << node->element->name
				<< ". Expected: " << expected_args.size() << ", got 0" << std::endl;
		}
	} else {
		const auto& block = me_in_class->second->get_block();

		const std::list<std::unique_ptr<IExpression>>& args = node->arguments->list;

		auto it = expected_args.cbegin();
		auto jt = args.cbegin();
		int i = 0;
		for (; it != expected_args.cend() && jt != args.cend(); ++i, ++it, ++jt) {

			jt->get()->Visit(this);
			VariableInfo* var = block.find(*it)->second.get();
			if (current_type != var->get_type()) {
				std::cout << "Wrong argument in method " << current_type.get_name() << "::" << node->element->name
					<< ". Expected: " << var->get_type().get_name() << " " << var->get_name()->get_text()
					<< ", got: " << current_type.get_name() << std::endl;
				break;
			}
		}
		if (it == expected_args.cend() && jt != args.cend())
			std::cout << "Wrong number of arguments in method " << current_type.get_name() << "::" << node->element->name
			<< ". Expected: " << expected_args.size() << ", got at least " << i + 1 << std::endl;
		if (it != expected_args.cend() && jt == args.cend())
			std::cout << "Wrong number of arguments in method " << current_type.get_name() << "::" << node->element->name
			<< ". Expected: " << expected_args.size() << ", got only " << i << std::endl;
	}


	//node->element->Visit(this);
	current_type = me_in_class->second.get()->get_return_type();

}

void Visitor::TypeChecker::Visit(ArrayExpression* node) {
	node->element->Visit(this);
	if (current_type.type != Type::Int) {
		std::cout << "Array index should be a number, not " << current_type.get_name() << std::endl;
	}

	//10a
	node->left->Visit(this);
	if (current_type.type != Type::IntArray) {
		print_operator_error("[]", "Int[]", current_type.get_name());
	}

	current_type = TypeInfo(Type::Int);
}

void Visitor::TypeChecker::Visit(AsterExpression* node) {
	node->left->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("*", "int", current_type.get_name());
	}

	node->right->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("*", "int", current_type.get_name());
	}
	current_type = TypeInfo(Type::Int);
}

void Visitor::TypeChecker::Visit(LowerExpression* node) {
	node->left->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("<", "int", current_type.get_name());
	}

	node->right->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("<", "int", current_type.get_name());
	}
	current_type = TypeInfo(Type::Bool);
}

void Visitor::TypeChecker::Visit(MinusExpression* node) {
	node->left->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("-", "int", current_type.get_name());
	}

	node->right->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("-", "int", current_type.get_name());
	}
	current_type = TypeInfo(Type::Int);
}

void Visitor::TypeChecker::Visit(PlusExpression* node) {
	node->left->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("+", "int", current_type.get_name());
	}

	node->right->Visit(this);
	if (current_type.type != Type::Int) {
		print_operator_error("+", "int", current_type.get_name());
	}
	current_type = TypeInfo(Type::Int);
}

void Visitor::TypeChecker::Visit(AndExpression* node) {

	node->left->Visit(this);
	if (current_type.type != Type::Bool) {
		print_operator_error("&", "Bool", current_type.get_name());
	}

	node->right->Visit(this);
	if (current_type.type != Type::Bool) {
		print_operator_error("&", "Bool", current_type.get_name());
	}
	current_type = TypeInfo(Type::Bool);
}

void Visitor::TypeChecker::Visit(NewArrayExpression* node) {
	//12b
	node->left->Visit(this);
	if (current_type.type != Type::Int) {
		std::cout << "Creating array with non-integer size\n";
	}
	current_type = TypeInfo(Type::IntArray);
}

void Visitor::TypeChecker::Visit(NotExpression* node) {
	node->right->Visit(this);

	if (current_type.type != Type::Bool) {
		print_operator_error("!", "bool", current_type.get_name());
		current_type = TypeInfo(Type::Bool);
	}
}

void Visitor::TypeChecker::Visit(ParenExpression* node) {
	node->left->Visit(this);
}

void Visitor::TypeChecker::Visit(NewExpression* node) {
	//12a
	if (table->get_class(node->left->name) == nullptr)
		std::cout << "Wrong type in NEW expression: " << node->left->name << std::endl;

	node->left->Visit(this);
}

void Visitor::TypeChecker::Visit(LengthExpression* node) {

	node->left->Visit(this);
	current_type = TypeInfo(Type::Int);
}

void Visitor::TypeChecker::Visit(IdExpression* node) {
	node->id->Visit(this);
}

void Visitor::TypeChecker::Visit(IntegerExpression* node) {
	current_type = TypeInfo(Type::Int);
}

void Visitor::TypeChecker::Visit(BoolExpression* node) {
	current_type = TypeInfo(Type::Bool);
}

void Visitor::TypeChecker::Visit(ThisExpression* node) {
	current_type = TypeInfo(Type::UserClass, current_class->get_name());
}

void Visitor::TypeChecker::Visit(WhileStatement* node) {
	node->condition->Visit(this);
	if (current_type.type != Type::Bool)
		std::cout << "Condition in WHILE statement is not bool: " << current_type.get_name() << std::endl;
	node->body->Visit(this);

	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(PrintStatement* node) {
	// 6a
	node->body->Visit(this);
	if (current_type.type != Type::Int)
		std::cout << "Sorry, MiniJava can print only numbers, not " << current_type.get_name() << std::endl;

	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(IfElseStatement* node) {
	// 5a
	node->condition->Visit(this);
	if (current_type.type != Type::Bool)
		std::cout << "Condition in IF statement is not bool: " << current_type.get_name() << std::endl;

	node->body_true->Visit(this);
	node->body_false->Visit(this);

	current_type = TypeInfo(Type::Void);
}

void Visitor::TypeChecker::Visit(BracedSequenceStatement* node) {
	node->sequence->Visit(this);
}

void Visitor::TypeChecker::Visit(AssignStatement* node) {
	//7b
	node->left->Visit(this);
	TypeInfo left_type = current_type;

	node->right->Visit(this);
	if (left_type != current_type) {
		std::cout << "Cannot assign " << current_type.get_name() << " to " << left_type.get_name() << " " << node->left->name << std::endl;
	}
	current_type = left_type;
}

void Visitor::TypeChecker::Visit(ArrayAssignStatement* node) {
	//7b
	node->left->Visit(this);
	if (current_type != Type::IntArray) {
		std::cout << "WEIRD\n";
	}

	node->right->Visit(this);
	if (current_type != Type::Int)
		std::cout << "Cannot assign " << current_type.get_name() << " to element of int[] " << node->left->name << std::endl;

	//7c
	node->in_bracket->Visit(this);
	if (current_type.type != Type::Int)
		std::cout << "Array index should be a number, not " << current_type.get_name() << std::endl;

	current_type = Type::Int;
}

void Visitor::TypeChecker::Visit(BoolType* node) {
	current_type = TypeInfo(Type::Bool);
}

void Visitor::TypeChecker::Visit(ClassType* node) {
	current_type = TypeInfo(Type::UserClass, Symbol::get_intern(node->class_name->name));
}

void Visitor::TypeChecker::Visit(IntArrayType* node) {
	current_type = TypeInfo(Type::IntArray);
}

void Visitor::TypeChecker::Visit(IntType* node) {
	current_type = TypeInfo(Type::Int);
}

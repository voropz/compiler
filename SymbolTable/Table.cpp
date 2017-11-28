#include "Table.h"
#include <fstream>
#include <iostream>

namespace SymbolTable {
	ClassInfo* Table::add_class(const std::string& name) {
		auto symbol = Symbol::get_intern(name);

		auto result = classes.emplace(symbol, std::make_unique<ClassInfo>(name));
		if (result.second == false) {
			return nullptr;
		}

		return result.first->second.get();
	}

	ClassInfo* Table::add_class(const std::string& name, const std::string& super_name) {
		auto parent_symbol = Symbol::get_intern(super_name);
		auto symbol = Symbol::get_intern(name);

		auto result = classes.emplace(symbol, std::make_unique<ClassInfo>(name, parent_symbol));
		if (result.second == false) {
			return nullptr;
		}

		return result.first->second.get();
	}


	ClassInfo* Table::get_class(const std::string& name) {
		auto symbol = Symbol::get_intern(name);

		auto it = classes.find(symbol);
		if (it == classes.end()) {
			return nullptr;
		}
		return it->second.get();
	}

	void Table::print(const std::string& path) {
		std::ofstream out;
		out.open(path);
		out << "GLOBAL SCOPE:" << std::endl;

		for (const auto& entry : classes) {
			out << entry.second->get_name()->get_text();
			if (entry.second->get_super() != nullptr) {
				out << " extends " << entry.second->get_super()->get_text();
			}
			out << std::endl;
		}
		out << std::endl << "-----class descriptions:------" << std::endl << std::endl;

		for (const auto& entry : classes) {
			print_class(entry.second.get(), out);
		}

		out.close();
	}

	void Table::print_class(const ClassInfo* class_, std::ofstream& out) const {
		out << "CLASS " << class_->get_name()->get_text() << std::endl << "Methods: ";
		for (auto methods : class_->get_methods()) {
			out << methods->get_text() << ", ";
		}
		out << std::endl << "Variables: ";
		for (const auto& var : class_->get_var_block()) {
			out << var.second->get_type().get_name() << " " << var.second->get_name()->get_text() << ", ";
		}
		out << std::endl << std::endl;
		for (const auto& method : class_->get_method_block()) {
			print_method(method.second.get(), out);
		}

		out << std::endl << "-----end class------" << std::endl << std::endl;
	}

	void Table::print_method(const MethodInfo* method, std::ofstream& out) const {
		out << "METHOD " << method->get_return_type().get_name() << " " << method->get_name()->get_text() << "(";
		for (auto args : method->get_args()) {
			out << args->get_text() << ", ";
		}

		out << ")" << std::endl << "Variables: ";
		for (const auto& var : method->get_block()) {
			out << var.second->get_type().get_name() << " " << var.second->get_name()->get_text() << ", ";
		}

	}
}

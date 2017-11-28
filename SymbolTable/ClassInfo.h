#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "Symbol.h"


namespace SymbolTable {
	class ClassInfo;
	typedef std::unordered_map<const Symbol*, std::unique_ptr<ClassInfo>> ClassBlock;
}

class SymbolTable::ClassInfo : public Entry {
public:
		ClassInfo(const std::string& name, const Symbol* super_class = nullptr) 
		:Entry(name), super_class(super_class)
		{}


		VariableInfo* add_variable(const std::string& name, TypeInfo type) {
			Symbol* symbol = Symbol::get_intern(name);

			auto it = variables_block.find(symbol);
			if (it != variables_block.end())
				return nullptr;

			VariableInfo* var = new VariableInfo(name, type);
			variables_block.emplace(symbol, std::unique_ptr<VariableInfo>(var));
			vars.push_back(symbol);
			return var;
		}

		MethodInfo* add_method(const std::string& name, TypeInfo type) {
			Symbol* symbol = Symbol::get_intern(name);

			auto it = methods_block.find(symbol);
			if (it != methods_block.end())
				return nullptr;

			MethodInfo* var = new MethodInfo(name, type);
			methods_block.emplace(symbol, std::unique_ptr<MethodInfo>(var));
			methods.push_back(symbol);
			return var;
		}

		const std::vector<const Symbol*>& get_methods() const {
			return methods;
		}
		const std::vector<const Symbol*>& get_vars() const {
			return vars;
		}
		MethodInfo* get_method(const std::string& name) const {
			Symbol* int_name = Symbol::get_intern(name);
			auto it = methods_block.find(int_name);
			if (it == methods_block.end())
				return nullptr;
			return it->second.get();
		}
		const VariableBlock& get_var_block() const {
			return variables_block;
		}
		const MethodBlock& get_method_block() const {
			return methods_block;
		}
		const Symbol* get_super() const {
			return super_class;
		}

		
private:
		const Symbol* super_class;

		std::vector<const Symbol*> methods;
		std::vector<const Symbol*> vars;
		VariableBlock variables_block;
		MethodBlock methods_block;

};

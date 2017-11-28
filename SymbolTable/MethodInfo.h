#pragma once

#include <unordered_map>
#include <string>
#include <cassert>
#include "Symbol.h"
#include "VariableInfo.h"

namespace SymbolTable {
	class MethodInfo;
	typedef std::unordered_map<Symbol*, std::unique_ptr<MethodInfo>> MethodBlock;
}

class SymbolTable::MethodInfo : public Entry {
public:
	MethodInfo(std::string name, TypeInfo return_type)
		:Entry(name), return_type(return_type) {}


	bool add_variable(const std::string& name, TypeInfo type) {
		Symbol* symbol = Symbol::get_intern(name);

		auto it = block.find(symbol);
		if (it != block.end())
			return false;

		VariableInfo* var = new VariableInfo(name, type);
		block.emplace(symbol, std::unique_ptr<VariableInfo>(var));
		vars.push_back(symbol);
		return true;
	}

	bool add_arg(const std::string& name, TypeInfo type) {
		Symbol* symbol = Symbol::get_intern(name);

		auto it = block.find(symbol);
		if (it != block.end())
			return false;

		VariableInfo* var = new VariableInfo(name, type);
		block.emplace(symbol, std::unique_ptr<VariableInfo>(var));
		args.push_back(symbol);
		return true;
	}

	const std::vector<Symbol*>& get_args() const {
		return args;
	}
	const std::vector<Symbol*>& get_vars() const {
		return vars;
	}
	const VariableBlock& get_block() const {
		return block;
	}
	TypeInfo get_return_type() const {
		return return_type;
	}


private:
	const Symbol* class_name;
	std::vector<Symbol*> vars;
	std::vector<Symbol*> args;
	VariableBlock block;
	TypeInfo return_type;
};

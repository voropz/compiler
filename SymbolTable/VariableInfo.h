#pragma once

#include <unordered_map>
#include <string>
#include <cassert>
#include "Entry.h"

namespace SymbolTable {
	class VariableInfo;

	enum class Type {
		Int,
		IntArray,
		Bool,
		UserClass
	};

	class TypeInfo {
	public:
		Type type;
		Symbol* user_class_name;
		std::string get_name() const {
			switch (type) {
			case Type::Bool:
				return "bool";
			case Type::Int:
				return "int";
			case Type::IntArray:
				return "int[]";
			case Type::UserClass:
				return user_class_name->get_text();
			default:
				break;
			}
		}
	};

	typedef std::unordered_map<Symbol*, std::unique_ptr<VariableInfo>> VariableBlock;
}

class SymbolTable::VariableInfo : public Entry {

public:
	VariableInfo(std::string name, TypeInfo type) 
		:Entry(name), type(type)
	{}

	const TypeInfo& get_type() {
		return type;
	}


private:
	TypeInfo type;
};
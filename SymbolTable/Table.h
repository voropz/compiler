#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "ClassInfo.h"
#include "MethodInfo.h"

namespace SymbolTable {
	class Table;
}

class SymbolTable::Table {
public:
	// returns ClassInfo* ptr if added, nullptr on error (most likely already exists)
	ClassInfo* add_class(const std::string& name);
	ClassInfo* add_class(const std::string& name, const std::string& super_name);

	ClassInfo* get_class(const std::string& name);

	void print(const std::string& path);

private:
	ClassBlock classes;

	void print_class(const ClassInfo*, std::ofstream&) const;
	void print_method(const MethodInfo*, std::ofstream&) const;
};

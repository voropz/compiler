#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace SymbolTable {
	class Symbol;
}

class SymbolTable::Symbol {
public:
	Symbol(std::string name)
		: text(name) 
	{}


	const std::string& get_text() const {
		return text;
	}

	static inline Symbol* get_intern(const std::string& name);


private:
	std::string text;

};

SymbolTable::Symbol* 
SymbolTable::Symbol::get_intern(const std::string& name) {
	static std::unordered_map<std::string, std::unique_ptr<Symbol>> strings;
	auto cached = strings.find(name);
	if (cached != strings.end()) {
		return cached->second.get();
	}

	Symbol* newVal = new Symbol(name);
	strings.emplace (name, std::unique_ptr<Symbol>(newVal));

	return newVal;
}
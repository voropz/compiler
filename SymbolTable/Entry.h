#pragma once
#include <string>
#include "Symbol.h"

namespace SymbolTable {
	class Entry;
}

class SymbolTable::Entry {
	public:
		Entry(std::string name)
			:name(Symbol::get_intern(name))
		{}

		Entry(Symbol* name)
			:name(name)
		{}

		const Symbol* get_name() const {
			return name;
		}

	protected:
		const Symbol* name;

};

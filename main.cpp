#include <iostream>
#include "IncludeList.h"
#include "bison.tab.h"
#include "GraphvizPrinter.h"
#include "SymbolTableMaker.h"

extern CProgram* goal;

int main() {
	yyparse();
	Visitor::Printer* printer = new Visitor::Printer("tree.dot");
	printer->Visit(goal);
	delete printer;

	Table table;
	Visitor::TableMaker table_filler(&table);
	table_filler.Visit(goal);

	table.print("symbols.txt");

}
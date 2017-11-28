#include <iostream>
#include "IncludeList.h"
#include "bison.tab.h"
#include "GraphvizPrinter.h"
#include "SymbolTableMaker.h"
#include "TypeChecker.h"

extern CProgram* goal;
extern "C" FILE *yyin;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "usage: ./compiler <your file>\n";
		return -1;
	}

	FILE * pt = fopen(argv[1], "r");
	if (!pt) {
		std::cout << "Bad Input " << argv[1] << std::endl;
		return -1;
	}
	yyin = pt;
	do {
		yyparse();
	} while (!feof(yyin));


	Visitor::Printer* printer = new Visitor::Printer("output/tree.dot");
	printer->Visit(goal);
	delete printer;
	//std::cout << "Successfully built AST (file tree.dot)\n";

	Table table;
	Visitor::TableMaker table_filler(&table);
	table_filler.Visit(goal);

	table.print("output/symbols.txt");
	//std::cout << "Successfully built table (log saved as symbols.txt)\n";

	Visitor::TypeChecker checker(&table);
	checker.Visit(goal);

}

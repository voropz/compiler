CPPFLAGS = -I AST -I AST/Expressions -I AST/Statements -I AST/Types -I Visitors -I SymbolTable -I .

all: compiler

clean:
	rm flex.o bison.o graph.o table.o tablevisit.o checker.o bison.tab.h bison.tab.c lex.yy.c bison.output

compiler: bison.o flex.o graph.o table.o tablevisit.o checker.o main.cpp
	g++ -g --std=c++14 $(CPPFLAGS) flex.o bison.o graph.o table.o tablevisit.o checker.o main.cpp -lfl -o compiler 

checker.o: Visitors/TypeChecker.cpp
	g++ -g -c --std=c++14 $(CPPFLAGS) Visitors/TypeChecker.cpp -o checker.o

tablevisit.o: Visitors/SymbolTableMaker.cpp
	g++ -g -c --std=c++14 $(CPPFLAGS) Visitors/SymbolTableMaker.cpp -o tablevisit.o

table.o: SymbolTable/Table.cpp
	g++ -g -c --std=c++14 $(CPPFLAGS) SymbolTable/Table.cpp -o table.o

graph.o: Visitors/GraphvizPrinter.cpp
	g++ -g -c --std=c++14 $(CPPFLAGS) Visitors/GraphvizPrinter.cpp -o graph.o 

bison.o: bison.y
	bison -dt --verbose bison.y && g++ -g -c --std=c++14 $(CPPFLAGS) bison.tab.c -o bison.o

flex.o: flex.l
	flex flex.l && g++ -g -c $(CPPFLAGS) lex.yy.c -o flex.o
%{

    #include <iostream>
    #include <memory>

    #include "Visitors/GraphvizPrinter.h"
    CProgram* goal;

    extern int yylex();
    extern int yyparse();
    void yyerror(const char *s);
%}
%define parse.error verbose

%locations

%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_BRACE
%token RIGHT_BRACE
%token LEFT_PAREN
%token RIGHT_PAREN

%token AND
%token LOWER
%token PLUS
%token MINUS
%token ASTER
%token EQUALS
%token EXMARK
%token DOT
%token SEMICOLON
%token COMMA

%token CLASS
%token IF
%token ELSE
%token WHILE
%token NEW
%token THIS
%token TRUE
%token FALSE
%token PUBLIC
%token RETURN
%token EXTENDS
%token INT
%token BOOL
%token LENGTH
%token STRING
%token MAIN
%token PRINT
%token ID
%token INTEGER_LITERAL


// shift-reduce conflict resolving
%left LEFT_BRACKET
%left AND
%left LOWER
%left DOT
%left PLUS MINUS 
%left ASTER
%right EXMARK


// non-terminals
%union {
    char* stringValue;
    int intValue;

    AST::CProgram* program;
    AST::CMain* main_class;
    AST::CClass* class_decl;
    AST::CClassSequence* class_seq;
    AST::CVar* var_decl;
    AST::CVarSequence* var_seq;
    AST::CMethod* method;
    AST::CMethodSequence* method_seq;
    AST::IType* type;
    AST::IStatement* statement;
    AST::CStatementSequence* statement_seq;
    AST::IExpression* expr;
    AST::CExpressionSequence* expr_seq;
    AST::CId* id;
};

%type <program> goal;
%type <main_class> class_main;
%type <class_seq> class_s;
%type <class_decl> class class_ext;
%type <var_decl> var;
%type <var_seq> var_s param_s;
%type <method> method;
%type <method_seq> method_s;
%type <type> type;
%type <statement> state;
%type <statement_seq> state_s;
%type <expr> exp;
%type <expr_seq> exp_s;
%type <id> id;

%%
goal
  : class_main         { $$ = new CProgram($1, nullptr); goal = $$;}                                 
  | class_main class_s { $$ = new CProgram($1, $2); goal = $$;}                                 
;

class_main 
  : CLASS id LEFT_BRACE
        MAIN LEFT_PAREN STRING LEFT_BRACKET RIGHT_BRACKET id RIGHT_PAREN LEFT_BRACE
            state
        RIGHT_BRACE
    RIGHT_BRACE         { $$ = new CMain($2, $9, $12); }                                               

class_s 
: class_s class { $$ = new CClassSequence($1, $2); }
| class_s class_ext { $$ = new CClassSequence($1, $2); }
| class { $$ = new CClassSequence(nullptr, $1); }
| class_ext { $$ = new CClassSequence(nullptr, $1); }
;

class 
: CLASS id LEFT_BRACE var_s method_s RIGHT_BRACE { $$ = new CClass($2, nullptr, $4, $5); }
| CLASS id LEFT_BRACE var_s RIGHT_BRACE { $$ = new CClass($2, nullptr, $4, nullptr); }
| CLASS id LEFT_BRACE method_s RIGHT_BRACE { $$ = new CClass($2, nullptr, nullptr, $4); }
| CLASS id LEFT_BRACE RIGHT_BRACE { $$ = new CClass($2, nullptr, nullptr, nullptr); }
;

class_ext
: CLASS id EXTENDS id LEFT_BRACE var_s method_s RIGHT_BRACE { $$ = new CClass($2, $4, $6, $7); }
| CLASS id EXTENDS id LEFT_BRACE var_s RIGHT_BRACE { $$ = new CClass($2, $4, $6, nullptr); }
| CLASS id EXTENDS id LEFT_BRACE method_s RIGHT_BRACE { $$ = new CClass($2, $4, nullptr, $6); }
| CLASS id EXTENDS id LEFT_BRACE RIGHT_BRACE { $$ = new CClass($2, $4, nullptr, nullptr); }
;

var_s
: var_s var { $$ = new CVarSequence($1, $2); }
| var { $$ = new CVarSequence(nullptr, $1); }
;

var
: type id SEMICOLON { $$ = new CVar($1, $2); }
;

method_s
: method_s method { $$ = new CMethodSequence($1, $2); }
| method { $$ = new CMethodSequence(nullptr, $1); }
;

method
: PUBLIC type id LEFT_PAREN param_s RIGHT_PAREN LEFT_BRACE
var_s state_s RETURN exp SEMICOLON RIGHT_BRACE { $$ = new CMethod($2, $3, $5, $8, $9, $11); }
| PUBLIC type id LEFT_PAREN param_s RIGHT_PAREN LEFT_BRACE
var_s RETURN exp SEMICOLON RIGHT_BRACE { $$ = new CMethod($2, $3, $5, $8, nullptr, $10); }
| PUBLIC type id LEFT_PAREN param_s RIGHT_PAREN LEFT_BRACE
state_s RETURN exp SEMICOLON RIGHT_BRACE { $$ = new CMethod($2, $3, $5, nullptr, $8, $10); }
| PUBLIC type id LEFT_PAREN param_s RIGHT_PAREN LEFT_BRACE
RETURN exp SEMICOLON RIGHT_BRACE { $$ = new CMethod($2, $3, $5, nullptr, nullptr, $9); }

param_s
: {}
| param_s COMMA type id { $$ = new CVarSequence($1, new CVar($3, $4)); }
| type id { $$ = new CVarSequence(nullptr, new CVar($1, $2)); }
;

type
: INT LEFT_BRACKET RIGHT_BRACKET { $$ = new IntArrayType(); }
| BOOL { $$ = new BoolType(); }
| INT { $$ = new IntType(); }
| id { $$ = new ClassType($1); }
;

state_s
: state_s state { $$ = new CStatementSequence($1, $2); }
| state { $$ = new CStatementSequence(nullptr, $1); }
;

state
: LEFT_BRACE state_s RIGHT_BRACE {$$ = new BracedSequenceStatement($2); } 
| IF LEFT_PAREN exp RIGHT_PAREN state ELSE state { $$ = new IfElseStatement($3, $5, $7); }
| WHILE LEFT_PAREN exp RIGHT_PAREN state { $$ = new WhileStatement($3, $5); }
| PRINT LEFT_PAREN exp RIGHT_PAREN SEMICOLON { $$ = new PrintStatement($3); }
| id EQUALS exp SEMICOLON { $$ = new AssignStatement($1, $3); }
| id LEFT_BRACKET exp RIGHT_BRACKET EQUALS exp SEMICOLON  { $$ = new ArrayAssignStatement($1, $3, $6); }
;

exp_s
: exp_s COMMA exp { $$ = new CExpressionSequence($1, $3); }
| exp { $$ = new CExpressionSequence(nullptr, $1); }
;

exp
: exp AND exp { $$ = new AndExpression($1, $3); }
| exp LOWER exp { $$ = new LowerExpression($1, $3); }
| exp PLUS exp { $$ = new PlusExpression($1, $3); }
| exp MINUS exp { $$ = new MinusExpression($1, $3); }
| exp ASTER exp { $$ = new AsterExpression($1, $3); }
| exp LEFT_BRACKET exp RIGHT_BRACKET { $$ = new ArrayExpression($1, $3); }
| exp DOT LENGTH { $$ = new LengthExpression($1); }
| exp DOT id LEFT_PAREN exp_s RIGHT_PAREN { $$ = new CallExpression($1, $3, $5); }
| exp DOT id LEFT_PAREN RIGHT_PAREN  { $$ = new CallExpression($1, $3, nullptr); }
| INTEGER_LITERAL { $$ = new IntegerExpression(yylval.intValue); }
| TRUE { $$ = new BoolExpression(true); }
| FALSE { $$ = new BoolExpression(false); }
| id { $$ = new IdExpression($1); }
| THIS { $$ = new ThisExpression(); }
| NEW INT LEFT_BRACKET exp RIGHT_BRACKET { $$ = new NewArrayExpression($4); }
| NEW id LEFT_PAREN RIGHT_PAREN { $$ = new NewExpression($2); }
| EXMARK exp { $$ = new NotExpression($2); }
| LEFT_PAREN exp RIGHT_PAREN { $$ = new ParenExpression($2); }
;

id
: ID { $$ = new CId(std::string(yylval.stringValue)); }
;

%%
void yyerror(const char* s) {
    printf("error %s", s);
}
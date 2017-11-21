%{
void update_location();
#define YY_USER_ACTION update_location();

#include <cstdio>
#include <cstdlib>
#include "IVisitor.h"
#include "bison.tab.h"

static int pos_x = 1;
static int pos_y = 1;

%}

%option noyywrap

DIGIT                         [0-9]
LETTER                        [a-zA-Z_]
ID                            {LETTER}({DIGIT}+|{LETTER})*
INTEGER_LITERAL               [1-9]{DIGIT}*|0

LEFT_BRACKET                   "["
RIGHT_BRACKET                  "]"
LEFT_BRACE                     "{"
RIGHT_BRACE                    "}"
LEFT_PAREN                     "("
RIGHT_PAREN                    ")"

PLUS                          "+"
MINUS                         "-"
ASTER                         "*"
AND                           "&&"
LOWER                         "<"
EQUALS                        "="
EXMARK                        "!"
DOT                           "."
SEMICOLON                     ";"
COMMA                         ","

CLASS                         "class"
IF                            "if"
ELSE                          "else"
WHILE                         "while"
NEW                           "new"
THIS                          "this"
TRUE                          "true"
FALSE                         "false"
PUBLIC                        "public"
RETURN                        "return"
EXTENDS                       "extends"
INT                           "int"
BOOL                          "boolean"
STRING                        "String"
LENGTH                        "length"

MAIN                          "public static void main"
PRINT                         "System.out.println"

COMMENT                       \/\/(.*)
DELIM                         [ \t\r]+

%%
\n                            { }
{COMMENT}                     { }
{DELIM}                       { }

{LEFT_BRACKET}                {return LEFT_BRACKET;}
{RIGHT_BRACKET}               {return RIGHT_BRACKET;}
{LEFT_BRACE}                  {return LEFT_BRACE;}
{RIGHT_BRACE}                 {return RIGHT_BRACE;}
{LEFT_PAREN}                  {return LEFT_PAREN;}
{RIGHT_PAREN}                 {return RIGHT_PAREN;}

{AND}                         {return AND;}
{LOWER}                       {return LOWER;}
{PLUS}                        {return PLUS;}
{MINUS}                       {return MINUS;}
{ASTER}                       {return ASTER;}
{EQUALS}                      {return EQUALS;}
{EXMARK}                      {return EXMARK;}
{DOT}                         {return DOT;}
{SEMICOLON}                   {return SEMICOLON;}
{COMMA}                       {return COMMA;}

{CLASS}                       {return CLASS;}
{IF}                          {return IF;}
{ELSE}                        {return ELSE;}
{WHILE}                       {return WHILE;}
{NEW}                         {return NEW;}
{THIS}                        {return THIS;}
{TRUE}                        {return TRUE;}
{FALSE}                       {return FALSE;}
{PUBLIC}                      {return PUBLIC;}
{RETURN}                      {return RETURN;}
{EXTENDS}                     {return EXTENDS;}
{INT}                         {return INT;}
{BOOL}                        {return BOOL;}
{STRING}                      {return STRING;}
{LENGTH}                      {return LENGTH;}

{MAIN}                        {return MAIN;}
{PRINT}                       {return PRINT;}
{ID}                          {yylval.stringValue = yytext; return ID;}
{INTEGER_LITERAL}             {yylval.intValue = atoi(yytext); return INTEGER_LITERAL;}

.                             {printf("???? !!!!");}

%%

void update_location()
{
    yylloc.first_line = pos_y;
    yylloc.first_column = pos_x;

    if (*yytext == '\n') 
    {
        pos_y += 1;
        pos_x = 1;
    }  
    else 
    {
        pos_x += strlen(yytext);
    }
    
    yylloc.last_line = pos_y;
    yylloc.last_column = pos_x;
}


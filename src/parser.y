%code requires {

# define YYLTYPE_IS_DECLARED 1 /* alert the parser that we have our own definition */
#include "Node.h"
#include "Block.h"
#include "Identifier.h"
#include "Function.h"
#include "Iteration.h"
#include "ExpressionStatement.h"
#include "Operation.h"
#include "Class.h"
#include "Condition.h"
#include "Types.h"

}

%{
    #include<string>
    
    extern int yylex();
    int yyerror(char const * s );

    // using namespace monk;
    #include "Block.h"
    
    monk::Block* programBlock;
   
%}

%union {
    monk::Node* node;
    monk::Block* block;
    monk::Expression* expression;
    monk::Statement* statement;
    monk::Identifier* identifier;
    monk::VarDecl* var_decl;
    monk::FuncVars* func_vars;
    monk::IterateCondition* iterate_condition;
    std::string *string;
    double number;
    int boolean;
    int token;
}

%token <string> TID
%token <number> TNUMBER
%token <boolean> TBOOL
%token <token> TIF TELSE
%token <token> TNOT TAND TOR
%token <token> TFUNCTION TCLASS
%token <token> TCREATE TSET TRET  TINC TDEC TBY 
%token <token> TITERATE TUNTIL TFROM TTO TTHROUGH
%token <token> TASSIGN TADD TSUB TMUL TDIV TCOMMA
%token <token> TLCBRACE TRCBRACE TLPAREN TRPAREN

%type <identifier> identifier
%type <statement> statement func_decl iterate condition class_decl return unary_operation
%type <block> program statements block
%type <expression> expression value
%type <var_decl> var_assign
%type <token> operators unary_operators
%type <func_vars> func_args
%type <iterate_condition> iterate_condition

%start program

%%

program: statements {programBlock = $1;};

identifier: TID {$$ = new monk::Identifier($1);};

statements  : statement            {$$ = new monk::Block(); $$->add_statement($1);}
            | statements statement {$1->add_statement($2);};

statement : expression
          | func_decl
          | iterate
          | class_decl
          | return
          | unary_operation
          | condition {$$ = new monk::ExpressionStatement($1);};

block : TLCBRACE statements TRCBRACE {$$ = $2;};

var_assign: TSET identifier TASSIGN expression {$$ = new monk::VarDecl($2, $4);};

operators : TADD | TSUB | TMUL | TDIV
          | TAND | TOR  | TNOT;

unary_operators: TINC | TDEC;

unary_operation: unary_operators identifier {$$ = new monk::UnaryOperation($1, $2);}
                | unary_operators identifier TBY expression {$$ = new monk::UnaryOperation($1, $2, $4);};

value: TNUMBER {$$ = new monk::Number($1);}
      | TBOOL {$$ = new monk::Boolean($1);};

expression  : identifier                           
            | value                                            
            // Assignment
            | var_assign            {$$ = $1;}
            // Binary Operation
            | expression operators expression {$$ = new monk::BinaryOperation($1, $2, $3);};

func_args   : %empty         {$$ = new monk::FuncVars();}
            | identifier     {$$ = new monk::FuncVars(); $$->add_identifier($1);}
            | var_assign     {$$ = new monk::FuncVars(); $$->add_var($1);}
            | func_args TCOMMA var_assign {$1->add_var($3);}
            | func_args TCOMMA identifier {$1->add_identifier($3);};

func_decl: TCREATE TFUNCTION identifier TLPAREN func_args TRPAREN block {$$ = new monk::FuncDecl($3, $5, $7);};

return: TRET           {$$ = new monk::Return();};
      | TRET expression {$$ = new monk::Return($2);};

class_decl: TCREATE TCLASS identifier block {$$ = new monk::ClassDecl($3, $4);};


iterate_condition   : TUNTIL expression {$$ = new monk::IterateCondition($2);}
                    | TTHROUGH expression {$$ = new monk::IterateCondition($2);}
                    | TFROM expression TTO expression {$$ = new monk::IterateCondition($2, $4);};

iterate : TITERATE iterate_condition block {$$ = new monk::Iteration($2, $3);};

condition   : TIF expression block TELSE block {$$ = new monk::Condition($2, $3, $5);}
            | TIF expression block {$$ = new monk::Condition($2, $3);};
%%

            



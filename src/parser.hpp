/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_HOME_CHARAN_PROJECTS_MONK_MONK_BUILD_PARSER_HPP_INCLUDED
# define YY_YY_HOME_CHARAN_PROJECTS_MONK_MONK_BUILD_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/home/charan/Projects/monk/monk/src/parser.y"


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


#line 64 "/home/charan/Projects/monk/monk/build/parser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TID = 258,
    TNUMBER = 259,
    TBOOL = 260,
    TIF = 261,
    TELSE = 262,
    TNOT = 263,
    TAND = 264,
    TOR = 265,
    TFUNCTION = 266,
    TCLASS = 267,
    TCREATE = 268,
    TSET = 269,
    TRET = 270,
    TINC = 271,
    TDEC = 272,
    TBY = 273,
    TITERATE = 274,
    TUNTIL = 275,
    TFROM = 276,
    TTO = 277,
    TTHROUGH = 278,
    TASSIGN = 279,
    TADD = 280,
    TSUB = 281,
    TMUL = 282,
    TDIV = 283,
    TCOMMA = 284,
    TLCBRACE = 285,
    TRCBRACE = 286,
    TLPAREN = 287,
    TRPAREN = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "/home/charan/Projects/monk/monk/src/parser.y"

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

#line 124 "/home/charan/Projects/monk/monk/build/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_CHARAN_PROJECTS_MONK_MONK_BUILD_PARSER_HPP_INCLUDED  */

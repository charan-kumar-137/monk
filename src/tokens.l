%{
    #include <string>
    #include "Node.h"
    #include "parser.hpp"
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define SAVE_NUMBER yylval.number = std::stod(std::string(yytext, yyleng))
    #define SAVE_BOOLEAN yylval.boolean = std::string(yytext, yyleng) == "True" ? 1 : 0
    #define TOKEN(t) (yylval.token = t)

    extern "C" int yywrap() { return 1; }

    int yyerror(char const * s )
    {
        printf("ERROR %s in '%s' at line %d col %d\n", s, yytext, yylineno);
        return 1;
    }
%}

DIG         [0-9]
NUMBER1     [-+]?{DIG}+\.([eE][-+]?{DIG}+)?
NUMBER2     [-+]?{DIG}*\.{DIG}+([eE][-+]?{DIG}+)?
NUMBER      {NUMBER1}|{NUMBER2}

%%

"If"                  return TOKEN(TIF);
"Else"                return TOKEN(TELSE);

"NOT"                 return TOKEN(TNOT);
"AND"                 return TOKEN(TAND);
"OR"                  return TOKEN(TOR);

"Function"            return TOKEN(TFUNCTION);
"Class"               return TOKEN(TCLASS);

"Create"              return TOKEN(TCREATE);
"Return"              return TOKEN(TRET );
"Increment"           return TOKEN(TINC);
"Decrement"           return TOKEN(TDEC);
"By"                  return TOKEN(TBY);
"Set"                 return TOKEN(TSET);

"Iterate"             return TOKEN(TITERATE);
"Until"               return TOKEN(TUNTIL);
"From"                return TOKEN(TFROM);
"To"                  return TOKEN(TTO);
"Through"             return TOKEN(TTHROUGH);

"="                   return TOKEN(TASSIGN);
"+"                   return TOKEN(TADD);
"-"                   return TOKEN(TSUB);
"*"                   return TOKEN(TMUL);
"/"                   return TOKEN(TDIV);
","                   return TOKEN(TCOMMA);

"{"                   return TOKEN(TLCBRACE);
"}"                   return TOKEN(TRCBRACE);
"("                   return TOKEN(TLPAREN);
")"                   return TOKEN(TRPAREN);

"True"                SAVE_BOOLEAN; return TBOOL;
"False"               SAVE_BOOLEAN; return TBOOL;

[a-zA-Z_]+            SAVE_TOKEN; return TID;
                      
{NUMBER}              SAVE_NUMBER; return TNUMBER;

[ \t\n]                 /* Skip  */;
.                     printf("line %d, len %d Unknown token %s !\n", yylineno, yyleng, yytext); yyterminate();


%%

#include "Block.h"
#include "CodeGenContext.h"
#include "PrettyPrint.h"
#include <iostream>
#include <stdio.h>

extern int yyparse();
extern FILE *yyin;
extern monk::Block *programBlock;

int main(int argc, char **argv) {

  if (argc > 1) {
    yyin = fopen(argv[1], "r");
  } else {
    yyin = stdin;
  }

  if (yyin == nullptr) {
    printf("File Not Found: %s", argv[1]);
    return -1;
  }

  printf("Parsing %s\n", argv[1]);
  int parse_status = yyparse();
  printf("Parse Status: %d\n", parse_status);
  if (parse_status == 0) {
    printf("Parsed -> \n\n");
    monk::PrettyPrint pp(&std::cout);
    programBlock->Accept(&pp);
    monk::CodeGenContext context(std::cout);
    std::cout << context.generateCode(*programBlock);
  }

  return 0;
}
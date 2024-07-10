
#include "Block.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/IR/Value.h"
#include <cstdio>
#include <string>

namespace monk {
void Block::add_statement(Statement *statement) {
  statements.push_back(statement);
}

llvm::Value *Block::codegen(CodeGenContext &context) {
  llvm::Value *last = nullptr;

  for (Statement *stmt : this->statements) {
    last = stmt->codegen(context);
  }

  printf("Completed Block %p \n ", last);
  return last;
}

void Block::Accept(Visitor *v) { v->VisitBlock(this); }

std::string Block::toString() { return "Block"; }

NodeType Block::get_type() { return NodeType::BLOCK; }

StatementList Block::get_statements() { return this->statements; }
} // namespace monk

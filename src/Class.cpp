#include "Class.h"
#include "Node.h"
#include "Visitor.h"
#include <string>

namespace monk {

ClassDecl::ClassDecl(Identifier *identifier, Block *block) {
  this->identifier = identifier;
  this->block = block;
}

void ClassDecl::Accept(Visitor *v) { v->VisitClassDecl(this); }

llvm::Value *ClassDecl::codegen(CodeGenContext& context) {
  return nullptr;
}

std::string ClassDecl::toString() { return "Class"; }

NodeType ClassDecl::get_type(){
  return NodeType::CLASS_DECL;
}

Block *ClassDecl::get_block() { return this->block; }

Identifier *ClassDecl::get_identifier() { return this->identifier; }

} // namespace monk
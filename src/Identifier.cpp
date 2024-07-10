#include "Identifier.h"
#include "CodeGenContext.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/IR/Instructions.h"

namespace monk {
Identifier::Identifier(std::string *name) { this->name = name; }

void Identifier::Accept(Visitor *v) { v->VisitIdentifier(this); }

llvm::Value *Identifier::codegen(CodeGenContext &context) {
  llvm::AllocaInst *alloc = context.find_variable(this);
  if (alloc != nullptr) {
    return new llvm::LoadInst(alloc->getAllocatedType(), alloc, *this->name,
                              false, context.get_current_block());
  }

  return alloc;
}

std::string Identifier::toString() { return "Identifier(" + *name + ")"; }

NodeType Identifier::get_type() { return NodeType::IDENTIFIER; }

std::string *Identifier::get_name() { return this->name; }
} // namespace monk

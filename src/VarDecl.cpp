#include "VarDecl.h"
#include "CodeGenContext.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include <string>

namespace monk {

VarDecl::VarDecl(Identifier *identifier, Expression *expression) {
  this->identifier = identifier;
  this->expression = expression;
}

llvm::Value *VarDecl::codegen(CodeGenContext &context) {
  llvm::Value *value = nullptr;

  if (context.find_variable(this->identifier)) {
    // Already Exists
    context.add_error("Variable Already Exists");
    return nullptr;
  }

  llvm::Type *type = llvm::Type::getDoubleTy(context.getGlobalContext());

  llvm::AllocaInst *alloc = new llvm::AllocaInst(
      type, 0, identifier->get_name()->c_str(), context.get_current_block());
  
  value = alloc;
  context.add_variable(identifier, alloc);

  value = expression->codegen(context);


  return new llvm::StoreInst(value, alloc, false, context.get_current_block());
}

void VarDecl::Accept(Visitor *v) { v->VisitVarDecl(this); }

Identifier *VarDecl::get_identifier() { return this->identifier; }
Expression *VarDecl::get_expression() { return this->expression; }

std::string VarDecl::toString() { return "VarDecl"; }

NodeType VarDecl::get_type() { return NodeType::VAR_DECL; }

} // namespace monk
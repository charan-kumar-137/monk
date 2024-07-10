#include "Types.h"
#include "CodeGenContext.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include <string>

namespace monk {
Number::Number(double val) { this->val = val; }

llvm::Value *Number::codegen(CodeGenContext &context) {
  return llvm::ConstantFP::get(
      llvm::Type::getDoubleTy(context.getGlobalContext()),
      llvm::APFloat(this->val));
}

void Number::Accept(Visitor *v) { v->VisitNumber(this); }

std::string Number::toString() { return "Number(" + std::to_string(val) + ")"; }

NodeType Number::get_type(){
  return NodeType::NUMBER;
}

Boolean::Boolean(int boolean) { this->boolean = boolean; }

llvm::Value *Boolean::codegen(CodeGenContext &context) {
  return llvm::ConstantFP::get(
      llvm::Type::getInt1Ty(context.getGlobalContext()), this->boolean);
}

void Boolean::Accept(Visitor *v) { v->VisitBoolean(this); }

std::string Boolean::toString() {
  std::string val = (boolean == 1 ? "True" : "False");
  return "Boolean(" + val + ")";
}

NodeType Boolean::get_type(){
  return NodeType::BOOLEAN;
}
} // namespace monk

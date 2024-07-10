#include "Operation.h"
#include "CodeGenContext.h"
#include "Node.h"
#include "Visitor.h"
#include "parser.hpp"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Value.h"
#include <llvm/Support/ManagedStatic.h>
#include <string>

namespace monk {

BinaryOperation::BinaryOperation(Expression *lhs, int op, Expression *rhs) {
  this->lhs = lhs;
  this->op = op;
  this->rhs = rhs;
}

void BinaryOperation::Accept(Visitor *v) { v->VisitBinaryOperation(this); }

Expression *BinaryOperation::get_lhs() { return this->lhs; }
Expression *BinaryOperation::get_rhs() { return this->rhs; }

llvm::Value *BinaryOperation::codegen(CodeGenContext &context) {
  llvm::Value *lhsVal = this->lhs->codegen(context);
  llvm::Value *rhsVal = this->rhs->codegen(context);

  if (!lhsVal || !rhsVal) {
    context.add_error("Invalid Result of Binary Operation");
    return nullptr;
  }

  switch (this->op) {
  case TADD:
    return context.getBuilder()->CreateFAdd(lhsVal, rhsVal, "add");
  case TSUB:
    return context.getBuilder()->CreateFSub(lhsVal, rhsVal, "sub");
  case TMUL:
    return context.getBuilder()->CreateFMul(lhsVal, rhsVal, "mul");
  case TDIV:
    return context.getBuilder()->CreateFDiv(lhsVal, rhsVal, "div");
  }

  context.add_error("No Operation ");

  return nullptr;
}

std::string BinaryOperation::toString() {
  std::string op = "";

  switch (this->op) {
  case TADD:
    op = "+";
    break;
  case TSUB:
    op = "-";
    break;
  case TMUL:
    op = "*";
    break;
  case TDIV:
    op = "/";
    break;
  }

  return "BinaryOperation(" + op + ")";
}

NodeType BinaryOperation::get_type() { return NodeType::BINARY_OPERATION; }

UnaryOperation::Operation UnaryOperation::get_op(int op) {

  switch (op) {
  case TINC:
    return Operation::INC;
  case TDEC:
    return Operation::DEC;
  }
}

UnaryOperation::UnaryOperation(int op, Identifier *identifier, Expression *by) {
  this->operation = get_op(op);
  this->identifier = identifier;
  this->by = by;
}

void UnaryOperation::Accept(Visitor *v) { v->VisitUnaryOperation(this); }

Identifier *UnaryOperation::get_identifier() { return this->identifier; }
Expression *UnaryOperation::get_by() { return this->by; }

llvm::Value *UnaryOperation::codegen(CodeGenContext &context) {
  return nullptr;
}

std::string UnaryOperation::toString() {
  std::string op = "";
  switch (this->operation) {
  case monk::UnaryOperation::INC:
    op = "++";
    break;
  case monk::UnaryOperation::DEC:
    op = "--";
    break;
  }

  return "UnaryOperation(" + op + ")";
}

NodeType UnaryOperation::get_type() { return NodeType::UNARY_OPERATION; }

} // namespace monk
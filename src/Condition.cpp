#include "Condition.h"
#include "CodeGenContext.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include <string>

namespace monk {

Condition::Condition(Expression *condition, Block *if_block,
                     Block *else_block) {
  this->condition = condition;
  this->if_block = if_block;
  this->else_block = else_block;
}

void Condition::Accept(Visitor *v) { v->VisitCondition(this); }

llvm::Value *Condition::codegen(CodeGenContext &context) {
  llvm::Value *value = condition->codegen(context);

  if (!value) {
    context.add_error("Not a Boolean Condition");
    return nullptr;
  }

  value = context.getBuilder()->CreateFCmpONE(
      value,
      llvm::ConstantFP::get(context.getGlobalContext(), llvm::APFloat(1.0)),
      "cond");

  llvm::Function *function = context.get_current_block()->getParent();

  llvm::BasicBlock *ifBlock =
      llvm::BasicBlock::Create(context.getGlobalContext(), "if", function);
  llvm::BasicBlock *elseBlock =
      llvm::BasicBlock::Create(context.getGlobalContext(), "else");

  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(context.getGlobalContext(), "merge");

  llvm::BranchInst::Create(ifBlock, elseBlock, value,
                           context.get_current_block());

  context.getBuilder()->SetInsertPoint(ifBlock);
  context.new_scope(ifBlock);

  llvm::Value *ifVal = if_block->codegen(context);
  if (ifVal == nullptr) {
    return nullptr;
  }

  context.getBuilder()->CreateBr(mergeBlock);
  ifBlock = context.getBuilder()->GetInsertBlock();

  context.end_scope();

  context.new_scope(elseBlock);

  llvm::Value *elseVal = nullptr;
  if (else_block != nullptr) {
    function->insert(function->end(), elseBlock);
    context.getBuilder()->SetInsertPoint(elseBlock);
    elseVal = else_block->codegen(context);
    if (elseVal == nullptr) {
      return nullptr;
    }

    context.getBuilder()->CreateBr(mergeBlock);
    elseBlock = context.getBuilder()->GetInsertBlock();
  }

  context.end_scope();

  context.new_scope(mergeBlock);
  function->insert(function->end(), mergeBlock);
  context.getBuilder()->SetInsertPoint(mergeBlock);

  llvm::PHINode *pn =
      llvm::PHINode::Create(llvm::Type::getDoubleTy(context.getGlobalContext()),
                            2, "mergetmp", context.get_current_block());
  pn->addIncoming(ifVal, ifBlock);
  pn->addIncoming(elseVal, elseBlock);
  llvm::AllocaInst *alloc =
      new llvm::AllocaInst(llvm::Type::getDoubleTy(context.getGlobalContext()),
                           0, "cond_res", context.get_current_block());
  new llvm::StoreInst(pn->getValueName()->getValue(), alloc, false,
                      context.get_current_block());
  llvm::ReturnInst::Create(context.getGlobalContext(), 0,
                           context.get_current_block());

  context.end_scope();

  return 0;
}

std::string Condition::toString() { return "Condition"; }

NodeType Condition::get_type() { return NodeType::CONDITION; }

Expression *Condition::get_expression() { return this->condition; }
Block *Condition::get_if_block() { return this->if_block; }

Block *Condition::get_else_block() { return this->else_block; }

} // namespace monk
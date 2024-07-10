#include "Condition.h"
#include "CodeGenContext.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
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

  if (!value->getType()->isDoubleTy()) {
    context.add_error("Not a Boolean");
    return nullptr;
  }

  llvm::Function *function = context.get_current_block()->getParent();
  llvm::BasicBlock *ifBlock =
      llvm::BasicBlock::Create(context.getGlobalContext(), "then", function);
  llvm::BasicBlock *elseBlock =
      llvm::BasicBlock::Create(context.getGlobalContext(), "else");
  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(context.getGlobalContext(), "merge");
  llvm::BranchInst::Create(ifBlock, elseBlock, value,
                           context.get_current_block());

  bool merge_block_needed = false;
  context.new_scope(ifBlock);

  llvm::Value *ifVal = if_block->codegen(context);
  if (ifVal == nullptr) {
    return nullptr;
  }

  if (context.get_current_block()->getTerminator() == nullptr) {
    llvm::BranchInst::Create(mergeBlock, context.get_current_block());
    merge_block_needed = true;
  }

  context.end_scope();

  context.new_scope(elseBlock);

  llvm::Value *elseVal = nullptr;
  if (else_block != nullptr) {
    elseVal = else_block->codegen(context);
    if(elseVal == nullptr) {
      return nullptr;
    }
  }

  if (context.get_current_block()->getTerminator() == nullptr) {
    llvm::BranchInst::Create(mergeBlock, context.get_current_block());
    merge_block_needed = true;
  }

  context.end_scope();

  if (merge_block_needed) {
    context.set_current_block(mergeBlock);
  }

  return mergeBlock;
}

std::string Condition::toString() { return "Condition"; }

NodeType Condition::get_type() { return NodeType::CONDITION; }

Expression *Condition::get_expression() { return this->condition; }
Block *Condition::get_if_block() { return this->if_block; }

Block *Condition::get_else_block() { return this->else_block; }

} // namespace monk
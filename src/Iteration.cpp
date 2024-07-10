#include "Iteration.h"
#include "Node.h"
#include "Visitor.h"
#include <string>

namespace monk {

IterateCondition::IterateCondition(Expression *expression, Expression *to) {
  if (to != nullptr) {
    this->from = expression;
    this->to = to;
    this->type = RANGE;
  } else {
    this->expression = expression;
    this->type = EXPRESSION;
  }
}

void IterateCondition::Accept(Visitor *v) { v->VisitIterateCondition(this); }

IterateCondition::Type IterateCondition::get_iterate_type() {
  return this->type;
}

Expression *IterateCondition::get_expression() { return this->expression; }
Expression *IterateCondition::get_from() { return this->from; }
Expression *IterateCondition::get_to() { return this->to; }

llvm::Value *IterateCondition::codegen(CodeGenContext& context) {
  return nullptr;
}

std::string IterateCondition::toString() {
  switch (type) {
  case EXPRESSION:
    return "Expression[Until|Exp]";
  case RANGE:
    return "Range";
  }
}

NodeType IterateCondition::get_type() { return NodeType::ITERATE_CONDITION; }

Iteration::Iteration(IterateCondition *condition, Block *block) {
  this->condition = condition;
  this->block = block;
}

void Iteration::Accept(Visitor *v) { v->VisitIteration(this); }

IterateCondition *Iteration::get_condition() { return this->condition; }
Block *Iteration::get_block() { return this->block; }

llvm::Value *Iteration::codegen(CodeGenContext& context) {
  return nullptr;
}

std::string Iteration::toString() { return "Iteration"; }

NodeType Iteration::get_type() { return NodeType::ITERATION; }

} // namespace monk
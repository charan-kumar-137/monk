#ifndef ITERATION_H
#define ITERATION_H

#include "Block.h"
#include "Node.h"

namespace monk {
class IterateCondition : public Statement {

public:
  using Type = enum { EXPRESSION, RANGE };

  IterateCondition(Expression *expression, Expression *to = nullptr);
  virtual ~IterateCondition() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  IterateCondition::Type get_iterate_type();
  Expression *get_expression();
  Expression *get_from();
  Expression *get_to();

private:
  Expression *expression;
  Expression *from;
  Expression *to;
  IterateCondition::Type type;
};

class Iteration : public Statement {

public:
  Iteration(IterateCondition *condition, Block *block);
  virtual ~Iteration() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  IterateCondition *get_condition();
  Block *get_block();

private:
  IterateCondition *condition;
  Block *block;
};
} // namespace monk

#endif /* ITERATION_H */
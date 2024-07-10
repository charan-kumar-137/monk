#ifndef CONDITION_H
#define CONDITION_H

#include "Block.h"
#include "Node.h"

namespace monk {

class Condition : public Statement {
private:
  Expression *condition;
  Block *if_block;
  Block *else_block;

public:
  Condition(Expression *condition, Block *if_block,
            Block *else_block = nullptr);
  virtual ~Condition() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Expression *get_expression();
  Block *get_if_block();
  Block *get_else_block();
};

} // namespace monk

#endif /* CONDITION_H */
#ifndef EXPRESSION_STATEMENT_H
#define EXPRESSION_STATEMENT_H

#include "Node.h"

namespace monk {

class ExpressionStatement : public Statement {

public:
  ExpressionStatement(Expression *expression);
  virtual ~ExpressionStatement() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;
  
  Expression *get_expression();

private:
  Expression *expression;
};

} // namespace monk

#endif /* EXPRESSION_STATEMENT_H */
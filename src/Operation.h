#ifndef OPERATION_H
#define OPERATION_H

#include "Identifier.h"
#include "Node.h"

namespace monk {

class BinaryOperation : public Expression {
private:
  Expression *lhs;
  Expression *rhs;
  int op;

public:
  BinaryOperation(Expression *lhs, int op, Expression *rhs);
  virtual ~BinaryOperation() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Expression *get_lhs();
  Expression *get_rhs();
};

class UnaryOperation : public Statement {

public:
  using Operation = enum { INC, DEC };
  UnaryOperation(int op, Identifier *identifier, Expression *by = nullptr);

  virtual ~UnaryOperation() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Identifier *get_identifier();
  Expression *get_by();

private:
  Operation operation;
  Identifier *identifier;
  Expression *by;

  Operation get_op(int op);
};

} // namespace monk

#endif /* OPERATION_H */
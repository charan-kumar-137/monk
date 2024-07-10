#ifndef TYPES_H
#define TYPES_H

#include "Node.h"

namespace monk {
class Number : public Expression {

public:
  Number(double val);
  virtual ~Number() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

private:
  double val;
};

class Boolean : public Expression {

public:
  Boolean(int boolean);
  virtual ~Boolean() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

private:
  int boolean;
};
} // namespace monk

#endif /* TYPES_H */
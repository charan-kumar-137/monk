#ifndef NODE_H
#define NODE_H

#include "Visitor.h"
#include "llvm/IR/Value.h"
#include <ostream>
#include <string>
#include <vector>

namespace monk {

class CodeGenContext;

enum NodeType {
  EXPRESSION,
  STATEMENT,
  BLOCK,
  CLASS_DECL,
  CONDITION,
  EXPRESSION_STATEMENT,
  FUNC_VARS,
  FUNC_DECL,
  RETURN,
  IDENTIFIER,
  ITERATE_CONDITION,
  ITERATION,
  BINARY_OPERATION,
  UNARY_OPERATION,
  NUMBER,
  BOOLEAN,
  VAR_DECL,
};

class Node;

using StatementList = std::vector<class Statement *>;
using VariableList = std::vector<class VarDecl *>;

class Node {
public:
  virtual ~Node() = default;

  virtual void Accept(Visitor *v) = 0;
  virtual llvm::Value *codegen(CodeGenContext &context) = 0;
  virtual std::string toString();
  virtual NodeType get_type() = 0;
};

class Expression : public Node {

public:
  virtual ~Expression() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext &context) override = 0;
  virtual std::string toString() override;
  virtual NodeType get_type() override;
};

class Statement : public Expression {
public:
  virtual ~Statement() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext &context) override = 0;
  virtual std::string toString() override;
  virtual NodeType get_type() override;
};

} // namespace monk

#endif /* NODE_H */
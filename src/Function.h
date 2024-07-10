#ifndef FUNCTION_H
#define FUNCTION_H

#include "Block.h"
#include "Identifier.h"
#include "Node.h"
#include "VarDecl.h"

namespace monk {

class FuncVars : public Expression {

public:
  virtual ~FuncVars() = default;

  virtual void add_identifier(Identifier *id);
  virtual void add_var(VarDecl *var);
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  VariableList get_vars();
  IdentifierList get_identifiers();

private:
  VariableList vars;
  IdentifierList identifiers;
};

class FuncDecl : public Statement {

public:
  FuncDecl(Identifier *name, FuncVars *vars, Block *block);
  virtual ~FuncDecl() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Identifier *get_identifier();
  FuncVars *get_vars();
  Block *get_block();

private:
  Identifier *name;
  FuncVars *vars;
  Block *block;
};

class Return : public Statement {
private:
  Expression *expression;

public:
  Return(Expression *expression = nullptr);

  virtual ~Return() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Expression *get_expression();
};

} // namespace monk

#endif /* FUNCTION_H */
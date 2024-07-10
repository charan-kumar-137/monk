#ifndef VARDECL_H
#define VARDECL_H

#include "Identifier.h"
#include "Node.h"

namespace monk {
class VarDecl : public Statement {

public:
  VarDecl(Identifier *identifier, Expression *expression);
  virtual ~VarDecl() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Identifier *get_identifier();
  Expression *get_expression();

private:
  Identifier *identifier;
  Expression *expression;
};
} // namespace monk

#endif /* VARDECL_H */

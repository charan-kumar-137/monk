#ifndef BLOCK_H
#define BLOCK_H

#include "Node.h"

namespace monk {

class Block : public Expression {

public:
  virtual ~Block() = default;
  void add_statement(Statement *statement);
  void Accept(Visitor *v) override;
  virtual std::string toString() override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;
  virtual NodeType get_type() override;
  StatementList get_statements();

private:
  StatementList statements;
};
} // namespace monk

#endif /* BLOCK_H */
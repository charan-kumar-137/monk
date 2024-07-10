#ifndef CLASS_H
#define CLASS_H

#include "Block.h"
#include "Identifier.h"
#include "Node.h"

namespace monk {
class ClassDecl : public Statement {
private:
  Identifier *identifier;
  Block *block;

public:
  ClassDecl(Identifier *identifier, Block *block);
  virtual ~ClassDecl() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  Block *get_block();
  Identifier *get_identifier();
};
} // namespace monk

#endif /* CLASS_H */
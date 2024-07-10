#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "Node.h"
#include <string>

namespace monk {
using IdentifierList = std::vector<class Identifier *>;

class Identifier : public Expression {

public:
  Identifier(std::string *name);
  virtual ~Identifier() = default;
  void Accept(Visitor *v) override;
  virtual llvm::Value *codegen(CodeGenContext& context) override;;
  virtual std::string toString() override;
  virtual NodeType get_type() override;

  std::string* get_name();

private:
  std::string *name;
};
} // namespace monk

#endif /* IDENTIFIER_H */
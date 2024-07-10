#include "ExpressionStatement.h"
#include "Node.h"
#include "Visitor.h"
#include <string>

namespace monk {

ExpressionStatement::ExpressionStatement(Expression *expression) {
  this->expression = expression;
}

void ExpressionStatement::Accept(Visitor *v) {
  v->VisitExpressionStatement(this);
}

std::string ExpressionStatement::toString() { return "Expression Statement"; }

NodeType ExpressionStatement::get_type() {
  return NodeType::EXPRESSION_STATEMENT;
}

Expression *ExpressionStatement::get_expression() { return this->expression; }

llvm::Value *ExpressionStatement::codegen(CodeGenContext &context) {
  return expression->codegen(context);
}

} // namespace monk
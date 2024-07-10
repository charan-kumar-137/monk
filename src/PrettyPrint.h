#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include "Node.h"
#include "Visitor.h"
#include <ostream>

namespace monk {
class PrettyPrint : public Visitor {

public:
  PrettyPrint(std::ostream *outs);
  virtual ~PrettyPrint() = default;
  void VisitExpression(Expression *expr) override;
  void VisitStatement(Statement *stmt) override;
  void VisitBlock(Block *block) override;
  void VisitClassDecl(ClassDecl *class_decl) override;
  void VisitCondition(Condition *cond) override;
  void VisitExpressionStatement(ExpressionStatement *expr_stmt) override;
  void VisitFuncVars(FuncVars *func_vars) override;
  void VisitFuncDecl(FuncDecl *func_decl) override;
  void VisitReturn(Return *rtrn) override;
  void VisitIdentifier(Identifier *identifier) override;
  void VisitIterateCondition(IterateCondition *iterate_condition) override;
  void VisitIteration(Iteration *iteration) override;
  void VisitBinaryOperation(BinaryOperation *bin_op) override;
  void VisitUnaryOperation(UnaryOperation *un_op) override;
  void VisitNumber(Number *number) override;
  void VisitBoolean(Boolean *boolean) override;
  void VisitVarDecl(VarDecl *var_decl) override;

private:
  int current_indent = 0;
  std::ostream *outs;
  void display(Node *node);
  void indent();
  void dedent();
};
} // namespace monk

#endif /* PRETTY_PRINT_H */
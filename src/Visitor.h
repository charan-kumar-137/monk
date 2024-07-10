#ifndef VISITOR_H
#define VISITOR_H

namespace monk {

class Expression;
class Statement;
class Block;
class ClassDecl;
class Condition;
class ExpressionStatement;
class FuncVars;
class FuncDecl;
class Return;
class Identifier;
class IterateCondition;
class Iteration;
class BinaryOperation;
class UnaryOperation;
class Number;
class Boolean;
class VarDecl;

class Visitor {
public:
  virtual void VisitExpression(Expression *expr) = 0;
  virtual void VisitStatement(Statement *stmt) = 0;
  virtual void VisitBlock(Block *block) = 0;
  virtual void VisitClassDecl(ClassDecl *class_decl) = 0;
  virtual void VisitCondition(Condition *cond) = 0;
  virtual void VisitExpressionStatement(ExpressionStatement *expr_stmt) = 0;
  virtual void VisitFuncVars(FuncVars *func_vars) = 0;
  virtual void VisitFuncDecl(FuncDecl *func_decl) = 0;
  virtual void VisitReturn(Return *rtrn) = 0;
  virtual void VisitIdentifier(Identifier *identifier) = 0;
  virtual void VisitIterateCondition(IterateCondition *iterate_condition) = 0;
  virtual void VisitIteration(Iteration *iteration) = 0;
  virtual void VisitBinaryOperation(BinaryOperation *bin_op) = 0;
  virtual void VisitUnaryOperation(UnaryOperation *un_op) = 0;
  virtual void VisitNumber(Number *number) = 0;
  virtual void VisitBoolean(Boolean *boolean) = 0;
  virtual void VisitVarDecl(VarDecl *var_decl) = 0;
};

} // namespace monk

#endif /* VISITOR_H */
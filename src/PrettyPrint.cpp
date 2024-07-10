#include "PrettyPrint.h"
#include "Block.h"
#include "Class.h"
#include "Condition.h"
#include "ExpressionStatement.h"
#include "Function.h"
#include "Identifier.h"
#include "Iteration.h"
#include "Node.h"
#include "Operation.h"
#include "Types.h"
#include <ostream>

namespace monk {

static std::string indent_spaces(size_t indent) {
  return std::string(indent * 2u, '_');
}

void PrettyPrint::indent() { current_indent += 1; }

void PrettyPrint::dedent() { current_indent -= 1; }

void PrettyPrint::display(Node *node) {
  *outs << indent_spaces(current_indent) << "<" << node->toString() << ">"
        << std::endl;
}

PrettyPrint::PrettyPrint(std::ostream *outs) { this->outs = outs; }

void PrettyPrint::VisitExpression(Expression *expr) { display(expr); }

void PrettyPrint::VisitStatement(Statement *stmt) { display(stmt); }

void PrettyPrint::VisitBlock(Block *block) {
  display(block);
  indent();

  for (Statement *stmt : block->get_statements()) {
    stmt->Accept(this);
  }

  dedent();
}

void PrettyPrint::VisitClassDecl(ClassDecl *class_decl) {
  display(class_decl);
  indent();
  class_decl->get_identifier()->Accept(this);
  Block *block = class_decl->get_block();
  if (block) {
    block->Accept(this);
  }
  dedent();
}

void PrettyPrint::VisitCondition(Condition *cond) {
  display(cond);
  indent();
  Expression *exp = cond->get_expression();
  if (exp) {
    exp->Accept(this);
  }

  Block *if_block = cond->get_if_block();
  if (if_block) {
    if_block->Accept(this);
  }

  Block *else_block = cond->get_else_block();
  if (else_block) {
    else_block->Accept(this);
  }
  dedent();
}

void PrettyPrint::VisitExpressionStatement(ExpressionStatement *expr_stmt) {
  display(expr_stmt);
}

void PrettyPrint::VisitFuncVars(FuncVars *func_vars) { display(func_vars); }

void PrettyPrint::VisitFuncDecl(FuncDecl *func_decl) {
  display(func_decl);
  indent();
  func_decl->get_identifier()->Accept(this);
  FuncVars *vars = func_decl->get_vars();
  if (vars) {
    vars->Accept(this);
  }

  Block *block = func_decl->get_block();
  if (block) {
    block->Accept(this);
  }
  dedent();
}

void PrettyPrint::VisitReturn(Return *rtrn) {
  display(rtrn);

  indent();
  Expression *expression = rtrn->get_expression();
  if (expression) {
    expression->Accept(this);
  }
  dedent();
}

void PrettyPrint::VisitIdentifier(Identifier *identifier) {
  display(identifier);
}

void PrettyPrint::VisitIterateCondition(IterateCondition *iterate_condition) {
  display(iterate_condition);
  indent();
  switch (iterate_condition->get_iterate_type()) {
  case monk::IterateCondition::EXPRESSION:
    iterate_condition->get_expression()->Accept(this);
    break;
  case monk::IterateCondition::RANGE:
    iterate_condition->get_from()->Accept(this);
    iterate_condition->get_to()->Accept(this);
    break;
  }
  dedent();
}

void PrettyPrint::VisitIteration(Iteration *iteration) {
  display(iteration);

  IterateCondition *cond = iteration->get_condition();
  if (cond) {
    cond->Accept(this);
  }

  indent();
  Block *block = iteration->get_block();
  if (block) {
    block->Accept(this);
  }
  dedent();
}

void PrettyPrint::VisitBinaryOperation(BinaryOperation *bin_op) {
  display(bin_op);
  indent();
  bin_op->get_lhs()->Accept(this);
  bin_op->get_rhs()->Accept(this);
  dedent();
}

void PrettyPrint::VisitUnaryOperation(UnaryOperation *un_op) {
  display(un_op);
  indent();
  un_op->get_identifier()->Accept(this);

  Expression *by = un_op->get_by();
  if (by) {
    by->Accept(this);
  }
  dedent();
}

void PrettyPrint::VisitNumber(Number *number) { display(number); }

void PrettyPrint::VisitBoolean(Boolean *boolean) { display(boolean); }

void PrettyPrint::VisitVarDecl(VarDecl *var_decl) {
  display(var_decl);
  indent();
  var_decl->get_identifier()->Accept(this);
  var_decl->get_expression()->Accept(this);
  dedent();
}

} // namespace monk
#include "Function.h"
#include "Node.h"
#include "Visitor.h"
#include <string>

namespace monk {

void FuncVars::add_var(VarDecl *var) { vars.push_back(var); }

void FuncVars::add_identifier(Identifier *identifier) {
  identifiers.push_back(identifier);
}

void FuncVars::Accept(Visitor *v) { v->VisitFuncVars(this); }

llvm::Value *FuncVars::codegen(CodeGenContext& context) { return nullptr;}

std::string FuncVars::toString() {
  std::string s = "";

  for (auto var : identifiers) {
    s.append(var->toString() + ",");
  }

  for (auto var : vars) {
    s.append(var->toString() + ",");
  }

  return "(" + s + ")";
}

NodeType FuncVars::get_type() { return NodeType::FUNC_VARS; }

VariableList FuncVars::get_vars() { return this->vars; }

IdentifierList FuncVars::get_identifiers() { return this->identifiers; }

FuncDecl::FuncDecl(Identifier *name, FuncVars *vars, Block *block) {
  this->name = name;
  this->vars = vars;
  this->block = block;
}

void FuncDecl::Accept(Visitor *v) { v->VisitFuncDecl(this); }

llvm::Value *FuncDecl::codegen(CodeGenContext& context) { return nullptr;}


std::string FuncDecl::toString() { return "Function"; }

NodeType FuncDecl::get_type() { return NodeType::FUNC_DECL; }

Identifier *FuncDecl::get_identifier() { return this->name; }
FuncVars *FuncDecl::get_vars() { return this->vars; }
Block *FuncDecl::get_block() { return this->block; }

Return::Return(Expression *expression) { this->expression = expression; }

void Return::Accept(Visitor *v) { v->VisitReturn(this); }

llvm::Value *Return::codegen(CodeGenContext& context) { return nullptr;}

std::string Return::toString() { return "Return"; }

NodeType Return::get_type() { return NodeType::RETURN; }

Expression *Return::get_expression() { return this->expression; }

} // namespace monk
#include "Node.h"
#include "Visitor.h"
#include <string>

namespace monk {

std::string Node::toString() { return "Node"; }

void Expression::Accept(Visitor *v) { v->VisitExpression(this); }

NodeType Expression::get_type() { return NodeType::EXPRESSION; }

std::string Expression::toString() { return "Expression"; }

void Statement::Accept(Visitor *v) { v->VisitStatement(this); }

NodeType Statement::get_type() { return NodeType::STATEMENT; }

std::string Statement::toString() { return "Statement"; }
} // namespace monk
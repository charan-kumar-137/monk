#ifndef CODE_GEN_CONTEXT_H
#define CODE_GEN_CONTEXT_H

#include "Identifier.h"
#include "Node.h"
#include "Visitor.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include <list>
#include <map>
#include <ostream>
#include <string>

namespace monk {

using NameValues = std::map<std::string, llvm::AllocaInst *>;
using NameType = std::map<std::string, llvm::Type *>;

class CodeGenBlock {

public:
  CodeGenBlock(llvm::BasicBlock *block);
  ~CodeGenBlock() = default;
  void set_code_block(llvm::BasicBlock *block);
  llvm::BasicBlock *get_code_block();
  NameValues &get_values();

private:
  llvm::BasicBlock *block;
  NameValues values;
};

class CodeGenContext {

public:
  CodeGenContext(std::ostream &outs);
  llvm::Module *getModule();
  llvm::IRBuilder<> *getBuilder();

  llvm::LLVMContext &getGlobalContext();

  llvm::AllocaInst *find_variable(Identifier *);
  llvm::BasicBlock *get_current_block();
  bool generateCode(Block &block);
  void add_variable(Identifier *, llvm::AllocaInst *);
  void new_scope(llvm::BasicBlock *);
  void end_scope();
  void set_current_block(llvm::BasicBlock *);
  void add_error(std::string);
  std::list<std::string> get_errors();

private:
  // std::ostream&            outs;
  std::ostream &outs;
  std::list<CodeGenBlock *> code_blocks;
  CodeGenBlock *current_block;
  llvm::Module *module;
  llvm::LLVMContext *context;
  llvm::Function *mainFunction;
  llvm::IRBuilder<> *builder;
  std::list<std::string> errors;
};

} // namespace monk

#endif /* CODE_GEN_CONTEXT_H */
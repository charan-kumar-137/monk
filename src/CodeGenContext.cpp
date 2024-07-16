
#include "CodeGenContext.h"
#include "Block.h"
#include "Identifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <string>

namespace monk {

CodeGenBlock::CodeGenBlock(llvm::BasicBlock *block) {
  this->set_code_block(block);
}

void CodeGenBlock::set_code_block(llvm::BasicBlock *block) {
  this->block = block;
}

llvm::BasicBlock *CodeGenBlock::get_code_block() { return this->block; }

CodeGenContext::CodeGenContext(std::ostream &outs) : outs(outs) {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();
  this->context = new llvm::LLVMContext();
  this->builder = new llvm::IRBuilder<>(getGlobalContext());
  this->module = new llvm::Module("monk", getGlobalContext());
}
NameValues &CodeGenBlock::get_values() { return this->values; }

llvm::IRBuilder<> *CodeGenContext::getBuilder() { return this->builder; }

bool CodeGenContext::generateCode(Block &block) {
  outs << "Generating Code.. \n";
  std::vector<llvm::Type *> argTypes;
  llvm::FunctionType *ftype = llvm::FunctionType::get(
      llvm::Type::getVoidTy(getGlobalContext()), argTypes, false);
  mainFunction = llvm::Function::Create(
      ftype, llvm::GlobalValue::InternalLinkage, "main", getModule());
  llvm::BasicBlock *mainBlock =
      llvm::BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

  new_scope(mainBlock);

  block.codegen(*this);

  if (get_current_block()->getTerminator() == nullptr) {
    outs << "Inside nullptr ret \n";
    llvm::ReturnInst::Create(getGlobalContext(), 0, get_current_block());
  }
  end_scope();

  module->print(llvm::outs(), nullptr);

  for (std::string error : this->get_errors()) {
    outs << "Error: " << error << "\n";
  }

  if (llvm::verifyModule(*getModule(), &llvm::errs())) {
    outs << ": Error constructing function!\n";
  }

  outs << "Done\n";

  // outs << "Running code...\n";
  //  std::string      err;
  //  llvm::ExecutionEngine* ee =
  //  llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).setErrorStr(&err).setEngineKind(llvm::EngineKind::JIT).create();
  // //  assert(ee);
  // outs << err << "\n";

  //  ee->finalizeObject();
  //  std::vector<llvm::GenericValue> noargs;
  //  llvm::GenericValue         v = ee->runFunction(mainFunction, noargs);
  //  outs << "Code was run.\n";
  return true;
}

llvm::Module *CodeGenContext::getModule() { return this->module; }

llvm::LLVMContext &CodeGenContext::getGlobalContext() { return *this->context; }

llvm::AllocaInst *CodeGenContext::find_variable(Identifier *id) {
  llvm::AllocaInst *alloca = nullptr;

  for (CodeGenBlock *block : this->code_blocks) {
    if (block->get_values().count(id->get_name()->c_str())) {
      return block->get_values()[id->get_name()->c_str()];
    }
  }

  return alloca;
}

llvm::BasicBlock *CodeGenContext::get_current_block() {
  return this->code_blocks.front()->get_code_block();
}

void CodeGenContext::add_variable(Identifier *identifier,
                                  llvm::AllocaInst *alloc) {
  this->code_blocks.front()->get_values()[identifier->get_name()->c_str()] =
      alloc;
}

void CodeGenContext::new_scope(llvm::BasicBlock *block) {
  if (block == nullptr) {
    block = llvm::BasicBlock::Create(this->getGlobalContext());
  }
  this->code_blocks.push_front(new CodeGenBlock(block));
}
void CodeGenContext::end_scope() {
  CodeGenBlock *top = this->code_blocks.front();
  code_blocks.pop_front();
  delete top;
}

void CodeGenContext::set_current_block(llvm::BasicBlock *block) {
  this->code_blocks.front()->set_code_block(block);
}

void CodeGenContext::add_error(std::string error) {
  this->errors.push_back(error);
}
std::list<std::string> CodeGenContext::get_errors() { return this->errors; }

} // namespace monk
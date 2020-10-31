#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

using namespace llvm;

#define DEBUG_TYPE "hw4_cfg"

struct hw4_cfg : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  hw4_cfg() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    // TODO: write something here

    return false;
  }
};

char hw4_cfg::ID = 0;
static RegisterPass<hw4_cfg> X("hw4-cfg", "Generate control flow graph", false, false);
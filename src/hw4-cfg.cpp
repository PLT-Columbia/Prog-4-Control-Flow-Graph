#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

#include "hw4-utils.h"

using namespace llvm;

#define DEBUG_TYPE "hw4_cfg"

struct hw4_cfg : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  hw4_cfg() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    OFile ofile(F);

    // TODO: write something here
    // Use ofile.printEdge(BB1, BB2, [OFile::EdgeType::<type>]) to output the edges
    // Use ofile.printKeyBlock(BB) to output key blocks

    return false;
  }
};

char hw4_cfg::ID = 0;
static RegisterPass<hw4_cfg> X("hw4-cfg", "Generate control flow graph", false, false);
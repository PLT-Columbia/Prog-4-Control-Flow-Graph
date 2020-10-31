#pragma once

#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"

#include <fstream>
#include <iostream>
#include <type_traits>

// Please use OFile to output the results
class OFile {
public:
  enum class EdgeType {Default, T, F};

private:
  std::ostream &out;
  std::ofstream file;

  // Support BasicBlock, Function, ...
  template<typename T>
  void printEdge(std::ostream &stream, const T &from, const T &to, 
                 EdgeType type = EdgeType::Default) {
    static_assert(std::is_pointer<T>::value == false, "Don't pass a pointer to printEdge()");
    stream << "edge: " << from.getName().str();
    if (type == EdgeType::T) stream << "(T)";
    else if (type == EdgeType::F) stream << "(F)";
    stream << " ---> " << to.getName().str() << std::endl;
  }

  void printKeyBlock(std::ostream &stream, const llvm::BasicBlock &BB) {
    stream << "Key Block: " << BB.getName().str() << std::endl;
  }

public:
  OFile(const llvm::Function &F):
    file(F.getName().str() + ".txt", std::ios::out | std::ios::trunc),
    out(std::cout) {}
  
  // Support BasicBlock, Function, ...
  template<typename T>
  void printEdge(const T &from, const T &to,
                 EdgeType type = EdgeType::Default) {
    printEdge(out, from, to, type);
    printEdge(file, from, to, type);
  }

  void printKeyBlock(const llvm::BasicBlock &BB) {
    printKeyBlock(out, BB);
    printKeyBlock(file, BB);
  }
};

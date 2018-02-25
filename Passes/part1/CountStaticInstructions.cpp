#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
#include <map>

using namespace llvm;
using namespace std;

namespace {
struct CountStaticInstructions : public FunctionPass {
  static char ID;
  CountStaticInstructions() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
  	map<string, int> fun_count;
  	for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
  			fun_count[string(I -> getOpcodeName())] += 1;
  	}

  	for (map<string, int>::iterator it = fun_count.begin(); it != fun_count.end(); ++it)
  		errs() << it->first << "\t" << it->second << '\n';
    return false;
  }
}; // end of struct TestPass
}  // end of anonymous namespace

char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("cse231-csi", "count static instructions",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

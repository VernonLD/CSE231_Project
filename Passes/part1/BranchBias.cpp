#include <map>
#include <string>
#include "llvm/Pass.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using namespace std;

namespace {
struct BranchBias : public FunctionPass {
  static char ID;
  BranchBias() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
  	Module *module  = F.getParent();
  	LLVMContext &context = module->getContext();

	vector<Type *> update_params(1, Type::getInt1Ty(context));
	FunctionType *update_ft = FunctionType::get(
		Type::getVoidTy(context), update_params, false);
	Function *update_helper = cast<Function>(module->getOrInsertFunction("updateBranchInfo", 
		update_ft));
    Function *print_helper  = cast<Function>(module->getOrInsertFunction("printOutBranchInfo", 
    	Type::getVoidTy(context), NULL));

    for (Function::iterator block = F.begin(), end = F.end(); block != end; ++block) {
    	for (BasicBlock::iterator i = block->begin(), end = block->end(); i != end; ++i) {
    		IRBuilder<> builder(&*block);
    		if ((string)i->getOpcodeName() == "br" && i->getNumOperands() > 1 ) {
    			builder.SetInsertPoint(&*--block->end());
    			vector<Value *> args;
				args.push_back(i->getOperand(0));
				builder.CreateCall(update_helper, args);
    		}
	    	if ((string)i->getOpcodeName() == "ret") {
	    		builder.SetInsertPoint(&*i);
	    		builder.CreateCall(print_helper);
	    	}
	    }
    }
    return false;
  }
}; // end of struct TestPass
}  // end of anonymous namespace

char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("cse231-bb", "Developed to test LLVM and docker",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

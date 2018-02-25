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

struct CountDynamicInstructions : public FunctionPass {
  static char ID;
  CountDynamicInstructions() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
  	Module *module  = F.getParent();
  	LLVMContext &context = module->getContext();

	vector<Type *> update_params(2, IntegerType::get(context, 32));
	FunctionType *update_ft = FunctionType::get(
		Type::getVoidTy(context), update_params, false);
	// Function *update_helper = (Function *)module->getOrInsertFunction("updateInstrInfo", update_functype);

  Function *update_helper = cast<Function>(module->getOrInsertFunction("updateInstrInfo", update_ft));

	Function *print_helper = cast<Function>(module->getOrInsertFunction(
		"printOutInstrInfo", Type::getVoidTy(context), NULL));

    for (Function::iterator block = F.begin(), end = F.end(); block != end; ++block) {
    	map<int, int> fun_count;
    	for (BasicBlock::iterator i = block->begin(); i != block->end(); ++i)
    		++fun_count[i->getOpcode()];

    	IRBuilder<> builder(&*block);
    	for (map <int,int>::iterator it = fun_count.begin(); it != fun_count.end(); ++it) {
			  builder.SetInsertPoint(&*--block->end());
    		vector<Value * > update_args;
    		update_args.push_back(ConstantInt::get(Type::getInt32Ty(context), it->first));
    		update_args.push_back(ConstantInt::get(Type::getInt32Ty(context), it->second));
    		builder.CreateCall(update_helper, update_args);
    	}

	    for (BasicBlock::iterator i = block->begin(), end = block->end(); i != end; ++i) {
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

char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions> X("cse231-cdi", "Developed to test LLVM and docker",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

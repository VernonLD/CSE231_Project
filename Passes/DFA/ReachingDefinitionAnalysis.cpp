#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"

#include <cassert>
#include <set>
#include <string>

#include "231DFA.h"

using namespace llvm;
using namespace std;
namespace {
// MyInfo definition
	class MyInfo public: Info
	{
	public:
		MyInfo();
		~MyInfo();
		void print() = 0;
		static bool equals(Info * info1, Info * info2){
		}
		static Info* join(Info * info1, Info * info2, Info * result){
		}
		
	};
}

char ReachingDefinitionAnalysisPass::ID = 0;
static RegisterPass<ReachingDefinitionAnalysisPass> X("cse231-reaching", "reaching definition",false, false);

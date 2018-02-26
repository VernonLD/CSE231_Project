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
// ReachingInfo definition
	class ReachingInfo : public Info
	{
	public:
        set<unsigned> def_set;
		void print(){
            errs() << "definition"<<"\n";
            for (set<unsigned>::iterator it = def_set.begin(); it!=def_set.end(); ++it){
                errs() << *it << '|';
            }
            errs()<< "\n";
        }
		static bool equals(ReachingInfo * info1, ReachingInfo * info2){
			return info1->def_set == info2->def_set;
		}
		static void join(ReachingInfo * info1, ReachingInfo * info2, ReachingInfo * result){


		}
		
	};


    class ReachingDefinitionAnalysis : public DataFlowAnalysis<ReachingInfo, true> {
    public:
        ReachingDefinitionAnalysis(ReachingInfo &initial, ReachingInfo &bottom):
                DataFlowAnalysis(initial, bottom){}
        ~ReachingDefinitionAnalysis(){}
    private:
        void flowfunction(Instruction * I,
                          std::vector<unsigned> & IncomingEdges,
                          std::vector<unsigned> & OutgoingEdges,
                          std::vector<ReachingInfo *> & Infos) override {
            int i = 0;
            i++;
        }
    };
	
	struct ReachingDefinitionAnalysisPass : public FunctionPass
	{
		static char ID;
        ReachingDefinitionAnalysisPass() : FunctionPass(ID) {}
  		bool runOnFunction(Function &F) override {
            ReachingInfo bottom;
            ReachingDefinitionAnalysis dfa(bottom, bottom);
            dfa.runWorklistAlgorithm(&F);
            dfa.print();
            return false;
  		}
	};
}

char ReachingDefinitionAnalysisPass::ID = 0;
static RegisterPass<ReachingDefinitionAnalysisPass> X("cse231-reaching", "reaching definition",false, false);

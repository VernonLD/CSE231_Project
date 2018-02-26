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
            for (set<unsigned>::iterator it = def_set.begin(); it!=def_set.end(); ++it){
                errs() << *it << '|';
            }
            errs()<< "\n";
        }
		static bool equals(ReachingInfo * info1, ReachingInfo * info2){
			return info1->def_set == info2->def_set;
		}
		static void join(ReachingInfo * info1, ReachingInfo * info2, ReachingInfo * result){
            //result = nullptr
//            errs() << "info1"<<"\n";
            if (result != info1){
                for (auto i:info1->def_set){
                    result->def_set.insert(i);
                }
            }
//            errs() << "info2"<<"\n";
            for (auto i:info2->def_set){
                result->def_set.insert(i);
            }
//            errs() << "info3"<<"\n";
		}
		
	};


    class ReachingDefinitionAnalysis : public DataFlowAnalysis<ReachingInfo, true> {
    public:
        ReachingDefinitionAnalysis(ReachingInfo &initial, ReachingInfo &bottom):
                DataFlowAnalysis(initial, bottom){}
        ~ReachingDefinitionAnalysis(){
            for (auto it : EdgeToInfo){
//                errs() << "Edge to delete" <<it.first.first << it.first.second <<"\n";
                if (it.second != &Bottom && it.second != &InitialState){
                    delete it.second;
                }
            }
        }
    private:
        void flowfunction(Instruction * I,
                          std::vector<unsigned> & IncomingEdges,
                          std::vector<unsigned> & OutgoingEdges,
                          std::vector<ReachingInfo *> & Infos) override {
            if (I == nullptr) return;
            int op = I->getOpcode();
            unsigned index = InstrToIndex[I];
            ReachingInfo *info_new = new ReachingInfo;
            for(auto it: IncomingEdges){
                Edge e = std::make_pair(it,index);
                ReachingInfo::join(info_new, EdgeToInfo[e],info_new);
            }

            if ((op >= 11 && op<= 30)||op == 55||op == 32||op == 51||op==52){
                info_new->def_set.insert(index);
//                for (unsigned i = 0; i < Infos.size(); i++){
//                    ReachingInfo::join(Infos[i],info_new,Infos[i]);
//                }
            }

//            if (op == 2 || op == 3 || op == 31){
//                for (unsigned i = 0; i < Infos.size(); i++){
//                    ReachingInfo::join(Infos[i],info_new,Infos[i]);
//                }
//            }

            if (op == 53){
                while (true){
                    info_new->def_set.insert(index);
                    if (IndexToInstr[index+1]->getOpcode() == 53) ++ index;
                    else break;
                }
            }
            for (unsigned i = 0; i < Infos.size(); i++){
                ReachingInfo::join(Infos[i],info_new,Infos[i]);
            }
            delete info_new;
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

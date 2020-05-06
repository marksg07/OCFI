#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
using namespace llvm;

#define DEBUG_TYPE "ocfi"

//STATISTIC(HelloCounter, "Counts number of functions greeted");

namespace {
    struct OCFI : public ModulePass {
        static char ID; // Pass identification, replacement for typeid
        OCFI() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            LLVMContext& c = M.getContext();
            std::vector<BasicBlock *> bbls;
            for (Function &f : M) {
              for (BasicBlock &bbl : f) {
                bbls.push_back(bbl);
              }
            }
            M.getOrInsertFunction("__ocfi_blocks", FunctionType::get(Type::getVoidTy(c), ArrayRef<Type*>(), false));
            Function* sto = M.getFunction("__ocfi_blocks");
            for (BasicBlock *bbl : bbls) {
                bbl->removeFromParent();
                bbl->insertInto(sto);
            }
            return false;
        }
    };
}

static RegisterPass<OCFI>
Y("ocfi", "OCFI pass");

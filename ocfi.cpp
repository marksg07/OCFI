#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include <vector>
using namespace llvm;

#define DEBUG_TYPE "ocfi"

//STATISTIC(HelloCounter, "Counts number of functions greeted");

namespace {
    struct OCFI : public MachineFunctionPass {
        static char ID; // Pass identification, replacement for typeid
        OCFI() : MachineFunctionPass(ID) {}

        bool runOnMachineFunction(MachineFunction &F) override {
            //LLVMContext& c = M.getContext();
              for (MachineBasicBlock &bbl : F) {
                bbl.setLabelMustBeEmitted();
              }
            
            return false;
        }
    };
}

char OCFI::ID = 0;
static RegisterPass<OCFI>
Y("ocfi", "OCFI pass");

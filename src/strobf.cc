#include <vector>
#include <typeinfo>

#include "llvm-18/llvm/Passes/PassPlugin.h"
#include "llvm-18/llvm/Passes/PassBuilder.h"
#include "llvm-18/llvm/IR/PassManager.h"
#include "llvm-18/llvm/IR/Constants.h"
#include "llvm-18/llvm/IR/ValueSymbolTable.h"
#include "llvm-18/llvm/IR/IRBuilder.h"
#include "llvm-18/llvm/Transforms/Utils/Cloning.h"
#include "llvm-18/llvm/Support/raw_ostream.h"

using namespace llvm;

class GlobalStr {
public:
    GlobalVariable* g_Var;
    static const int SIMPLE_STRING_TYPE = 1;
    static const int STRUCT_STRING_TYPE = 2;
    unsigned int StrLength;
    int          Type;
    unsigned int Index;

    GlobalStr( GlobalVariable* g_Var, unsigned int Length ) : g_Var( g_Var ), Index( -1 ), StrLength( Length ), Type( SIMPLE_STRING_TYPE ) {}
    GlobalStr( GlobalVariable* g_Var, unsigned int Length, unsigned int Index ) : g_Var( g_Var ), Index( Index ), StrLength( Length ), Type( STRUCT_STRING_TYPE ) {}
};

char* XorStr( const char* Data, unsigned int Length ) {

}

Function* DecodeStub( 
    Module& Mod, 
    std::vector<GlobalStr>& GlobalStrs, 
    Function* DecodeFnc 
) {
    Mod.getContext();
}

struct StrObf : public PassInfoMixin<StrObf> {

};

extern "C" ::llvm::PassPluginLibraryInfo 
LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo( void ) {
    return {
        LLVM_PLUGIN_API_VERSION, "OblivStrObf", "v0.1", []( PassBuilder& PsBuilder ) {
            PsBuilder.registerPipelineParsingCallback(
                [] ( StringRef Name, ModulePassManager& ModPsMngr, ArrayRef<PassBuilder::PipelineElement> ) 
                {
                    if ( Name == "OBLIV-STR-OBF" ) 
                    {
                        ModPsMngr.addPass( StrObf() ); return true;
                    }
                    else 
                    {
                        return false;
                    }
                }
            );
        }
    };
}
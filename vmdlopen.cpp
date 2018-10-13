#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ADT/Triple.h"
#include "llvm/IRReader/IRReader.h"
#include "ExecutionEngine/MCJIT/MCJIT.h"
//#include "ExecutionEngine/JIT/JIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/SourceMgr.h"
#include <string>
extern "C" void* vmdlopen(const char* fname, int dummy);
extern "C" void* vmdlsym(void* handle, const char* symbol);
extern "C" void vmdlclose(void* p);
using namespace llvm;

namespace {

static struct AnonymousNativeTargetInitializer{
   AnonymousNativeTargetInitializer(){
      InitializeNativeTarget();
      InitializeNativeTargetAsmPrinter();
      InitializeNativeTargetAsmParser();
      llvm::MCJIT::Register();
   }
}NativeTargetInitializer;

}
struct DLModule{
   MCJIT* jit;
   Module* m;
   TargetMachine* TM;
   llvm::EngineBuilder* EB;
   SMDiagnostic Err ;
   std::string errString;
   
   DLModule(const char* filename){ 
//      llvm::JIT::Register();
      LLVMContext& Context = getGlobalContext();
      m = NULL;
      m = llvm::ParseIRFile(filename,Err,Context);
      if(m){ 
         EB = new llvm::EngineBuilder(m);
         EB->setOptLevel( CodeGenOpt::Default);
         EB->setUseMCJIT(true);
         EB->setCodeModel(CodeModel::JITDefault);
         EB->setEngineKind(EngineKind::JIT);
         EB->setErrorStr(&errString);
         EB->setOptLevel(CodeGenOpt::Default);
         EB->setMCJITMemoryManager(new SectionMemoryManager());
         Triple triple(sys::getDefaultTargetTriple());
         EB->setMArch("x86");
         EB->setMCPU(sys::getHostCPUName()); 
         //TM = EB.selectTarget();
         ExecutionEngine* ee = EB->create();
         //ee->addModule(m);
         ee->runStaticConstructorsDestructors(false);
         this->jit = (MCJIT*)(ee);
      }
   }
   ~DLModule(){
      delete jit;
   }
   void* getPointerToFunction(const char* fnName){
      return (void*)jit->getFunctionAddress(fnName);
   }
};

extern "C" void* vmdlopen(const char* fname, int dummy){
   DLModule* dlret = new DLModule(fname);
   if(dlret->m == NULL){
      dlret->Err.print(fname, errs()); 
   }
   return dlret;
}
extern "C" void* vmdlsym(void* handle, const char* symbol){
   if(handle){
      DLModule* dl = (DLModule*)handle;
      return dl->getPointerToFunction(symbol);
   }
   return NULL;
}
extern "C" void vmdlclose(void* p){
   if(p){
      DLModule* dl = (DLModule*) p;
      delete dl;
   }
}

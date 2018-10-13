LIBPATH=../x86/lib
g++ -fPIC -shared vmdlopen.cpp -o libvmdlopen.so \
-I ../llvm-3.4/ \
-I ../llvm-3.4/include \
-I ../llvm-3.4/lib  \
-D__STDC_CONSTANT_MACROS -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DLLVM_NATIVE_TARGETMC="LLVMInitializeX86TargetMC"  \
$LIBPATH/libLLVMMCJIT.a \
$LIBPATH/libLLVMRuntimeDyld.a \
$LIBPATH/libLLVMIRReader.a \
$LIBPATH/libLLVMExecutionEngine.a \
$LIBPATH/libLLVMBitReader.a \
$LIBPATH/libLLVMAsmParser.a \
$LIBPATH/libLLVMCore.a \
$LIBPATH/libLTO.a \
$LIBPATH/libLLVMX86Info.a \
$LIBPATH/libLLVMX86Desc.a \
$LIBPATH/libLLVMObject.a \
$LIBPATH/libLLVMX86AsmPrinter.a \
$LIBPATH/libLLVMX86Utils.a \
$LIBPATH/libLLVMX86CodeGen.a \
$LIBPATH/libLLVMAsmPrinter.a \
$LIBPATH/libLLVMMCParser.a \
$LIBPATH/libLLVMSelectionDAG.a \
$LIBPATH/libLLVMCodeGen.a \
$LIBPATH/libLLVMScalarOpts.a \
$LIBPATH/libLLVMTarget.a \
$LIBPATH/libLLVMMC.a \
$LIBPATH/libLLVMTransformUtils.a \
$LIBPATH/libLLVMAnalysis.a \
$LIBPATH/libLLVMSupport.a \
$LIBPATH/libLLVMCore.a \
-lpthread -ldl -ltinfo


#include "../tensor.h"

#include <iostream>
#include <vector>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>

namespace codegen {

class executor {
public:
    executor() {
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        context_ = std::make_unique<llvm::LLVMContext>();
        owner_ = new llvm::Module("fsml", *context_);
    }

    tensor execute(tensor root);
private:
    // std::unique_ptr<llvm::Module> owner_;
    std::unique_ptr<llvm::LLVMContext> context_;
    // llvm::LLVMContext context_;
    llvm::Module* owner_;
};

namespace binaryops {

class Add {
public:
    // Add(llvm::Module *M, llvm::LLVMContext &Context):
    //     M_(M), Context_(Context) {}
    Add(){}
    llvm::Function* generate(llvm::Module *M, llvm::LLVMContext &Context);
    llvm::Function* generate(llvm::Module *M, llvm::IRBuilder<> &builder);
private:
    // llvm::Module* M_;
    // llvm::LLVMContext &Context_;
}; // Add
} // namespace binaryops
} // namespace codegen
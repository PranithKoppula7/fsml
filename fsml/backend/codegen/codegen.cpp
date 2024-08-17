#include <iostream>
#include <vector>

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/ExecutionEngine/ExecutionEngine.h"


static llvm::Function *createSumFunction(llvm::Module *M, llvm::LLVMContext &Context) {
    // create function template
    // returns an int, with args/ parameters of two ints
    llvm::FunctionType *sumFuncType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(Context),
        {llvm::Type::getInt32Ty(Context),
        llvm::Type::getInt32Ty(Context)},
        false
    );

    llvm::Function *sumFunc = llvm::Function::Create(
        sumFuncType,
        llvm::Function::ExternalLinkage,
        "custom_sum",
        M
    );

    // basic block for function
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(Context, "entry", sumFunc);

    // args
    llvm::Function::arg_iterator args = sumFunc->arg_begin();
    llvm::Value *arg1 = args++;
    arg1->setName("x");
    llvm::Value *arg2 = args++;
    arg2->setName("y");

    // add operation
    llvm::Value *tmp = llvm::BinaryOperator::CreateAdd(
        arg1,
        arg2,
        "tmp",
        bb
    );

    // return statement
    llvm::ReturnInst::Create(Context, tmp, bb);

    return sumFunc;
}

int main(int argc, char* argv[]) {
    std::cout << "Hello World!" << std::endl;

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::LLVMContext context;

    std::unique_ptr<llvm::Module> owner(new llvm::Module("fsml", context));
    llvm::Module *M = owner.get();

    llvm::Function* sumFunc = createSumFunction(M, context);

    M->print(llvm::errs(), nullptr);

    llvm::ExecutionEngine *ee = 
        llvm::EngineBuilder(std::unique_ptr<llvm::Module>(M)).create();
    ee->finalizeObject();

    int (*add)(int, int) = (int (*)(int, int))ee->getFunctionAddress("custom_sum");
    printf("Result: %d\n", add(10, 10));

    return 0;
}
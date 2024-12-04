#include <iostream>
#include <vector>

#include "codegen.h"
#include "../operation.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/Function.h>

namespace codegen {
    tensor executor::execute(tensor root) {
        std::string op = root.ctx_->op_;
        if (op == "+") {
            llvm::FunctionType *sumFuncType = llvm::FunctionType::get(
                llvm::Type::getFloatTy(*context_),
                {llvm::Type::getFloatTy(*context_),
                llvm::Type::getFloatTy(*context_)},
                false
            );

            llvm::Function *sumFunc = llvm::Function::Create(
                sumFuncType,
                llvm::Function::ExternalLinkage,
                "custom_sum",
                owner_
            );

            // basic block for function

            // args
            llvm::Function::arg_iterator args = sumFunc->arg_begin();
            llvm::Value *arg1 = args++;
            llvm::Value *arg2 = args++;

            // add operation
            llvm::Value *tmp = llvm::BinaryOperator::CreateAdd(
                arg1,
                arg2,
                "tmp"
            );

            // return statement
            llvm::ReturnInst::Create(*context_, tmp);
            owner_->print(llvm::errs(), nullptr);

            // execution
            llvm::ExecutionEngine *ee = 
                llvm::EngineBuilder(std::unique_ptr<llvm::Module>(owner_)).create();
            ee->finalizeObject();

            // function call and answer
            float (*add_)(float, float) = (float (*)(float, float))ee->getFunctionAddress("custom_sum");
            // std::vector<float> ans;
            // for (int i = 0; i < root.size(); i++) {
            //     float a = root.parents_.at(0)->data_vec.at(i);
            //     float b = root.parents_.at(1)->data_vec.at(i);
            //     float res = add_(a, b);
            //     ans.push_back(res);
            //     // just first iteration
            //     break;
            // }
            // float add
            float res = add_(
                root.parents_.at(0)->data_vec.at(0),
                root.parents_.at(1)->data_vec.at(0)
            );
            printf("Result: %f\n", res);
        }
        return tensor(std::vector<float>{2.0}, std::vector<int>{1});
    }

    namespace binaryops {
        llvm::Function* Add::generate(llvm::Module *M, llvm::LLVMContext &Context) {
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
            // arg1->setName("x");
            llvm::Value *arg2 = args++;
            // arg2->setName("y");

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

        llvm::Function* Add::generate(llvm::Module *M, llvm::IRBuilder<> &builder) {
            llvm::FunctionType *sumFuncType = llvm::FunctionType::get(
                builder.getInt32Ty(),
                {builder.getInt32Ty(),
                builder.getInt32Ty()},
                false
            );

            llvm::Function *sumFunc = llvm::Function::Create(
                sumFuncType,
                llvm::Function::ExternalLinkage,
                "custom_sum",
                M
            );

            // basic block for function
            llvm::BasicBlock *bb = llvm::BasicBlock::Create(builder.getContext(), "entry", sumFunc);
            builder.SetInsertPoint(bb);

            // args
            llvm::Function::arg_iterator args = sumFunc->arg_begin();
            llvm::Value *arg1 = args++;
            llvm::Value *arg2 = args++;

            llvm::Value *tmp = builder.CreateAdd(arg1, arg2, "tmp");

            // return statement
            builder.CreateRet(tmp);

            return sumFunc;
        }
    }

}

// int main(int argc, char* argv[]) {
//     std::cout << "Hello World!" << std::endl;
// }

// static llvm::Function *createSumFunction(llvm::Module *M, llvm::LLVMContext &Context) {
//     // create function template
//     // returns an int, with args/ parameters of two ints
//     llvm::FunctionType *sumFuncType = llvm::FunctionType::get(
//         llvm::Type::getInt32Ty(Context),
//         {llvm::Type::getInt32Ty(Context),
//         llvm::Type::getInt32Ty(Context)},
//         false
//     );

//     llvm::Function *sumFunc = llvm::Function::Create(
//         sumFuncType,
//         llvm::Function::ExternalLinkage,
//         "custom_sum",
//         M
//     );

//     // basic block for function
//     llvm::BasicBlock *bb = llvm::BasicBlock::Create(Context, "entry", sumFunc);

//     // args
//     llvm::Function::arg_iterator args = sumFunc->arg_begin();
//     llvm::Value *arg1 = args++;
//     arg1->setName("x");
//     llvm::Value *arg2 = args++;
//     arg2->setName("y");

//     // add operation
//     llvm::Value *tmp = llvm::BinaryOperator::CreateAdd(
//         arg1,
//         arg2,
//         "tmp",
//         bb
//     );

//     // return statement
//     llvm::ReturnInst::Create(Context, tmp, bb);

//     return sumFunc;
// }

// int main(int argc, char* argv[]) {
//     std::cout << "Hello World!" << std::endl;

//     llvm::InitializeNativeTarget();
//     llvm::InitializeNativeTargetAsmPrinter();
//     llvm::LLVMContext context;

//     std::unique_ptr<llvm::Module> owner(new llvm::Module("fsml", context));
//     llvm::Module *M = owner.get();

//     llvm::Function* sumFunc = createSumFunction(M, context);

//     M->print(llvm::errs(), nullptr);

//     llvm::ExecutionEngine *ee = 
//         llvm::EngineBuilder(std::unique_ptr<llvm::Module>(M)).create();
//     ee->finalizeObject();

//     int (*add)(int, int) = (int (*)(int, int))ee->getFunctionAddress("custom_sum");
//     printf("Result: %d\n", add(10, 10));

//     return 0;
// }
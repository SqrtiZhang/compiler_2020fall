#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRBuilder.h"
#include "Module.h"
#include "Type.h"

#include <iostream>
#include <memory>

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module)

int main()
{
    auto module = new Module("Assign code");
    auto builder = new IRBuilder(nullptr, module);
    Type *Int32Type = Type::get_int32_type(module);
    //int callee(int a);
    auto calleeFun = Function::create(FunctionType::get(Int32Type, {Int32Type}),"callee", module);
    auto bb = BasicBlock::create(module, "entry", calleeFun);

    builder->set_insert_point(bb); 
    
    auto aAlloca = builder->create_alloca(Int32Type);
    //get a
    builder->create_store(*calleeFun->arg_begin(), aAlloca);
    auto aLoad = builder->create_load(aAlloca); 

    auto mul = builder->create_imul(CONST_INT(2), aLoad);
    //return 2 * a;
    builder->create_ret(mul);
    //int main()
    auto mainFun = Function::create(FunctionType::get(Int32Type, {}),"main", module);
    bb = BasicBlock::create(module, "entry", mainFun);
    builder->set_insert_point(bb);
    auto call = builder->create_call(calleeFun, {CONST_INT(110)}); 
    //return callee(110);
    builder->create_ret(call);

    std::cout << module->print();
    delete module;
    return 0;
}
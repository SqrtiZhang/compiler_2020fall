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
    auto module = new Module("If code");
    auto builder = new IRBuilder(nullptr, module);
    Type *Int32Type = Type::get_int32_type(module);
    Type *FloatType = Type::get_float_type(module);
    //int main()
    auto mainFun = Function::create(FunctionType::get(Int32Type, {}),"main", module);
    auto bb = BasicBlock::create(module, "entry", mainFun);
    builder->set_insert_point(bb);
    //float a = 5.555;
    auto aAlloca = builder->create_alloca(FloatType);
    builder->create_store(CONST_FP(5.555), aAlloca); 
    auto aLoad = builder->create_load(aAlloca);
    //cmp
    auto fcmp = builder->create_fcmp_gt(aLoad, CONST_FP(1));

    auto trueBB = BasicBlock::create(module, "trueBB", mainFun);
    auto retBB = BasicBlock::create(module, "retBB", mainFun);

    auto br = builder->create_cond_br(fcmp, trueBB, retBB);
    //if(a > 1)
    builder->set_insert_point(trueBB);
    //return 233;
    builder->create_ret(CONST_INT(233));
    //return 0;
    builder->set_insert_point(retBB);
    builder->create_ret(CONST_INT(0));

    std::cout << module->print();
    delete module;
    return 0;
}
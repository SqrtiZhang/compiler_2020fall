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
    auto module = new Module("While code");
    auto builder = new IRBuilder(nullptr, module);
    Type *Int32Type = Type::get_int32_type(module);
    //int main()
    auto mainFun = Function::create(FunctionType::get(Int32Type, {}),"main", module);
    auto bb = BasicBlock::create(module, "entry", mainFun);
    builder->set_insert_point(bb);
    //int a, i
    auto aAlloca = builder->create_alloca(Int32Type);
    auto iAlloca = builder->create_alloca(Int32Type);
    //a=10; i=0;
    builder->create_store(CONST_INT(10), aAlloca);
    builder->create_store(CONST_INT(0), iAlloca);

    auto condBB = BasicBlock::create(module, "condBB", mainFun);
    auto bodyBB = BasicBlock::create(module, "bodyBB", mainFun);
    auto endBB = BasicBlock::create(module, "endBB", mainFun);
    //while(i<10)
    auto br = builder->create_br(condBB);
    builder->set_insert_point(condBB);
    auto iLoad = builder->create_load(iAlloca);
    auto icmp = builder->create_icmp_lt(iLoad, CONST_INT(10));
    br = builder->create_cond_br(icmp, bodyBB, endBB);
    //loop
    builder->set_insert_point(bodyBB);
    iLoad = builder->create_load(iAlloca);
    //i++
    auto add = builder->create_iadd(iLoad, CONST_INT(1));
    builder->create_store(add, iAlloca);
    //a=a+i
    auto aLoad = builder->create_load(aAlloca);
    iLoad = builder->create_load(iAlloca);
    add = builder->create_iadd(iLoad, aLoad);
    builder->create_store(add, aAlloca);
    br = builder->create_br(condBB);
    //return a
    builder->set_insert_point(endBB);
    aLoad = builder->create_load(aAlloca);
    builder->create_ret(aLoad);

    std::cout << module->print();
    delete module;
    return 0;
}
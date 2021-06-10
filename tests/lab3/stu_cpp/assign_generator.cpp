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

    auto *arrayType = ArrayType::get(Int32Type, 10);
    //int main()
    auto mainFun = Function::create(FunctionType::get(Int32Type, {}),"main", module);
    auto bb = BasicBlock::create(module, "entry", mainFun);
    builder->set_insert_point(bb);
    //int a[10];
    auto a = builder->create_alloca(arrayType);
    auto a0GEP = builder->create_gep(a, {CONST_INT(0), CONST_INT(0)});
    //a[0] = 10;
    builder->create_store(CONST_INT(10), a0GEP);
    auto a0Val = builder->create_load(a0GEP);
    //cac a[0]*2
    auto mul = builder->create_imul(a0Val, CONST_INT(2));
    //a[1]=a[0]*2
    auto a1GEP = builder->create_gep(a, {CONST_INT(0), CONST_INT(1)});  
    builder->create_store(mul, a1GEP);

    auto a1Val = builder->create_load(a1GEP);

    auto retAlloca = builder->create_alloca(Int32Type);
    builder->create_store(a1Val, retAlloca);
    auto retLoad = builder->create_load(retAlloca);
    //return a[1]
    builder->create_ret(retLoad);
    
    std::cout << module->print();
    delete module;
    return 0;
}
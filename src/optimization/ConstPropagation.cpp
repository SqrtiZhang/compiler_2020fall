#include "ConstPropagation.hpp"
#include "logging.hpp"

// 给出了返回整形值的常数折叠实现，大家可以参考，在此基础上拓展
// 当然如果同学们有更好的方式，不强求使用下面这种方式
ConstantInt *ConstFolder::compute(
    Instruction::OpID op,
    ConstantInt *value1,
    ConstantInt *value2)
{

    int c_value1 = value1->get_value();
    int c_value2 = value2->get_value();
    switch (op)
    {
    case Instruction::add:
        return ConstantInt::get(c_value1 + c_value2, module_);

        break;
    case Instruction::sub:
        return ConstantInt::get(c_value1 - c_value2, module_);
        break;
    case Instruction::mul:
        return ConstantInt::get(c_value1 * c_value2, module_);
        break;
    case Instruction::sdiv:
        return ConstantInt::get((int)(c_value1 / c_value2), module_);
        break;
    default:
        return nullptr;
        break;
    }
}

ConstantInt *ConstFolder::compute(
    CmpInst::CmpOp op,
    ConstantInt *value1,
    ConstantInt *value2
)
{
    int c_value1 = value1->get_value();
    int c_value2 = value2->get_value();
    switch (op)
    {
    case CmpInst::EQ:
        return ConstantInt::get(c_value1 == c_value2, module_);

        break;
    case CmpInst::NE:
        return ConstantInt::get(c_value1 != c_value2, module_);
        break;
    case CmpInst::GT:
        return ConstantInt::get(c_value1 > c_value2, module_);
        break;
    case CmpInst::GE:
        return ConstantInt::get((int)(c_value1 >= c_value2), module_);
        break;
    case CmpInst::LT:
        return ConstantInt::get((int)(c_value1 <= c_value2), module_);;
        break;
    case CmpInst::LE:
        return ConstantInt::get((int)(c_value1 < c_value2), module_);;
        break;
    default:
        return nullptr;
        break;
    }
}

ConstantFP *ConstFolder::compute(
    Instruction::OpID op,
    ConstantFP *value1,
    ConstantFP *value2)
{
    float lhs = value1->get_value();
    float rhs = value2->get_value();
    switch (op)
    {
    case Instruction::fadd:
        return ConstantFP::get(lhs + rhs, module_);
        break;
    case Instruction::fsub:
        return ConstantFP::get(lhs - rhs, module_);
        break;
    case Instruction::fmul:
        return ConstantFP::get(lhs * rhs, module_);
        break;
    case Instruction::fdiv:
        return ConstantFP::get((float)(lhs / rhs), module_);
        break;
    default:
        return nullptr;
        break;
    }
}

ConstantInt *ConstFolder::compute(
    CmpInst::CmpOp op,
    ConstantFP *value1,
    ConstantFP *value2)
{
    float c_value1 = value1->get_value();
    float c_value2 = value2->get_value();
    switch (op)
    {
    case CmpInst::EQ:
        return ConstantInt::get(c_value1 == c_value2, module_);

        break;
    case CmpInst::NE:
        return ConstantInt::get(c_value1 != c_value2, module_);
        break;
    case CmpInst::GT:
        return ConstantInt::get(c_value1 > c_value2, module_);
        break;
    case CmpInst::GE:
        return ConstantInt::get((int)(c_value1 >= c_value2), module_);
        break;
    case CmpInst::LT:
        return ConstantInt::get((int)(c_value1 <= c_value2), module_);;
        break;
    case CmpInst::LE:
        return ConstantInt::get((int)(c_value1 < c_value2), module_);;
        break;
    default:
        return nullptr;
        break;
    }
}
// 用来判断value是否为ConstantFP，如果不是则会返回nullptr
ConstantFP *cast_constantfp(Value *value)
{
    auto constant_fp_ptr = dynamic_cast<ConstantFP *>(value);
    if (constant_fp_ptr)
    {
        return constant_fp_ptr;
    }
    else
    {
        return nullptr;
    }
}
ConstantInt *cast_constantint(Value *value)
{
    auto constant_int_ptr = dynamic_cast<ConstantInt *>(value);
    if (constant_int_ptr)
    {
        return constant_int_ptr;
    }
    else
    {
        return nullptr;
    }
}


void ConstPropagation::run()
{
    // 从这里开始吧！

    auto func_list = m_->get_functions();
    for(auto func : func_list){


    }
}
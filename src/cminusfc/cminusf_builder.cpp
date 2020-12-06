#include "cminusf_builder.hpp"

// use these macros to get constant value
#define CONST_FP(num) \
    ConstantFP::get((float)num, module.get())
#define CONST_ZERO(type) \
    ConstantZero::get(var_type, module.get())


// You can define global variables here
// to store state
Value* Expression;

int current_number;
float current_float;
CminusType current_type;

/*
 * use CMinusfBuilder::Scope to construct scopes
 * scope.enter: enter a new scope
 * scope.exit: exit current scope
 * scope.push: add a new binding to current scope
 * scope.find: find and return the value bound to the name
 */

void CminusfBuilder::visit(ASTProgram &node) {
    std::cout<<"test9"<<std::endl;
    for(auto decl: node.declarations){
        decl->accept(*this);
    }
    scope.exit();
}

void CminusfBuilder::visit(ASTNum &node) { 
    current_type = node.type;
    if(current_type == TYPE_INT)
        current_number = node.i_val;
    else if(current_type == TYPE_FLOAT)
        current_number = node.i_val;
}

void CminusfBuilder::visit(ASTVarDeclaration &node) { 
    Type* node_type;
    Type* node_value_type;

    if(node.type == TYPE_INT)
        node_value_type = Type::get_int32_type(module.get());
    else if(node.type == TYPE_FLOAT)
        node_value_type = Type::get_float_type(module.get()); 

    if(node.num != nullptr)
    {
        // when the var is a array
        node.num->accept(*this);
        node_type = ArrayType::get(node_value_type, node.num->i_val);
    }
    else
    {
        // the var is not a array 
        node_type = node_value_type;
    }

    if(scope.in_global())
    {
        //TODO: verify global
        auto *global_var = new GlobalVariable(node.id, module.get(), node_type, false);
        scope.push(node.id, global_var);
    }
    else
    {
        auto node_alloca = builder->create_alloca(node_type);
        scope.push(node.id, node_alloca);
    }
    

}

void CminusfBuilder::visit(ASTFunDeclaration &node) { 
    // 一个stupid的版本，现在只是生成了main函数需要的部分，其他的函数声明处理还没管。
    std::cout<<"test3"<<std::endl;
    Type *Int32Type = Type::get_int32_type(module.get());
    auto mainFun = Function::create(FunctionType::get(Int32Type, {}),
                                  "main", module.get());
    auto bb = BasicBlock::create(module.get(), "entry", mainFun);
    builder->set_insert_point(bb);
    node.compound_stmt->accept(*this);
}

void CminusfBuilder::visit(ASTParam &node) { }

void CminusfBuilder::visit(ASTCompoundStmt &node) { 
    // 访问局部变量
    for(auto vardec: node.local_declarations){
        vardec->accept(*this);
    }
}

void CminusfBuilder::visit(ASTExpressionStmt &node) { }

void CminusfBuilder::visit(ASTSelectionStmt &node) { }

void CminusfBuilder::visit(ASTIterationStmt &node) { }

void CminusfBuilder::visit(ASTReturnStmt &node) { }

void CminusfBuilder::visit(ASTVar &node) { }

void CminusfBuilder::visit(ASTAssignExpression &node) { }

void CminusfBuilder::visit(ASTSimpleExpression &node) { }

void CminusfBuilder::visit(ASTAdditiveExpression &node) { }

void CminusfBuilder::visit(ASTTerm &node) { }

void CminusfBuilder::visit(ASTCall &node) { }

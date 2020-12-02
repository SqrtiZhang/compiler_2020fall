#include "cminusf_builder.hpp"

// use these macros to get constant value
#define CONST_FP(num) \
    ConstantFP::get((float)num, module.get())
#define CONST_ZERO(type) \
    ConstantZero::get(var_type, module.get())


// You can define global variables here
// to store state
Value* Expression;

/*
 * use CMinusfBuilder::Scope to construct scopes
 * scope.enter: enter a new scope
 * scope.exit: exit current scope
 * scope.push: add a new binding to current scope
 * scope.find: find and return the value bound to the name
 */

void CminusfBuilder::visit(ASTProgram &node) {
    std::cout<<"test1"<<std::endl;
    for(auto decl: node.declarations){
        decl->accept(*this);
    }
}

void CminusfBuilder::visit(ASTNum &node) { 
    
}

void CminusfBuilder::visit(ASTVarDeclaration &node) { 
    std::cout<<"test2"<<std::endl;
    
    if(node.num != nullptr){
        // when the var is a array
        Type *Int32Type = Type::get_int32_type(module.get());
        std::cout<<node.num->i_val<<std::endl;
        auto *arraytype = ArrayType::get(Int32Type, node.num->i_val);
        auto aalloc = builder->create_alloca(arraytype);

    }else{
        // the var is not a array 
        Type *Int32Type = Type::get_int32_type(module.get());
        auto valloc = builder->create_alloca(Int32Type);
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

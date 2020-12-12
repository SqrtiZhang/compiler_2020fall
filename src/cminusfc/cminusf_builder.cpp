#include "cminusf_builder.hpp"

// use these macros to get constant value
#define CONST_FP(num) \
    ConstantFP::get((float)num, module.get())
#define CONST_ZERO(type) \
    ConstantZero::get(var_type, module.get())


// You can define global variables here
// to store state

// to be used in while, if and return statements
// Value* Expression;

int current_number;
float current_float;
CminusType current_type;

Function* current_func;
BasicBlock* current_bb; 

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
        current_number = node.f_val;
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
        auto *global_var = GlobalVariable::create(node.id, module.get(), node_type, false, nullptr);
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


void CminusfBuilder::visit(ASTExpressionStmt &node) {
    
 }

void CminusfBuilder::visit(ASTSelectionStmt &node) { }




void CminusfBuilder::visit(ASTIterationStmt &node) {
    // the iteration-stmt

    // create three bb: compare bb, while_body bb, end bb.
    auto cmp_bb = BasicBlock::create(module.get(), "cmp_bb", current_func);
    auto while_body_bb = BasicBlock::create(module.get(), "while_body_bb", current_func);
    auto end_bb = BasicBlock::create(module.get(), "end_bb", current_func);

    // br to cmp_bb
    builder->create_br(cmp_bb);

    // cmp_bb
    builder->set_insert_point(cmp_bb);
    current_bb = cmp_bb;
    // enter the expression node
    node.expression->accept(*this);
    //TODO remember to push the cmp value in the expression node
    auto cmp = scope.find("cmp"); // find the while_expression value
    builder->create_cond_br(cmp, while_body_bb, end_bb);

    // while_body
    builder->set_insert_point(while_body_bb);
    current_bb = while_body_bb;
    // enter the statement node
    node.statement->accept(*this);
    // jump to the cmp bb, it's a loop
    builder->create_br(cmp_bb);
    //TODO consider the return-stmt inside the while bb
    // end_bb
    builder->set_insert_point(end_bb);
    current_bb = end_bb;

 }

void CminusfBuilder::visit(ASTReturnStmt &node) {
    if(node.expression){// return-stmt->return expression;
        node.expression->accept(*this);
        //TODO consider to bind the ret_value when visit expression-stmt node
        auto ret_var = scope.find("ret_value");
        builder->create_ret(ret_var);
    }else{ // return-stmt->return;
        builder->create_ret(nullptr);
    }
 }

void CminusfBuilder::visit(ASTVar &node) { 
    if(node.expression){
        // var->ID [expression]

    }else{
        // var->ID
    }
}

void CminusfBuilder::visit(ASTAssignExpression &node) {
    // expression->var=expression | simple-expression
    
 }

void CminusfBuilder::visit(ASTSimpleExpression &node) {
    // simple-expression→additive-expression relop additive-expression 
    // ∣ additive-expression

 }

void CminusfBuilder::visit(ASTAdditiveExpression &node) {
    // additive-expression→additive-expression addop term ∣ term
 }

void CminusfBuilder::visit(ASTTerm &node) {
    // term→term mulop factor ∣ factor
 }

void CminusfBuilder::visit(ASTCall &node) {
    // call->ID ( args )
 }

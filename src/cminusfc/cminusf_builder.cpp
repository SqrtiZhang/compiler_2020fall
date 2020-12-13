#include "cminusf_builder.hpp"
#include "logging.hpp"
// use these macros to get constant value
#define CONST_FP(num) \
    ConstantFP::get((float)num, module.get())
#define CONST_ZERO(type) \
    ConstantZero::get(var_type, module.get())


// You can define global variables here
// to store state

// to be used in while, if and return statements
Value* Expression;

int current_number;
bool want_change_type = false;
float current_float;
CminusType current_type;

Function* current_func;
BasicBlock* current_bb; 

Value* current_var;

Value* return_alloca;

/*
 * use CMinusfBuilder::Scope to construct scopes
 * scope.enter: enter a new scope
 * scope.exit: exit current scope
 * scope.push: add a new binding to current scope
 * scope.find: find and return the value bound to the name
 */

void CminusfBuilder::visit(ASTProgram &node) {
    LOG(INFO) << "Program";

    for(auto decl: node.declarations){
        decl->accept(*this);
    }
    scope.exit();
}

void CminusfBuilder::visit(ASTNum &node) { 
    LOG(INFO) << "NUM";
    current_type = node.type;
    if(current_type == TYPE_INT){
        current_number = node.i_val;
        // type change 
        if(want_change_type && current_var->get_type()->get_pointer_element_type()->is_float_type()){
            Expression = ConstantFP::get((float)current_number, module.get());
        }else{
            Expression = ConstantInt::get(current_number, module.get());
        }
        
    }
    else if(current_type == TYPE_FLOAT){
        if(want_change_type && current_var->get_type()->get_pointer_element_type()->is_integer_type()){
            Expression = ConstantInt::get((int)(node.f_val), module.get());
        }else{
            Expression = ConstantFP::get(node.f_val, module.get());
        }
    }
        
}

void CminusfBuilder::visit(ASTVarDeclaration &node) { 
    LOG(INFO) << "VarDeclaration";
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
    LOG(INFO) << "FunDeclaration";
    std::vector<Type*> Params;
    for(auto param: node.params){
        if(param->isarray){
            Params.push_back(PointerType::get_int32_ptr_type(module.get()));
        }else{
            Params.push_back(Type::get_int32_type(module.get()));
        }
    }
    auto Int32Type = Type::get_int32_type(module.get());
    auto FloatType = Type::get_float_type(module.get());
    auto voidType = Type::get_void_type(module.get());
    FunctionType* functype;
    // choose the function type
    if(node.type == TYPE_INT){
        functype = FunctionType::get(Int32Type,Params);
    }else if(node.type == TYPE_FLOAT){
        functype = FunctionType::get(FloatType,Params);
    }else{
        functype = FunctionType::get(voidType,Params);
    }
    // get the function
    auto Func = Function::create(functype, node.id, module.get());
    // push the func's name
    scope.push(node.id, Func);

    current_func = Func;
    auto bb = BasicBlock::create(module.get(), "entry", Func);
    builder->set_insert_point(bb);

    current_bb = bb;

    // enter the scope of this function
    scope.enter();
    // allocate for params
    // get the 迭代器 也就是形参
    auto arg = Func->arg_begin();
    for(auto param: node.params){
        if(arg == Func->arg_end()){
            // error
            std::cout<<"error"<<std::endl;
        }

        if(param->isarray){
            // 传入的是指针 根据参数的类型来判断。
            if(param->type == TYPE_INT){
                auto param_var = builder->create_alloca(PointerType::get(Int32Type));
                scope.push(param->id, param_var);
                builder->create_store(*arg, param_var);
            }
            if(param->type == TYPE_FLOAT){
                auto param_var = builder->create_alloca(PointerType::get(FloatType));
                scope.push(param->id, param_var);
                builder->create_store(*arg, param_var);
            }
        }else{
            if(param->type == TYPE_INT){
                auto param_var = builder->create_alloca(Int32Type);
                scope.push(param->id, param_var);
                builder->create_store(*arg, param_var);
            }
            if(param->type == TYPE_FLOAT){
                auto param_var = builder->create_alloca(FloatType);
                scope.push(param->id, param_var);
                builder->create_store(*arg, param_var);
            }
        }

        arg++;
    }

    // allocate return_alloca it's a global value
    if(node.type == TYPE_INT){
        return_alloca = builder->create_alloca(Int32Type);
    }else if(node.type == TYPE_FLOAT){
        return_alloca = builder->create_alloca(FloatType);
    }
    // visit the compound_stmt and store the ret value in the return_alloca
    node.compound_stmt->accept(*this);

    if(node.type == TYPE_VOID){
        builder->create_void_ret();
    }else{
        auto ret_load = builder->create_load(return_alloca);
        builder->create_ret(ret_load);
    }
    // exit the scope of this function
    scope.exit();
}

void CminusfBuilder::visit(ASTParam &node) {
    //TODO put the code from funcdeclaration to here
 }

void CminusfBuilder::visit(ASTCompoundStmt &node) { 
    LOG(INFO) << "Compoundstmt";
    // {}内的变量要有作用域
    scope.enter();
    
    for(auto decl: node.local_declarations){
        decl->accept(*this);
    }

    for(auto stmt: node.statement_list){
        stmt->accept(*this);
        if(builder->get_insert_block()->get_terminator() != nullptr){
            break;
        }
    }
    scope.exit();

}


void CminusfBuilder::visit(ASTExpressionStmt &node) {
    LOG(INFO) << "ExpressionStmt";
    if (node.expression != nullptr)
        node.expression->accept(*this);
    
 }

void CminusfBuilder::visit(ASTSelectionStmt &node) { 
    LOG(INFO) << "SelectionStmt";
    node.expression->accept(*this); // set global value Expression to transfer the value
    auto trueBB = BasicBlock::create(module.get(), "trueBB", current_func);
    auto falseBB = BasicBlock::create(module.get(), "falseBB", current_func);
    auto retBB = BasicBlock::create(module.get(), "retBB", current_func);
    if(node.else_statement != nullptr)
        auto br = builder->create_cond_br(Expression, trueBB, falseBB);
    else{
        auto br = builder->create_cond_br(Expression, trueBB, retBB);
    }
    builder->set_insert_point(trueBB);
    node.if_statement->accept(*this);
    if(builder->get_insert_block()->get_terminator() == nullptr){
        builder->create_br(retBB);
    }    

    LOG(DEBUG) << "before enter else";
    if (node.else_statement != nullptr){
        builder->set_insert_point(falseBB);

         LOG(DEBUG) << "falseBB";
        node.else_statement->accept(*this);
        if(builder->get_insert_block()->get_terminator() == nullptr){
            builder->create_br(retBB);
        }
    }else{
        builder->set_insert_point(falseBB);
        builder->create_br(retBB);
    }
    LOG(DEBUG) << "after enter else";


    builder->set_insert_point(retBB);

}




void CminusfBuilder::visit(ASTIterationStmt &node) {
    // the iteration-stmt
    LOG(INFO) << "Iterationstmt";
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
    // set the value of expression
    auto cmp = Expression;
    builder->create_cond_br(cmp, while_body_bb, end_bb);

    // while_body
    builder->set_insert_point(while_body_bb);
    current_bb = while_body_bb;
    // enter the statement node
    node.statement->accept(*this);
    // jump to the cmp bb, it's a loop
    if(builder->get_insert_block()->get_terminator() == nullptr){
        builder->create_br(cmp_bb);
    }
    // end_bb
    builder->set_insert_point(end_bb);
    current_bb = end_bb;

 }

void CminusfBuilder::visit(ASTReturnStmt &node) {
    LOG(INFO) << "returnstmt";
    if(node.expression){// return-stmt->return expression;
        node.expression->accept(*this);
        // global value, seted in accept()
        auto ret_var = Expression;
        if(Expression->get_type()->is_pointer_type()){
            ret_var = builder->create_load(Expression);
        }
        builder->create_ret(ret_var);
    }else{ // return-stmt->return;
            ;
    }
 }

void CminusfBuilder::visit(ASTVar &node) { 
    LOG(INFO) << "Var";
    auto x = scope.find(node.id); // find the alloca
    // var->ID | ID [expression]
    if (node.expression != nullptr) {
        std::cout << "[]" << std::endl;
        //
        node.expression->accept(*this);
        auto index = builder->create_load(Expression);
        auto valueGEP = builder->create_gep(x, {ConstantInt::get(0, module.get()), (ConstantInt*)index});
        current_var = valueGEP;
        Expression = valueGEP;
        
    }else{
        // not a array
        current_var = x;
        Expression = x;
    }
}

void CminusfBuilder::visit(ASTAssignExpression &node) {
    LOG(INFO) << "assignexpression";
    // expression->var=expression | simple-expression
    // assign or call
    Value* left_alloca;
    Value* right_value;
    Value* temp;
    node.var->accept(*this); // know the alloca from current_var
    
    left_alloca = current_var; // find the address of the value
    want_change_type = true;
    node.expression->accept(*this);
    if(Expression->get_type()->is_pointer_type()){
        right_value = builder->create_load(Expression);;
    }else{
        // Expression is a constant
        right_value = Expression;
    }
     // get the value of the expression
    if(right_value->get_type()->is_float_type() && left_alloca->get_type()->is_integer_type()){

        builder->create_store(right_value, left_alloca);
    }
    builder->create_store(right_value, left_alloca); // store the value in the addression
 }

void CminusfBuilder::visit(ASTSimpleExpression &node) {
    LOG(INFO) << "simpleExpression";
    // simple-expression→additive-expression relop additive-expression 
    // ∣ additive-expression
    node.additive_expression_l->accept(*this);
    Value* left = Expression;
    

    if (node.additive_expression_r == nullptr) {
        LOG(DEBUG) << "simpleExpression->additive-expression";
    } else {
        left = builder->create_load(Expression);
        node.additive_expression_r->accept(*this);
        Value* right = Expression;
        if(right->get_type()->is_pointer_type()){
            right = builder->create_load(right);
        }
        
        if (node.op == OP_LT) {
            Expression = builder->create_icmp_lt(left, right);
        } else if (node.op == OP_LE) {
            Expression = builder->create_icmp_le(left, right);
        } else if (node.op == OP_GE) {
            Expression = builder->create_icmp_ge(left, right);
        } else if (node.op == OP_GT) {
            Expression = builder->create_icmp_gt(left, right);
        } else if (node.op == OP_EQ) {
            Expression = builder->create_icmp_eq(left, right);
        } else if (node.op == OP_NEQ) {
            Expression = builder->create_icmp_ne(left, right);
        } else {
            std::abort();
        }
        std::cout << std::endl;
    }
       
 }

void CminusfBuilder::visit(ASTAdditiveExpression &node) {
    LOG(INFO) << "additiveexpression";
    // additive-expression→additive-expression addop term ∣ term
    if (node.additive_expression == nullptr) {
        node.term->accept(*this); 
        
    } else {
        node.additive_expression->accept(*this);
        Value* left = Expression;
        if(left->get_type()->is_pointer_type()){
            left = builder->create_load(left);
        }
        node.term->accept(*this); 
        Value* right = Expression;
        if(right->get_type()->is_pointer_type()){
            right = builder->create_load(right);
        }

        if (node.op == OP_PLUS) {
            Expression = builder->create_iadd(left, right);
        } else if (node.op == OP_MINUS) {
            Expression = builder->create_isub(left, right);
        } else {
            std::abort();
        }
    }
        
    
 }

void CminusfBuilder::visit(ASTTerm &node) {
    LOG(INFO) << "term";
    // term→term mulop factor ∣ factor
    if (node.term == nullptr) {
        node.factor->accept(*this);
    } else {
        node.term->accept(*this);
        Value* left = Expression;
        if(left->get_type()->is_pointer_type()){
            left = builder->create_load(left);
        }
        node.factor->accept(*this);
        Value* right = Expression;
        if(right->get_type()->is_pointer_type()){
            right = builder->create_load(right);
        }
        if (node.op == OP_MUL) {
            Expression = builder->create_imul(left, right);
        } else if (node.op == OP_DIV) {
            Expression = builder->create_isdiv(left, right);
        } else {
            std::abort();
        }
    }

 }

void CminusfBuilder::visit(ASTCall &node) {
    LOG(INFO) << "call";
    // call->ID ( args )
    auto func = scope.find(node.id);
    if(func == nullptr){
        ;
    }else{
        std::vector<Value*> args;
        for (auto arg: node.args) {
            arg->accept(*this);
            if(Expression->get_type()->is_pointer_type())
                Expression = builder->create_load(Expression);
            args.push_back(Expression);
        }
        Expression = builder->create_call(func, args);
    }
    
 }

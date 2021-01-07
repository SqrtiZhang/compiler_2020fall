#include "ActiveVars.hpp"

void ActiveVars::run()
{std::cout<<"hello"<<std::endl;
    std::ofstream output_active_vars;
    output_active_vars.open("active_vars.json", std::ios::out);
    output_active_vars << "[";
    for (auto &func : this->m_->get_functions()) {
        if (func->get_basic_blocks().empty()) {
            continue;
        }
        else
        {
            func_ = func;  
            
            func_->set_instr_name();
            live_in.clear();
            live_out.clear();
            
            // 在此分析 func_ 的每个bb块的活跃变量，并存储在 live_in live_out 结构内
            for(auto bb : func->get_basic_blocks())
            {
                std::set<std::pair<Value*, Value*>> use;
                std::set<Value*> def;

                /*if(bb == func->get_entry_block())
                {
                    for(auto arg: func->get_args())
                    {
                        use.insert(std::make_pair<Value*, Value*>(arg, nullptr));
                    }
                }*/

                for(auto instruction: bb->get_instructions())
                {
                    def.insert(instruction);
                    if(instruction->is_add() || instruction->is_sub() || instruction->is_mul() || instruction->is_div() || 
                    instruction-> is_fadd() || instruction->is_fsub() || instruction->is_fmul() || instruction->is_fdiv() ||
                    instruction -> is_cmp() || instruction -> is_fcmp())
                    {
                        if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0), nullptr));
                        if(instruction->get_operand(1)->get_type()->is_pointer_type() && def.find(instruction->get_operand(1)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(1), nullptr));
                    }
                    if(instruction -> is_load())
                    {
                        if(def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0), nullptr));
                    }
                    if(instruction -> is_store())
                    {
                        if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0), nullptr));
                        if(def.find(instruction->get_operand(1)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(1), nullptr));
                    }
                    if(instruction -> is_phi())
                    {
                        if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(1)));
                        if(instruction->get_operand(2)->get_type()->is_pointer_type() && def.find(instruction->get_operand(2)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(2),instruction->get_operand(3)));
                    }
                    if(instruction -> is_call())
                    {
                        for(int i = 0; i < instruction->get_num_operand(); i++)
                        {
                            if(instruction->get_operand(i)->get_type()->is_pointer_type() && def.find(instruction->get_operand(i)) == def.end())
                                use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(i), nullptr));
                        }
                    }
                    if(instruction -> is_gep())
                    {
                        if(instruction->get_num_operand() == 2)
                        {
                            if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                                use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(0)));
                            if(instruction->get_operand(1)->get_type()->is_pointer_type() && def.find(instruction->get_operand(1)) == def.end())
                                use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(1)));
                        }
                        else if(instruction->get_num_operand() == 3)
                        {
                            if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                                use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(0)));
                            if(instruction->get_operand(2)->get_type()->is_pointer_type() && def.find(instruction->get_operand(2)) == def.end())
                                use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(2)));
                        
                        }
                    }
                    if(instruction -> is_zext())
                    {
                        if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(0)));
                    }
                    if(instruction -> is_br() && instruction -> get_num_operand() == 3)
                    {
                        if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(0)));
                    }
                    if(instruction -> is_fp2si() || instruction -> is_si2fp())
                    {
                         if(instruction->get_operand(0)->get_type()->is_pointer_type() && def.find(instruction->get_operand(0)) == def.end())
                            use.insert(std::make_pair<Value*, Value*>(instruction->get_operand(0),instruction->get_operand(0)));
                    }
                }
            }

            output_active_vars << print();
            output_active_vars << ",";
        }
    }
    output_active_vars << "]";
    output_active_vars.close();
    return ;
}

std::string ActiveVars::print()
{
    std::string active_vars;
    active_vars +=  "{\n";
    active_vars +=  "\"function\": \"";
    active_vars +=  func_->get_name();
    active_vars +=  "\",\n";

    active_vars +=  "\"live_in\": {\n";
    for (auto &p : live_in) {
        if (p.second.size() == 0) {
            continue;
        } else {
            active_vars +=  "  \"";
            active_vars +=  p.first->get_name();
            active_vars +=  "\": [" ;
            for (auto &v : p.second) {
                active_vars +=  "\"%";
                active_vars +=  v->get_name();
                active_vars +=  "\",";
            }
            active_vars += "]" ;
            active_vars += ",\n";   
        }
    }
    active_vars += "\n";
    active_vars +=  "    },\n";
    
    active_vars +=  "\"live_out\": {\n";
    for (auto &p : live_out) {
        if (p.second.size() == 0) {
            continue;
        } else {
            active_vars +=  "  \"";
            active_vars +=  p.first->get_name();
            active_vars +=  "\": [" ;
            for (auto &v : p.second) {
                active_vars +=  "\"%";
                active_vars +=  v->get_name();
                active_vars +=  "\",";
            }
            active_vars += "]";
            active_vars += ",\n";
        }
    }
    active_vars += "\n";
    active_vars += "    }\n";

    active_vars += "}\n";
    active_vars += "\n";
    return active_vars;
}
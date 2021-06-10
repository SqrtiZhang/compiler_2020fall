# lab3 实验报告
 PB17111585 张永停

## 问题1: cpp与.ll的对应
请描述你的cpp代码片段和.ll的每个BasicBlock的对应关系。描述中请附上两者代码。

##### assign

assign只有一个bloock

```
label.entry:
  %0 = alloca [10 x i32]
  %1 = getelementptr [10 x i32], [10 x i32]* %0, i32 0, i32 0
  store i32 10, i32* %1
  %2 = load i32, i32* %1
  %3 = mul i32 %2, 2
  %4 = getelementptr [10 x i32], [10 x i32]* %0, i32 0, i32 1
  store i32 %3, i32* %4
  %5 = load i32, i32* %4
  %6 = alloca i32
  store i32 %5, i32* %6
  %7 = load i32, i32* %6
  ret i32 %7
```

```c++
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
```

##### fun

`main`函数有一个block`entry`， `callee`函数有一个`entry`

`main`中对应为

```
label.entry:
  %0 = call i32 @callee(i32 110)
  ret i32 %0
```

```c++
auto mainFun = Function::create(FunctionType::get(Int32Type, {}),"main", module);
    bb = BasicBlock::create(module, "entry", mainFun);
    builder->set_insert_point(bb);
    auto call = builder->create_call(calleeFun, {CONST_INT(110)}); 
    //return callee(110);
    builder->create_ret(call);
```

`callee`中对应为

```
label.entry:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = load i32, i32* %1
  %3 = mul i32 2, %2
  ret i32 %3
```

```c++
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
```

##### if

由于涉及分支，共三个block，分别为`entry`, `trueBB`, `retBB`

其中， `entry`的对应为

```
label.entry:
  %0 = alloca float
  store float 0x40163851e0000000, float* %0
  %1 = load float, float* %0
  %2 = fcmp ugt float %1,0x3ff0000000000000
  br i1 %2, label %label.trueBB, label %label.retBB
```

```c++
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
```

`trueBB`的对应为

```
label.trueBB:
  ret i32 233
```

```c++
builder->set_insert_point(trueBB);
    //return 233;
    builder->create_ret(CONST_INT(233));
```

`retBB`的对应为

```
label.retBB:
  ret i32 0
```

```c++
 builder->set_insert_point(retBB);
    builder->create_ret(CONST_INT(0));
```

##### while

共有四个block, 分别为`entry`， 循环条件`condBB`, 循环体`bodyBB`，以及循环结束后`endBB`

`entry`的对应为

```
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  store i32 10, i32* %0
  store i32 0, i32* %1
  br label %label.condBB
```

```c++
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
```

`condBB`的对应为

```
label.condBB:
  %2 = load i32, i32* %1
  %3 = icmp slt i32 %2, 10
  br i1 %3, label %label.bodyBB, label %label.endBB
```

```c++
builder->set_insert_point(condBB);
    auto iLoad = builder->create_load(iAlloca);
    auto icmp = builder->create_icmp_lt(iLoad, CONST_INT(10));
    br = builder->create_cond_br(icmp, bodyBB, endBB);
```

`bodyBB`的对应为

```
label.bodyBB:
  %4 = load i32, i32* %1
  %5 = add i32 %4, 1
  store i32 %5, i32* %1
  %6 = load i32, i32* %0
  %7 = load i32, i32* %1
  %8 = add i32 %7, %6
  store i32 %8, i32* %0
  br label %label.condBB
```

```c++
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
```

`endBB`的对应为

```
label.endBB:
  %9 = load i32, i32* %0
  ret i32 %9
```

```c++
builder->set_insert_point(endBB);
    aLoad = builder->create_load(aAlloca);
    builder->create_ret(aLoad);
```



## 问题2: Visitor Pattern
请指出visitor.cpp中，`treeVisitor.visit(exprRoot)`执行时，以下几个Node的遍历序列:numberA、numberB、exprC、exprD、exprE、numberF、exprRoot。  
序列请按如下格式指明：  
exprRoot->numberF->exprE->numberA->exprD

$$ exprRoot \rightarrow numberF \rightarrow exprE \rightarrow exprD \rightarrow numberB\rightarrow numberA \rightarrow exprC \rightarrow numberA \rightarrow numberB$$

## 问题3: getelementptr
请给出`IR.md`中提到的两种getelementptr用法的区别,并稍加解释:
  - `%2 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 %0` 
  - `%2 = getelementptr i32, i32* %1 i32 %0` 

##### 第一个方法

`[10 x i32]` 表示类型

`[10 x i32]* %1` 表示初始地址

第一个`i32 0`表示在`[10 x i32]* %1`的基础上偏移`0*[10 x i32]`，即`%1 + 0*4*10`

第二个`i32 0`计算的是指向`%1`第`0`个元素的地址，即`%1 + 0*4`

该方法返回的类型为`i32 *`

##### 第二个方法

`i32 %0`表示 `%1 + 0*4*10`

该方法返回的为指向结构体的指针



这两种方法在下例区别很明显

```c++
%MyVar = global { [10 x i32] }
%idx1 = getelementptr { [10 x i32] }, { [10 x i32] }* %MyVar, i64 0, i32 0, i64 1
%idx2 = getelementptr { [10 x i32] }, { [10 x i32] }* %MyVar, i64 1
```

`idx1` 计算结构体`%MyVar`中的第二个整数的地址, 即 `MyVar+4`.  `idx1` 的类型为 `i32*`. 

`idx2`  `%MyVar`的下一个结构体的地址.  `idx2` 的类型为 `{ [10 x i32] }*` ，值为`MyVar + 40` 

参考自https://llvm.org/docs/GetElementPtr.html

## 实验难点
总体实验不算难，助教文档很详细了几乎，文档上没的也都查到了^U^

## 实验反馈
吐槽助教在`gcd_array_generator.cpp`中吓人
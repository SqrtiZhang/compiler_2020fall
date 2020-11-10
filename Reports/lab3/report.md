# lab3 实验报告
PB18061351 闫超美

## 问题1: cpp与.ll的对应
请描述你的cpp代码片段和.ll的每个BasicBlock的对应关系。描述中请附上两者代码。

## 问题2: Visitor Pattern
请指出visitor.cpp中，`treeVisitor.visit(exprRoot)`执行时，以下几个Node的遍历序列:numberA、numberB、exprC、exprD、exprE、numberF、exprRoot。  
序列请按如下格式指明：  
exprRoot->numberF->exprE->numberA->exprD

## 问题3: getelementptr
请给出`IR.md`中提到的两种getelementptr用法的区别,并稍加解释:
  - `%2 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 %0` 
  - `%2 = getelementptr i32, i32* %1 i32 %0` 

## 实验难点
描述在实验中遇到的问题、分析和解决方案

### 1. .ll 文件编写

.ll文件是LLVM IR代码，也就是由C编译得到的中间代码，有一点类似汇编，是一种三地址码。

### assign.ll

```shell

```







### 2. LightIR + cpp 编写生成.ll的程序



### 3. Visitor Pattern





## 实验反馈
吐槽?建议?
# lab2 实验报告
PB17111585 张永停
## 实验要求
1. 了解 `bison` 基础知识和理解 Cminus-f 语法（重在了解如何将文法产生式转换为 `bison` 语句）
2. 阅读 `/src/common/SyntaxTree.c`，对应头文件 `/include/SyntaxTree.h`（重在理解分析树如何生成）
3. 了解 `bison` 与 `flex` 之间是如何协同工作，看懂pass_node函数并改写 Lab1 代码（提示：了解 `yylval` 是如何工作，在代码层面上如何将值传给`$1`、`$2`等）
4. 补全 `src/parser/syntax_analyzer.y` 文件和 `lexical_analyzer.l` 文件

Tips：在未编译的代码文件中是无法看到关于协同工作部分的代码，建议先编译 1.3 给出的计算器样例代码，再阅读 `/build/src/parser/` 中的 `syntax_analyzer.h` 与 `syntax_analyzer.c` 文件。

本次实验需要各位同学首先将自己的 lab1 的词法部分复制到 `/src/parser` 目录的 [lexical\_analyzer.l](./src/parser/lexical\_analyzer.l)并合理修改相应部分，然后根据 `cminus-f` 的语法补全 [syntax\_analyer.y](./src/parser/syntax_analyzer.y) 文件，完成语法分析器，要求最终能够输出解析树

## 实验难点

个人感觉lab2实验难点在于阅读说明，代码，搞清楚如何传递参数

## 实验设计

#### 将`lexical_analyer.l`中动作增加

使用`passnode()`函数建立结点

```c++
"else" {pos_start = pos_end; pos_end = pos_start + 4; pass_node("else"); return ELSE;}
```

对于`IDENTIFIER` `INTEGER` `FLOATPOINT`返回他们的值

```c++
{LETTER}+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); yylval.string = strdup(yytext); return IDENTIFIER;}
{DIGIT}+ {pos_start = pos_end; pos_end = pos_start + strlen(yytext); yylval.int_number = atoi(yytext); return INTEGER;} 
(({DIGIT}+[.])|({DIGIT}*[.]{DIGIT}+)) {pos_start = pos_end; pos_end = pos_start + strlen(yytext); yylval.string = strdup(yytext); return FLOATPOINT;}
(\[\]) {pos_start = pos_end; pos_end = pos_start + 2; pass_node("[]"); return ARRAY;}
```

#### `syntax_analyzer.y`

这部分几乎就是把实验文档抄一遍

```c++
local-declarations : local-declarations var-declaration{
    $$ = node("local-declarations", 2, $1, $2);
} | {
    $$ = node("local-declarations", 1, new_syntax_tree_node("epsilon"));
}
```

只是需要特别注意一下空串





## 实验结果验证





## 实验反馈

助教文档很详细，ℹ了ℹ了
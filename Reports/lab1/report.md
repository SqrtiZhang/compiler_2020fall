# lab1实验报告
PB17111585 张永停
## 实验要求

本次实验需要各位同学根据`cminux-f`的词法补全[lexical_analyer.l](./src/lexer/lexical_analyzer.l)文件，完成词法分析器，能够输出识别出的`token`，`type` ,`line(刚出现的行数)`，`pos_start(该行开始位置)`，`pos_end(结束的位置,不包含)`。如：

文本输入：

```c
 int a;
```

则识别结果应为：

```shell
int     280     1       2       5
a       285     1       6       7
;       270     1       7       8
```

**具体的需识别token参考[lexical_analyzer.h](./include/lexical_analyzer.h)**

**特别说明对于部分token，我们只需要进行过滤，即只需被识别，但是不应该被输出到分析结果中。因为这些token对程序运行不起到任何作用。**

## 实验难点

#### 多行注释

```c
"/*"([*]+[^/]|[^*])*[*]+"/"  {
    pos_start = pos_end; pos_end += yyleng;
    int pre_eol = -1;
    for (int i = 0; i < yyleng; ++i){
        if (yytext[i] == '\n'){
            lines++;
            pos_end -= (pos_start - 1) + (i - pre_eol);
            pos_start = 1;
            pre_eol = i;
        }
    }
    return COMMENT;
}
```

这里我认为注释必须同时具有`/*`与`*/`，若只有`\*`，则识别为`\`和`*`，之后的内容识别为`id`

## 实验设计
- 几乎所有模式，识别后需要做类似`pos_start = pos_end; pos_end = pos_start + 1; return SEMICOLON;`的操作。
- 比较特殊的是换行，`[\n] {lines++; pos_end = 1; pos_start = 1; return EOL;}`，需要重置`pos_start`与`pos_end`
- 多行注释部分设计见上
- 由于 flex 的匹配行为，`while`、`else` 等关键字的模式行为代码必须写在 `IDENTIFIER` 的行为前面，否则这些关键字将被匹配成标识符。

## 实验结果验证

所有的测试文件放置于`tests\lab1\testcase`中。

这里，自己主要测试了复杂空格，空行，只有一半注释的情况

- `7.cminus`首行为空
- `8.cminus`中，添加`int;`
- `10.cminus`中，`x = x/*comment*/*/******/4;`
- `11.cminus`测试了整个文件只有`/*`的情况没有`*/`
- `12.cminus`插入或删除了很多换行、空白等等，也添加了一个没有实际含义但是测试时需要的 `[]`。

## 实验反馈

本次实验总计耗时5h，其中学习flex约1h，写完基础代码约2h，思考特殊情况以及书写实验报告约2h。

个人认为本次实验说明十分详细，没有遇到特别大的困难。

希望下次实验可以说明一下输出格式，本次实验有约半个小时在研究如何输出TAT
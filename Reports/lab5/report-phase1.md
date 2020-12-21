# Lab5 实验报告-阶段一

小组成员

闫超美 PB18061351

张永停 PB17111585

## 实验要求

1. 阅读`Mem2Reg`与`LoopSearch`两个优化Pass的代码，能够描述优化的基本流程，并且回答思考题。
2. 通过阅读代码，掌握如何开发基于LightIR的优化Pass



## 优化的基本流程

### 1. LoopSearch

**1.1 run()函数**是LoopSearch.cpp的入口，首先调用get_functions()，获得function_list_，是一个函数链表，记录了这个编译单元的所有函数。然后循环遍历每个函数，如果函数的基本块个数不为0，则执行找循环的流程：

```txt
step 1： 建立CFG，这里调用build_cfg(func, nodes);传入当前函数和CFGNode指针集合，建立一个CFG图。然后调用dump_graph(nodes, func->get_name())打印此CFG图， 传入CFGNode指针集合nodes和当前函数的名字。
step 2： 调用strongly_connected_components()函数求强连通分量集合，存入sccs。
step 3: 在每个强连通分量中找到循环入口块。
step 4: 储存结果，即将分量中的block存入bb_set，插入loop_set（循环集合），插入func2loop，插入base2loop，插入loop2base。
step 5: 将每个node与循环入口对应起来，循环将bb和base_bb的键值对插入bb2base，即将这个强连通分量中的bb都与循环入口base对应的bb联系起来。
step 6: 将循环入口从CFG图中删除，从而将当前循环破坏掉，从而再次用strongly_connected_components()寻找时可以找到当前循环中可能存在的内层循环。
```



**1.2 build_cfg()函数**，维护了一个哈希表bb2cfg_node，将bb和cfg的node相对应。第一个for循环创建node并初始化node，将bb与node键值对插入bb2cfg_node，然后将node插入result这个集合里。 然后第二个for循环，先根据bb从bb2cfg_node哈希表中查出node，接下来是两个循环，分别遍历当前bb的后继bb和当前bb的前驱bb，并在bb2cfg_node中查询出bb对应节点，将其插入当前node的succs集合和prevs集合中。最终每个bb对应的node都有了各自的succ集合和prev集合。从而建立起了CFG图。



**1.3 dump_graph()函数**，这个函数是用来将图输出为png，与Pass逻辑无关，为了节省报告篇幅，不仔细解释函数逻辑。



**1.4 strongly_connected_components()函数**，传入一个CFG图，然后初始化index_count为0，将stack清空，然后循环遍历CFG图中的节点，如果节点的index还是-1，则调用tracerse()函数，传入当前节点和result集合。循环结束后result集合存储着强连通分量。如果result为空，则返回false，表示没有强连通分量，否则返回true。



**1.5 traverse()函数**，首先初始化传入的node的index和lowlink，设定此节点次序编号，将lowlink初值定为此编号。然后将此node给push到stack里，再将此node压入栈中。接下来是一个循环遍历当前node的succs集合，也就是枚举此节点发出的每一条边，如果没有访问过当前后继节点，则调用traverse()函数继续往下找，如果访问过此后继节点，则再看此节点是否在栈中，如果在栈中，则将当前节点的lowlink置为后继节点的index和当前节点的lowlink值的较小值。之后如果当前节点是强连通分量的根，就一直出栈，作为强连通分量的顶点存入set中，最后如果此强连通分量不止有一个节点，则将此强连通分量set插入到result集合中去，否则不保存此集合。



**1.6 find_loop_base()函数**， 在find_loop_base函数中，传入强连通分量和reserved集合，对强连通分量中的每个节点，都遍历它的前驱节点，如果有节点的前驱节点不在强连通分量中，则此节点为循环入口，置为base。然后如果通过此次循环找到了base，则返回此base；否则就说明这个强连通分量是一个内层循环，外层循环的base已经被删除，且插入到reserved中，所以要在reserved中继续找，对于reserved集合的每一个节点，都遍历它的所有后继节点，如果此后继节点在当前强连通分量中，则此后继节点为循环入口，赋值给base。循环结束后返回base。



### 2. Mem2reg





## 思考题
### LoopSearch
1. 循环的入口如何确定？循环的入口的数量可能超过1嘛？
```txt
先是通过Tarjan算法找到所有的强连通分量，然后对每一个强连通分量，都调用find_loop_base函数，传入强连通分量和reserved集合，对强连通分量中的每个节点，都遍历它的前驱节点，如果有节点的前驱节点不在强连通分量中，则此节点为循环入口，置为base。然后如果通过此次循环找到了base，则返回此base；否则就说明这个强连通分量是一个内层循环，外层循环的base已经被删除，且插入到reserved中，所以要在reserved中继续找，对于reserved集合的每一个节点，都遍历它的所有后继节点，如果此后继节点在当前强连通分量中，则此后继节点为循环入口，赋值给base。循环结束后返回base。

循环入口的数量不会超过1，因为在Tarjan算法中，即traverse函数中，只有当n的index和lowlink相等时才会插入一个强连通分量，而所有node的index是唯一的，所以在一个强连通分量中，循环的入口也是唯一的。
```



2. 简述一下算法怎么解决循环嵌套的情况。

```txt
在run()函数的while (strongly_connected_components(nodes, sccs))循环中，每次都从CFG图nodes中找到强连通分量集合sccs，然后循环调用find_loop_base()找到每个强连通分量的循环入口，存储结果，将此强连通分量中的bb和循环入口的bb组成键值对插入到bb2base中，如果已经存在bb对应键值对，就用当前的循环入口的bb更新bb2base[bb]。最后将此强连通分量的循环入口base从CFG图中删除，并插入到reserved集合中，这一步就是解决嵌套的核心，在下次循环时，又要调用strongly_connected_components()函数，如果原来的循环包含内循环，则在删除循环入口后得到的新的强连通分量就是内层循环，这样再次更新bb2base时内层循环的bb对应的就是内层循环的入口base。如果还有嵌套循环则通过删除循环入口+重新找强连通分量又能够更新对应的bb2base。从而在调用get_inner_loop函数时可以通过bb2base[bb]来先得到此bb对应最内层的循环入口bb，再通过base2loop[bb2base[bb]]得到对应循环。
```



### Mem2reg

1. 请简述支配边界的概念。
2. 请简述`phi`节点的概念，与其存在的意义。
3. 请描述`Mem2Reg Pass`执行前后的`ir`的变化, 简述一下。
4. 在放置phi节点的时候，算法是如何利用支配树的信息的？
5. 算法是如何选择`value`(变量最新的值)来替换`load`指令的？（描述数据结构与维护方法）

### 代码阅读总结

**闫超美:** Pass中用到了很多次哈希表和集合，用来存储bb和node，func，loop等的映射，在求强连通分量时采用的Tarjan算法也很巧妙，在处理循环嵌套的过程，删除掉循环入口node的操作也很妙。体会到Pass对module的处理流程大致就是先建立CFG图，然后对这个CFG图做处理，然后再对节点对应的bb做操作，从而达到优化的目的。



### 实验反馈 （可选 不会评分）

对本次实验的建议

### 组间交流 （可选）

本次实验和哪些组（记录组长学号）交流了哪一部分信息

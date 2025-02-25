{{ self.title() }}

{{ s('description') }}

给定一个 $n$ 个顶点的无根树，顶点编号 $1 \sim n$。以及一个初始为空的集合 $S$，要求支持以下操作：

+ 在集合 $S$ 内新增一个带权元素，元素为该无根树上的一条路径，这条路径的长度（经过的边个数）不会超过 $L$。
+ 给定树上的一个连通块，询问集合 $S$ 中所有路径与连通块有交的元素的权值和。

{{ s('input format') }}

{{ self.input_file() }}

输入的第一行包含两个正整数 $n,m$ 和一个非负整数 $L$，其中 $n,L$ 如题意所示，$m$ 表示操作的个数。

接下来 $n-1$ 行，每行两个正整数 $a, b$，描述一条树边。

接下来 $m$ 行，每行第一个 01 整数 $type$，描述操作的类型。若 $type=0$，则接下来有三个正整数 $p, q, v$，表示在集合 $S$ 中加入一个权值为 $v$ 的元素，该元素在树上的路径为 $p\to q$；若 $type=1$，则接下来一个正整数 $k$，描述询问的连通块所代表的子图中度数为 $1$ 的顶点个数，然后接下来 $k$ 个互不相同的正整数，描述这 $k$ 个顶点的编号。接下来一个非负整数 $r$，描述询问的连通块所代表的子图中度数大于 $2$ 的顶点个数。接下来 $r$ 个互不相同的正整数，描述这 $r$ 个顶点的编号。**特别地，若该连通块的大小为 1，则该行的 $k=1,r=0$，且 $k$ 后紧跟一个正整数，描述该连通块内的唯一顶点编号**。

{{ s('output format') }}

{{ self.output_file() }}

对于每个询问，输出一行一个整数，描述答案。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [6,2,3,2,2,3,10], font_size=10) }}

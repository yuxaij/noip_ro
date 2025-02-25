{{ self.title() }}

Author: yuxaij@gmail.com

## 强连通分量缩点

若 A 可以广播到 B，不妨连一条边 (A,B)，这样构成了一张有向图。容易看出，对于这张图中的一个强连通分量(Strongly Connected Component, SCC) 而言，如果某一个点在某一次更新中被访问到，则这个 SCC 内的所有点都会在此次更新中被访问到。

因此，对于最坏情况而言，更新次数不会超过强连通分量的总个数 $M$。而我们也可以构造出更新次数为 $M$ 的方案：将这些强连通分量按逆拓扑序更新，则每一次都只会更新到恰好一个强连通分量。

对于最好情况而言，显然更新次数不会低于这个强连通分量的 DAG 中，入度为 0 的强连通分量个数。而等于这个数值的答案也很明显：每次更新一个入度为 0 的强连通分量即可，这样对于任意度数不为 0 的强连通分量，沿着其的入边反向走，由于不存在环，因此总会走到一个入度为 0 的强连通分量，故这个度数不为 0 的强连通分量会在这一次更新中被访问到。

## TARJAN 算法求强连通分量

考虑随意找一个点做 DFS。则这一次 DFS 中找到的所有点一定构成一些完整的强连通分量。若一个强连通分量不完整，即某个点 $t$ 在这次 DFS 之外，那么显然存在该强连通分量中的一个点 $s$，使得 $s$ 在本次 DFS 内，且有 $s$ 到 $t$ 在该强连通分量内的路径 $s \to a_1 \to a_2 \to a_k \to t$，归纳有 $a_1, a_2, a_k$ 必然在本次 DFS 内，则 $t$ 也应在本次 DFS 内，矛盾。

故我们可以每次选一个还未被访问过的点做 DFS 来求出一些强连通分量。考察这些强连通分量在 DFS 树上的分布。首先容易发现，一个强连通分量必然是 DFS 树上的一个连通块。这个条件可以这样描述：

> 若两个点 $a,b$ 在同一个强连通分量中，则 $LCA(a,b)$ 也在该强连通分量中。

考虑反证法。首先注意到本次 DFS 中的非树边只有以下几种情况：

+ 从一点 $u$ 向其子树中某点的连边。显然去掉这些边，连通性不变。

+ 从一点 $u$ 向其某个祖先 $parent_u$ 的返祖边。

+ 从一点 $u$ 向某个不是其祖先的点 $v$ 连边，$v$ 在 DFS 序中的位置必然比 $u$ 靠前。

不妨令 $a$ 在 DFS 序中的位置比 $b$ 靠前。那么若 $a,b$ 强连通，则必然存在一条 $a \to b$ 的路径 $a = c_0 \to c_1 \to c_2 \to c_k = b$。这个路径必然存在一个 $i$ 使得 $c_i$ 的 DFS 位置比 $b$ 靠前，$c_{i+1}$ 的 DFS 序位置至少在 $b$ 之后（包括 b)。此时这是一条沿树边的转移，因此必然有 $c_i$ 为 $c_{i+1}$ 的父亲，即 $c_i$ 为 DFS 到 $b$ 时的一个活跃点，即 $b$ 的某个祖先，故 $a, father(b)$ 强连通，归纳可知，最终一定有 $father(b)=lca(a,b)$。

因此对于一个点而言，我们只要知道它是否为所属强连通分量的入口（即公共祖先）。如果对于每个点我们都求出这个 01 变量，那么实际上就求出了所有的强连通分量。

一个点不是所属强连通分量的入口当且仅当存在一条路径，使得其能走到某个祖先。如果只有返祖边，这就是一个非常简单的树形 DP：每个点记录从这个点直接连出的边中深度最小的祖先，然后判断该点子树内记录的最小深度是否比该点更小即可。

考虑带上不是返祖边的 $(u,v)$。此时如果 $(u,v)$ 不在同一个强连通分量中，那么有两种情况：

+ $v$ 到 $LCA(u,v)$ 的路径上存在一个强连通分量的入口，此时 $v$ 所属强连通分量显然已求出（如果你觉得该强连通分量已求出的事实不明显，我们等会会说明如何处理）。
+ $v$ 到 $LCA(u,v)$ 的路径上不存在一个强连通分量的入口，但是 $u$ 到 $LCA(u,v)$ 的路径上存在。这个其实是不成立的，因为此时我们有 $v \to LCA(u,v) \to u \to v$。

因此要么 $v$ 所属强连通分量已求出，要么 $u,v$ 同属一个强连通分量。若是后者，我们可以发现将这条 $u \to v$ 的边修改为 $u \to LCA(u,v)$，对连通性没有影响：如果 $LCA(u,v)$ 是入口，那么显然；如果 $LCA(u,v)$ 不是入口且 $u$ 能通过 $v$ 到达一个比 $LCA(u,v)$ 更浅的位置 $t$，那么由于在 $LCA(u,v)$ 位置 $u,v$ 都会被考虑到，因此这个信息存在 $v$ 处，或者更靠前即可。

更严谨地说，具体考虑这条路径 $u \to v \to c_1 \to c_k \to t$ ，以及 $[LCA(u,v), t)$ 这个祖先链上的任何一个点 $s$，路径上必然一个 $i$ 使得从 $s$ 子树内的 $c_i$ 跳到了子树外的点 $c_{i+1}$，此时有 $lca(c_i, c_{i+1})$ 为 $s$ 的祖先，因此 $s$ 不会被看做一个入口。

这样算法就完成了。对于之前所说强连通分量已求出这个事实不明显的情况，把这个事实和算法一起做归纳证明即可。

最后考虑 LCA 怎么求。事实上我们没必要具体地求出它是谁，而只要保证在 $[u, LCA(u,v))$ 上的所有点在 $u$ 的影响下都不会被看做是入口，用 $v$ 的 DFS 序位置即可。同理，返祖边也可以用 DFS 序的位置。

整体上看就是 TARJAN 算法。

## 优化连边

注意到每个城市相当于向某个区间内的所有城市连边。不妨用线段树来优化这个过程：

1. 将城市位置离散化，这样一个城市所连的区间规模缩减到 $[1,n]$。
2. 构建一个 $[1,n]$ 的线段树，线段树上的每个节点向其两个儿子连一条有向边。线段树表示区间 $[a,a]$ 的叶子向编号为 a 的城市连边。
3. 若编号为 $a$ 的城市所连的区间为 $[l_a, r_a]$，则在线段树上询问该区间。若在询问过程中，发现当前节点所表示区间 $[L, R] \subseteq [l_a, r_a]$，则从城市 $a$ 向该节点连一条边，并 RETURN。根据线段树的性质可知，所有被从城市 $a$ 连边节点所表示的区间两两交集为空，并集为 $[l_a,r_a]$。 

必要性：若城市 $a$ 可以不经过其他城市而直接广播到城市 $b$，则 $b \in [l_a, r_a]$，根据 3. 可知，城市 $a$ 必然向 $b$ 所在叶子的某个祖先节点 $p$ 连边，而根据 2. 可知，$p$ 可到达 $b$。结合可知在新图上 $a$ 可到达 $b$。

充分性：再考虑新图中，若城市 $a$ 可以不经过其他城市，即只经过线段树上的节点，而直接到达某个城市 $b$ 的话，城市 $a$ 必然向 $b$ 的某个祖先节点 $p$ 连了边，根据 3. 可知，在原图中 $a$ 所连区间必然包含 $b$，因此原图中也有 $a$ 可直接到达 $b$。

故新图和原图中，所有城市之间的连通性是等价的。

对新图做缩点，最后只考虑含有城市的强连通分量即可。注意线段树中有些节点可能是无用的：例如，如果没有城市向根节点 $[1,n]$ 连边，那么这个根节点就应删去。

实现时可以只从城市顶点开始 DFS。

## 递推维护

考虑线性的递推。假设我们已经维护了城市 $1 \sim K-1$ 构成子图中的所有强连通分量（虽然我们现在并不知道是怎么维护的），现在想知道加入城市 $K$ 后这个子图的信息如何变化。

不妨先来考虑一个强连通分量在数轴上是怎样的。

首先注意到，若存在一条广播链 $a_1 \to a_2 \to \cdots \to a_k$，则该广播链上所有广播区间的并集是连续的。很容易用归纳证明：

+ 若 $k=1$，广播区间为 $[x_{a_1} - d_{a_1}, x_{a_1} + d_{a_1}]$，显然成立。
+ 令 $k=i-1$ 的广播区间为 $[l_{i-1}, r_{i-1}]$，则由于 $x_{a_i} \in [l_{i-1}, r_{i-1}], ~[l_{i-1}, r_{i-1}] \cap [x_{a_i} - d, x_{a_i}+d] \neq \varnothing$，故 $k=i$ 时结论亦成立。

容易推广到：对于一个强连通分量而言，这个强连通分量的广播范围是一个连续的区间——考虑能广播到最远左端点的城市 $a$ 和最远右端点的城市 $b$ 之间的广播链即可。

此外，若一个城市可以广播到一个强连通分量，只需要能广播到这个强连通分量中最靠左的城市或者最靠右的城市即可。因此一个强连通分量 $A$ 可以用 $[lef_A, l_A, r_A, rig_A]$ 表示：这个强连通分量的广播能力为 $[lef_A, rig_A]$，接受广播时只用考虑 $l_A$ 或者 $r_A$。为了方便，假设这 4 个数都做过离散化处理。

由于一个强连通分量是一个类似区间的元素，因此可以再考察强连通分量之间的位置关系。

1. 若强连通分量 A 和 B 相交且不呈包含关系，例如 $l_A < l_B < r_A < r_B$，则显然有 A 可以广播到 $l_B$，而 B 可以广播到 $l_A$。因此这种情况不存在。
2. 若强连通分量 A 和 B 呈包含关系，则 A 可以广播到 B，而 B 无法广播到 A 范围以外的任何强连通分量，包括 $A$。

对于第二种情况，可以发现这个强连通分量无论加入 $K,K+1,\dots,n$ 都不会发生变化。否则，考虑第一个使 B 产生变化的 $K'$，此时要存在一条从 B 广播到 $K'$ 的链，但若存在的话，B 要经由某个城市 $a' < K'$ 广播出强连通分量 A 的范围 $[l_A, r_A]$，此时经由 $a'$ 有 A,B 强连通，即第一个使 B 产生变化的是 $a' < K'$，矛盾。

因此找到这样的强连通分量后就令最坏情况 $+1$ 即可。虽然我们现在不知道这是怎么找到的，但通过归纳，我们只要保证在加入城市 $K$ 后，新产生的类似强连通分量都被找到即可。

总而言之，这样的强连通分量不会再变化。那么所有可能被影响的强连通分量满足 $[l, r]$ 互不相交，显然可以用一个栈来存储这些强连通分量。

差不多可以考虑加入新城市 $K$ 后的变化。显然，新城市能到达的强连通分量是栈顶的连续部分。由于边可以一条一条加，我们先考虑栈顶的强连通分量 T 与城市 $K$ 所代表的元强连通分量的关系：

1. $rig_T \geq x_K(l_K)$，即 T 能广播到城市 $K$ 所在强连通分量，同属一个强连通分量。显然新强连通分量 $T+K$ 的 $lef,rig,l,r$ 都可以 $O(1)$ 得到，求出 $T+K$ 后代替 $K$，考虑栈顶的下一个强连通分量即可。

2. $rig_T < x_K(l_K)$，但是或许 $T$ 依然能广播到 $K$，通过一条向栈底稍微走一走的广播链 $T \to T' \to \cdots \to T^{(r)} \to x_K$。注意到此时 $rig_{T^{(r)}} \geq x_K \geq l_{T}$ 且 $lef_{T^{(r)}} < l_T$,因此在 $K$ 之前这两个分量就是强连通的，矛盾。

这之后有两种思路。

## 思路 1.

对于 2. 中的 $T$，考虑其会不会成为一个被包含的强连通分量。显然当且仅当在 $T$ 之后存在一个强连通分量和**当前的 $K$**可合并时，$T$ 会成为这样的强连通分量。如果在 $T$ 之后这样的强连通分量不存在，$K$ 也不会再变化。

如何确定栈中下一个能和 $T$ 合并的强连通分量？这相当于询问栈中的一个从栈顶出发的后缀最大值。由于栈顶和询问的 $lef$ 都是变化的，最坏情况下可以认为询问随机的区间，因此线段树显然可以做到；当然注意到这是一个栈结构，利用倍增后缀则可以在 $O(n \log n)$ 的空间开销下完成该问题。确定了这个强连通分量在栈中的位置后，统计新生成的，被包含的强连通分量个数。

最后加入城市 $n$，显然所有入度为 $0$ 的强连通分量都在栈内。如何求出这些强连通分量？一个最简单的思路是用二分求出每个分量在栈内对应的广播范围，然后打上区间标记即可。另一个思路是若栈中第 $i$ 个分量的入度不为 $0$，则要么被 $1 \sim i-1$ 中某个分量的 $rig$ 覆盖，要么被 $i+1 \sim n$ 中某个分量的 $lef$ 覆盖。统计 $rig$/$lef$ 的前缀最大值/后缀最小值即可。

这个算法的复杂度瓶颈在于确定栈中最后一个能和 $T$ 合并强连通分量的时间复杂度为 $O(\log n)$，整体时间复杂度除了常数以外，实际上和线段树优化连边的方法一样。

### 优化思路 1.

考虑到如果我们发现存在一个 $T'$ 可以和 $K$ 合并，则下一次找可合并的强连通分量直接考虑 $l_{T'}$ 即可。因此一个思路是每当栈内新加一个元素时，维护它之前倒数的第一个能直接访问他的元素。注意到若维护中存在 $A$ 可以访问 $K$，则 (A, K) 这个开区间内的所有强连通分量向后访问的能力不会超过 $K$，即这个开区间内的强连通分量都不可能成为访问之后 $K+1,K+2,\dots, n$ 的元素，可以不再考虑。

问题变成找到第一个可以和 $K$ 合并的 $T'$，沿着栈顶元素的逆访问链查询即可。问题在于这个查询并不一定附带退栈操作，时间复杂度还需证明。注意到维护第一个能访问到 $K$ 的元素也需要沿着这个逆访问链走，而且这一部分的维护是单调的 - 一旦 $K$ 走到了访问链的位置 $i$，则之后只用考虑 $i$ 之前的部分。而维护第一个能访问到 $K$ 的元素包含找到第一个可以和 $K$ 合并的 $T'$ 的工作——只需要再判定是否 $K$ 能到达 $T'$ 即可。

实际上这个优化可以直接推进到思路 2。

## 思路 2.

做更进一步的推导。

3. 根据 2. 可知道若 $rig_T < x_K$，则 $T$ 必然无法广播到 $K$，因此 $T$ 在这一轮不发生变化。同理可推出 $T$ 在任意 $K' > K$ 时都不发生变化，因此 $T$ 之后无用。此时由于 $K$ 可以广播 $T$，$T$ 不是入度为 $0$ 的强连通分量，因此令最坏情况的答案 +1 即可，然后考虑栈顶的下一个强连通分量。

这样任务依然是求出最后栈中入度为 $0$ 的强连通分量。但此时有一个问题：由于 $K$ 可以访问到 3. 中的这些 $T$，因此最终栈内强连通分量的 $lef$ 并不准确，甚至可能 $rig$ 不准确——可能有一个在 $T$ 之前的元素也可以访问 $T$。

解决这个问题的思路，或者说解释，有两种：

1. 注意到 $T$ 若存在多个入度，只保留一条入度不会影响最终答案。因此只保留 $T,K$ 之间的入度即可。即对于 3. 中的所有 $T$，从栈中撤走时，用其的 $lef, rig$ 更新 $K$ 的 $lef,rig$。这样实际上我们可以认为栈中的一个元素是一个 "强连通分量 DFS 树上的连通块"，$l,r$ 继承连通块根的值，而 $lef,rig$ 则以连通块内的最大广播范围为准。

2. 注意到每次将 $K$ 加入栈时，$K$ 无法广播到此时的栈顶元素。即栈顶元素都无法广播到栈内之前的元素。考虑栈顶第二个元素产生的时候，其也无法广播到第三个元素之后的部分，因此通过归纳可知，**任何时候栈内元素只能向后广播**，即栈底元素只向栈顶元素连边。因此 $lef$ 无用，而对于 $rig$，由于 $T$ 无法广播到 $K$，因此任何元素无法通过 $T$ 广播到 $K$ 之后的内容，即 $rig$ 也无用。即直接撤走这个元素是没有问题的。

由于 2. 是必然满足的性质，1. 的工作其实是无用的，但从正确性上，1. 的解释和做法并没有错。 

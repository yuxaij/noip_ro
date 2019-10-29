{{ self.title() }}

Author: yuxaij@gmail.com

## 算法 1

模拟足够多次，打表。

## 算法 2

令 $S$ 表示当前正面朝上的硬币集合。注意到每次操作不会使 $S$ 减小，因此以 $S$ 为状态，可以写出一个 DAG。

令 $P(i, S)$ 表示在第 $i$ 轮时，正面朝上的硬币集合为 $S$ 的概率。显然有转移
$$P(i, S) = \sum_{T \subseteq S} P(i-1, T) \times trans(T, S)$$ 

其中 $trans(T, S)$ 表示一轮操作内从 T 转移到 S 的概率。最终答案即为 
$$\sum_{i=1}^{\infty} (P(i, 1) - P(i-1, 0)) \times i = \lim_{n \to \infty} n \times P(n, 1) - \sum_{i=0}^{n-1} P(i, 1) = \lim_{n \to \infty} \sum_{i=0}^{n-1} 1 - P(i, 1) $$。

答案显然是收敛的。枚举足够多层即可，打表。

## 算法 3 

考虑优化上面的极限式。注意 $1 - P(i,1) = \sum_{T \neq 1} P(i, T)$，因此我们可以化为求：
$$\sum_{T \neq 1} \sum_{i=0}^{\infty} P(i, T) = \sum_{T \neq 1} cumP(T) $$

注意 $cumP(T)$ 在本题内的数学含义为 **直到所有硬币朝上为止，期望有多少次操作后硬币朝上的集合为 T，最开始没有操作时也要计算一次**。

利用转移式展开 
$$\begin{aligned}
cumP(T) &= \sum_{i=0}^{\infty} P(i, T) \\
&= \sum_{i=0}^{\infty} \sum_{Q \subseteq T} P(i-1, Q) \times trans(T, S) \\
&= cumP(T) \times trans(T, T) + \sum_{Q \subset T} cumP(Q) \times trans(Q, T)
\end{aligned}$$

解得：
$$cumP(T) = \frac{\sum_{Q \subset T} cumP(Q) \times trans(Q, T)}{1 - trans(T, T)}$$

这个转移的边界条件为 $cumP(0) = 1$。

## 算法 4

关于算法 3 的转移。最精确的做法为维护 $cumP(T)$ 的分子分母，因此转移时可以通分。具体地说，$\forall Q \subset T$，将 $cumP(Q)$ 的分母化到同一水准上即可。

由于分母一定形如 $\binom{n+1}{2}^k$ 的格式，因此可以直接记录 $k$，在最后计算时再除去即可。这样只需要高精度整数。

## 算法 5

利用容斥原理。
$$1 - P(i,1) = \sum_{S > 0, S \in [n]} (-1)^{|S|-1} P(i, x_{S_j} = 0)$$

$$Ans = \sum_{S>0, S\in [n]} (-1)^{|S|-1} cumP(x_{S_j} = 0)$$

注意到确定了正面朝下的硬币集 $S$ 后，我们每次操作可以选择的区间个数 $r(S)$ 就确定下来了。因此可知

$$cumP(x_{S_j} = 0) = \sum_{i=0}^{\infty} \left(\frac{r(S)}{\binom{n+1}{2}} \right)^{i}$$
可以直接用等比数列求和公式得到。

利用 DP 可以求出 $r(S)$ 为一个确定值的 $S$ 有多少个，这样就不需要枚举 $S$。

最后在算法 5 的基础上加入高精度即可。


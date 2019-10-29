{{ self.title() }}

Author: yuxaij@gmail.com

## 枚举 + HASH

可以考虑枚举所有可行的串。咋看之下，对于单个前缀的判断没有较高效率的做法，因此可以考虑枚举 AB 这个循环节，然后求出有哪些前缀可以被 AB 满足。

首先要判断对应的前缀 $\overline{ABAB\dotsAB}$ 是否满足条件。若满足，则再枚举 A，判断 $S[len(ABAB\dotsAB)+1, \dots, n]$ 是否有一个前缀为 A 即可。容易看出，合法的 A 共有 $LCP(S[len(ABAB\dotsAB)+1, \dots, n], AB)$ 个。也就是所有的 
$$p = len(ABAB\dotsAB), \dots, len(ABAB\dotsAB) + LCP(S[len(ABAB\dotsAB)+1, \dots, n], AB)$$
都满足条件，这是一个区间标记。将所有的区间标记求出后扫描线统计即可。

对于求 LCP，可以用二分 + HASH 做到。对于判断 $\overline{ABAB\dotsAB}$ 是否满足条件，暴力枚举每一个 AB 并判断即可。根据调和级数可知，需要判断的总次数不会超过 $\sum_{len(AB)=1}^{n} \lfloor n / len(AB) \rfloor \sim n \log n$。当然也可以直接考虑所有长度大于 $n / K$ 的 AB 都不会被枚举，因此最多只要判断 $n / K \times (K-1) < n$ 次。

利用前缀和相减，字符串的 HASH 值可以 $O(1)$ 求得。

注意若 HASH 值直接取 $2^k$ 之类，很容易构造数据使得两个不相等的串的 HASH 值相等。

## KMP

考虑若一个前缀可以被拆分为 $(AB)^k A$ 的形式，且我们称 $AB$ 为该前缀的一个不完全循环节。则这个前缀在 KMP 算法中，fail 指针至少不小于 $(AB)^{k-1}A$，且 fail 指针链必然经过 $(AB)^{k-1}A$。

又容易看出，在 KMP 算法中，若 $fail[n] = m$，则前缀 $S[1\dots n]$ 有一个不完全循环节的长度为 $|n-m|$。

结合两者可知：在 KMP 算法中，若 $fail[n] = m$，则前缀 $S[1\dots n]$ 的最小不完全循环节长度为 $|n-m|$。

让我们考虑 AB 和这个最小循环节 $C$ 的关系。首先凭直觉，$\exists R, ~AB=C^{r}$。

如果这个直觉是对的，那么设 $S[1\dots n] = C^{s} T$，其中 T 为 C 的某个前缀，则我们只需要考虑 $r = \lfloor s / K \rfloor$。

+ 若 $r > \lfloor s / K \rfloor$，则 $AB^{K} > C^{s}$，矛盾。
+ 若 $r < \lfloor s / K \rfloor$，且这样的 AB 合法，则必然有 $A = C^{S - rK}T$。此时由于 $(r+1)K < C$，因此令 $AB = C^{r+1}, A = C^{S - (r+1)K} T$，依然是一个合法方案。

故判断下式即可
$$\lfloor s / K \rfloor \geq (s ~\mathrm{mod} ~K) + [T = \varnothing] eps.$$

## 证明

考虑如何证明。假设不正确，意味着此时 $k \geq 2$，且存在一个合法的 AB 不是 C 的一个完全循环，但是是 $S[1\dots n]$ 的一个不完全循环节。

将 AB 和 C 在字符串中的循环形式画出来，容易看到存在一个 C 跨越了两个 AB，而这个 C 内实际上满足了以下的关系：

$$C[i ~\mathrm{mod} ~|C|] = C[(i + |AB|) ~\mathrm{mod} ~|C|]$$

容易看出这将产生若干个循环，且每个循环内的元素个数相等——这说明 C 是某个更小字符串的完全循环，与 C 是最小不完全循环节的条件矛盾。

## 另一个方法

如果发现自己难以证明该如何处理？考虑按 fail 边建有根树，可以发现问题变为，对于每个顶点，询问是否存在一个祖先，满足其祖先的位置在某一个区间内，这个区间的左端点和右端点都是递增的。

可以注意到这个问题和 NOI2014 Day2 T1 动物园是类似的。

## Z-Algorithm

回到 Hash 部分的算法，效率瓶颈在于必须要二分算出一个位置开始的后缀与原串的 LCP。实际上这个问题可以利用 Z-Algorithm 在 $O(n)$ 时间内求出。在此亦不赘述，可以参考 http://codeforces.com/blog/entry/3107。


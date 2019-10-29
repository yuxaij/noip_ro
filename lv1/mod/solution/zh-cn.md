{{ self.title() }}

author: yuxaij@gmail.com

## 算法 1

当 $a,p$ 相等时，只需要求出 $a$ 在模$p$意义下的一个幂循环节 $t$，然后求解 $bx \equiv t (\mathrm{mod}~p)$ 的模方程即可。求解该模方程可以用拓展欧几里得算法。

## 算法 2

考虑所有质数 $p$，利用费马小定理 $a^{p-1} \equiv 1 (\mathrm{mod}~p)$，然后求解 $bx \equiv p-1 (\mathrm{mod}~p)$ 即可。

考虑费马小定理的证明。令 $S = \{1, 2, \dots, p-1\}, aS = \{a ~\mathrm{mod} ~ p, 2a ~\mathrm{mod} ~ p, \dots, (p-1)a ~\mathrm{mod} ~ p\}$，注意到由于 $p$ 是质数，因此 $aS$ 中必然不存在 $0$，且 $aS$ 中的元素两两不相等——那么实际上 $S = aS$，将两个集合中的所有元素在模意义下相乘得到 
$$ mul(S) \equiv mul(aS) \equiv (p-1)! \equiv a^{p-1}(p-1)! ~(\mathrm{mod} ~ p)$$
显然有 $a^{p-1} \equiv 1 ~(\mathrm{mod} p)$。

费马小定理也可以用来求逆元，$a^{-1} \equiv a^{p-2} ~ (\mathrm{mod} p)$。

## 算法 3

考虑 $p$ 非质数的情况。首先 $a,p$ 必然互质，否则无解。拓展费马小定理的证明，我们令 $S$ 为所有与 $p$ 互质的数的个数，那么由于 $a$ 与 $p$ 互质，我们很容易得到 $S = aS$，也就是 $a^{\phi(p)} = 1 (\mathrm{mod} ~ p)$。这个即为欧拉-费马小定理。

如果此时 $b,p$ 互质，那么我们直接求解方程即可。

## 算法 4

注意欧拉-费马小定理只能说明 $\phi(p)$ 是 $a$ 的一个幂循环节，而非最小的幂循环节 $min\_cir(a,p)$。例如 $\phi(48) = 2^3 \times (2-1) \times (3-1) = 16$，而显然我们有 $7^2 \equiv 1 (\mathrm{mod} ~ 48)$。

当 $b,p$ 不互质的时候，$bx$ 在模 $p$ 意义下可以产生的数有限，但我们想知道的是 $bx$ 所产生的数中是否存在一个数为最小幂循环节 $min\_cir(a,p)$ 的倍数，而非产生了 $\phi(p)$。也就是说，**有可能 $bx \equiv \phi(p) (\mathrm{mod} ~ p)$ 无解，但原方程有解。** 此外，即使将所有 $\phi(p)$ 的倍数也考虑进来，也是不够的。

考虑 $p = 2 \cdot 3^2 = 18$ 时的一个反例，此时有 $\phi(p)=1 \cdot 2 \cdot 3 = 6$。我们可以找到 $7^3 \equiv 1 (\mathrm{mod} ~18)$，再令 $b=3^2=9$。由于 $gcd(b,p)=9$，$bx \equiv k\phi(p) (\mathrm{mod} ~ p)$ 是不存在解的，但显然有 $x=1$ 时，$7^{9} \equiv (7^3)^3 \equiv 1 (\mathrm{mod} ~18)$。

考虑怎么找 $min\_cir(a,p)$。首先 $min\_cir(a,p)$ 一定是 $\phi(p)$ 的一个因数，且对于任意的 $k$ 均有 $a^{k \times min\_cir(a,p)} \equiv 1 (\mathrm{mod} ~ p)$。考虑将 $\phi(p)$ 和 $min\_cir(a,p)$ 质因数分解：

$$\begin{aligned}
\phi(p) &= p_0^{\alpha_0} p_1^{\alpha_1} \cdots p_m^{\alpha_m} \\
min\_cir(a,p) &= p_0^{\beta_0} p_1^{\beta_1} \cdots p_m^{\beta_m} 
\end{aligned}
$$ 

显然有 $\beta_i \leq \alpha_i$。我们考虑如何确定 $\beta_0$，可以发现，对于所有的 $\gamma \in [\alpha_0, \beta_0]$，均有
$$\exists K = p_1^{\alpha_1-\beta_1} \cdots p_m^{\alpha_m-\beta_m}, ~s.t., \quad p_0^{\gamma} p_1^{\alpha_1} \cdots p_m^{\alpha_m} = k \times min\_cir(a, p)$$ 

即此时这个数依然是一个循环节。因此我们可以暴力枚举 $\gamma$，每次枚举后判断 $a$ 对应的次幂是否模 $p$ 意义下为 $1$ 即可，一直枚举到 $\gamma=\beta_{0}-1$，发现此时对应的次幂模 $p$ 不为 $1$ 时，我们即确定了 $\beta_0$ 的值。

类似的，我们也可以确定 $\beta_1, \beta_2, \dots, \beta_m$ 的值。由于枚举的次数最多为 $O(\log \phi(p))$ 次，每次枚举都可以通过快速幂计算，故这一部分的时间复杂度为 $O(\log^2 p)$。

求出 $min\_cir(a,p)$ 后，考虑如何判断 $bx$ 所产生的数中存在一个数为 $min\_cir(a,p)$ 的倍数。首先容易知道 $bx$ 能产生的数集为 $\{ gcd(b,p), 2gcd(b, p), \dots, p - gcd(b, p)\}$，因此只要找一个 $i \times gcd(b,p)$
为 $min\_cir(a,p)$ 的倍数即可，这个数显然为 $gcd(b,p) \times min\_cir(a,p) / gcd(gcd(b,p), min\_cir(a,p))$。判断这个数是否小于 $p$ 即可。

## 算法 EX

也可以用大步小步算法来找最小的循环节 $min\_cir(a,p)$。令 
$$min\_cir(a,p) = k\lfloor sqrt(p) \rfloor - s ~(0 \leq s < \lfloor sqrt(p) \rfloor)$$

预处理出所有的 $a^{s}$ 并枚举 $k$，每次只需要判断是否存在一个 $a^{s}$ 满足
$$ a^{s} \equiv a^{k\lfloor sqrt(p) \rfloor} (\mathrm{mod} ~ p)$$

即可。利用 HASH 可以在 $O(1)$ 时间内解决这个判断，复杂度 $O(\sqrt{p})$。

{{ self.title() }}

{{ s('description') }}

已知 $n$ 组正整数 $a, b, p$，对于每一组，请求出下列模方程的一个可行解 $x$
$$a^{(bx ~\mathrm{mod} ~p)} \equiv 1 ~ (\mathrm{mod} ~p) $$

同时要求 $bx \not\equiv 0 ~(\mathrm{mod} ~p)$ 且 $x \in [0, p)$。

{{ s('input format') }}
{{ self.input_file() }}

输入包含多行，每行三个正整数 $a,b,p$，描述一组方程的参数。保证 $p \geq 2$。

输入以 `EOF` 结束。

{{ s('output format') }}
{{ self.output_file() }}

输出包含多行，依次对于每组询问，给出一个可行的答案 $x$。若无解，则输出 $-1$。

若你对于所有 $p$ 为素数的询问都给出了可行的 $x$，则你可以获得 $50\%$ 的分数。

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [3,2,2,2,8], font_size=10) }}

{{ s('hint') }}

有必要的话，可以考虑推广费马小定理的证明。


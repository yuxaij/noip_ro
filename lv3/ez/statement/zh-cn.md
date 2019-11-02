{{ self.title() }}

{{ s('description') }}

给出 $k$ 个大小为 $k$ 的集合，集合中的每个元素带权。一个合法的选择方案从每个集合中选出恰好一个元素，且获得这 $k$ 个元素的总权值作为方案的代价。

显然，一共有 $k^k$ 种合法的选择方案。求出这些方案中前 $k$ 小的代价是多少。

{{ s('input format') }}
{{ self.input_file() }}

输入包含多个集合组。

对于每一个集合组，第一行为一个正整数 $k$。接下来 $k$ 行，每行 $k$ 个正整数，描述一个集合中 $k$ 个元素的权值。

输入以 `EOF` 结束。

{{ s('output format') }}
{{ self.output_file() }}

依次对于每组询问，输出一行 $k$ 个正整数，描述前 $k$ 小的方案代价。

{{ s('sample') }}
{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data', width = [4,2,2,2]) }}

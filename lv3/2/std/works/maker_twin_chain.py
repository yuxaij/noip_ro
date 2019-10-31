from tqdm import tqdm
from copy import copy
import numpy as np
import random

class Section():
    def __init__(self, nodes, n_pathes):
        self.nodes = nodes
        self.n_pathes = n_pathes

    def pop(self):
        self.n_pathes -= 1
        return self.n_pathes == 0

    def rand(self, all_nodes, force = True):
        if force or np.random.rand() < (1. / (self.n_pathes + 2)):
            return random.choice(all_nodes)
        else: return None

class RandomSection(Section):
    def rand(self, all_nodes):
        a = super().rand(all_nodes, False)
        if a is None:
            return random.choice(self.nodes)
        else:
            return a

class ChainSection(Section):
    def __init__(self, nodes, rangas):
        super().__init__(nodes, len(rangas))
        self.rangas = rangas
        self.ranga_index = 0

    def pop(self):
        self.ranga_index += 1
        return super().pop()

    def rand(self, all_nodes):
        a = super().rand(all_nodes, False)
        if a is None:
            a, b = self.rangas[self.ranga_index]
            return self.nodes[np.random.randint(a, b)]
        else:
            return a

def build_chain_with_tiny_branch(chain_nodes, branch_nodes, exp_branch_size):
    edges = []

    chain_len = len(chain_nodes)
    n_branch_nodes = len(branch_nodes)

    tailers = copy(chain_nodes)

    for i in range(1, chain_len):
        edges.append((chain_nodes[i], chain_nodes[i-1]))

    n_branch = max(1, n_branch_nodes // exp_branch_size)
    branch_loces = np.random.permutation(chain_len)[:n_branch]
    brancha = []

    barricades = np.sort(np.random.permutation(n_branch_nodes - 1)[:n_branch - 1]).tolist() + [n_branch_nodes - 1]
    last = 0

    for i in tqdm(range(len(barricades)), desc='build_chain_with_tiny_branch'):
        entry = chain_nodes[branch_loces[i]]
        cur_branch = []
        for j in range(last, barricades[i] + 1):
            cur_branch.append(branch_nodes[j])
            edges.append((branch_nodes[j], entry))
            entry = branch_nodes[j]

        k = np.random.randint(barricades[i] + 1 - last + 1)

        if k != 0:
            tailers[branch_loces[i]] = branch_nodes[last + k - 1]

        brancha.append(cur_branch)
        last = barricades[i] + 1 

    return edges, tailers, brancha
        
def random_path_from_brancha(brancha, num_path, v_low, v_high):
    probs = [len(l)**2 for l in brancha]
    sump = sum(probs)
    probs = [p / sump for p in probs]

    choices = list(range(len(brancha)))
    
    where_ids = np.random.choice(choices, size = num_path, p = probs)

    pathes = [] 
    for wheta in where_ids:
        wheres = brancha[wheta]
        a, b = np.random.choice(wheres, size=2)
        v = np.random.randint(v_low, v_high)
        pathes.append((a, b, v))

    return pathes

def random_path_from_chain(tailers, num_path, v_low, v_high):
    assert v_high - v_low >= num_path, \
        "error: <random_path_from_chain> {} - {} >= {}".format(v_high, v_low, num_path)

    v_ranges = np.arange(v_low, v_high, (v_high - v_low) // num_path)[:num_path].tolist() + [v_high]

    barricades = np.sort(np.random.permutation(len(tailers) - 1 + num_path)[:num_path])

    last = -1
    lef, rig = 0, len(tailers)
    pathes = []
    path_rangas = []

    for i in tqdm(range(len(barricades)), desc='random_path_from_chain'):
        erasa = barricades[i] - last - 1
        
        erasa_lef = np.random.randint(erasa + 1)
        erasa_rig = erasa - erasa_lef

        lef += erasa_lef
        rig -= erasa_rig

        assert lef <= rig, \
            "error: <random_path_from_chain>, {} < {}".format(lef, rig)

        pathes.append((tailers[lef], tailers[rig - 1], np.random.randint(v_ranges[i], v_ranges[i+1])))
        path_rangas.append((lef, rig))

        last = barricades[i]

    return pathes, path_rangas

def very_random_section(nodes, n_pathes, v_low, v_high):
    edges = []
    for i in tqdm(range(1, len(nodes)), desc='very_random_section_1'):
        edges.append((nodes[i], nodes[max(0, i - np.random.randint(5) - 1)]))

    pathes = []
    for i in tqdm(range(n_pathes), desc='very_random_section_2'):
        pathes.append((random.choice(nodes), random.choice(nodes), np.random.randint(v_low, v_high)))

    return edges, pathes, RandomSection(nodes, len(pathes))

def get_edges_for_sections(sections):
    sections = [sect.nodes for sect in sections]
    n = sum(len(sect) for sect in sections)
    edges = []
    while len(sections) > 1:
        probs = [len(sect) / n for sect in sections]
        try:
            a, b = np.random.choice(list(range(len(sections))), size = 2, replace=False, p = probs)
        except:
            from IPython import embed
            embed()
        edges.append((np.random.choice(sections[a]), np.random.choice(sections[b])))
        
        sections = [sections[i] for i in range(len(sections)) if i != a and i != b] + [sections[a] + sections[b]]

    return edges

def get_sections_and_rand_ops(parts, n_ops, min_queries): # part's v_range should be increasing.
    sections = []
    all_nodes = []
    all_edges = []
    all_pathes = []
    for part in parts:
        mode, nodes, n_pathes, v_low, v_high, meta = part
        if mode == 'random':
            edges, pathes, section = very_random_section(nodes, n_pathes, v_low, v_high)
        elif mode == 'chain':
            n_branch_nodes, exp_branch_size, n_noises, noise_v_low = meta
            edges, tailer, brancha = build_chain_with_tiny_branch(nodes[n_branch_nodes:], nodes[:n_branch_nodes], exp_branch_size)
            pathes, rangas = random_path_from_chain(tailer, n_pathes - n_noises, v_low, noise_v_low)
            pathes += random_path_from_brancha(brancha, n_noises, noise_v_low, v_high)

            section = ChainSection(nodes[n_branch_nodes:], rangas)
        else:
            raise NotImplementedError('section mode {}'.format(mode))

        last_pathes = len(all_pathes)

        sections.append(section)
        all_nodes += nodes
        all_edges += edges
        all_pathes += pathes

    all_edges += get_edges_for_sections(sections) 

    n_dels = last_pathes + np.random.randint(len(all_pathes) - last_pathes + 1) 
    n_queries = max(n_ops - n_dels, min_queries)
    n_dels = n_ops - n_queries

    print('n_dels: {}'.format(n_dels))

    del_loces = [n_ops] + np.sort(np.random.permutation(n_ops)[:n_dels]).tolist()[::-1]
    ops = []

    sections.append(Section(0, len(all_pathes) + 1)) # emtpy section if all pathes are deleted

    for i in tqdm(range(n_ops), desc='get_ops'):
        if del_loces[-1] == i:
            ops.append((0, 0))

            if sections[0].pop():
                sections = sections[1:]
                if sections[0].n_pathes <= 0:
                    from IPython import embed
                    embed()
            del_loces.pop()
        else:
            if sections[0].n_pathes < 0:
                from IPython import embed
                embed()
            ops.append((1, sections[0].rand(all_nodes)))

    return all_edges, all_pathes, ops 

def gen_data(file_name, raw_parts, n_ops, min_queries):
    if min_queries == -1:
        min_queries = n_ops

    last_v = 1
    last_node = 0
    last_path = 0
    parts = []
    for part in raw_parts:
        print(part)
        mode, node, path, v, meta = part
        path = int(path)
        node = int(node)
        v = int(v)
        if mode == 'random':
            parts.append((mode, list(range(last_node, node)), path - last_path, last_v, v, None))
        else:
            n_branch_rate, exp_branch_size, noise_rate, noise_v_rate = meta  
            n_branch_nodes = int(n_branch_rate * (node - last_node)) 
            n_noises = int(noise_rate * (path - last_path))
            noise_v_low = int(v - noise_v_rate * (v - last_v))

            # n_branch_nodes: how many nodes are not in the major chain
            # exp_branch_size: the expected size for a branch that grows from a node at the major chain
            # n_noises: how many path are noises - they do not intersect with the major chain
            # noise_v_low: noise path's value should be high, so it does no influence to pathes in chain

            parts.append((mode, list(range(last_node, node)), path - last_path, last_v, v, 
                (n_branch_nodes, exp_branch_size, n_noises, noise_v_low)))

        last_v = v
        last_node = node
        last_path = path

    all_edges, all_pathes, all_ops = get_sections_and_rand_ops(parts, n_ops, min_queries)

    np.random.shuffle(all_edges)
    np.random.shuffle(all_pathes)
            
    f = open(file_name, 'w')
    mapping = np.random.permutation(last_node)
    #mapping = list(range(last_node))
    lines = []
    lines.append('{} {} {}'.format(last_node, last_path, n_ops))
    lines += ['{} {}'.format(mapping[a] + 1, mapping[b] + 1) for a, b in all_edges]
    lines += ['{} {} {}'.format(mapping[a] + 1, mapping[b] + 1, v) for a, b, v in all_pathes]

    lines += ['0' if a == 0 else '1 {}'.format(mapping[b] + 1) for a, b in all_ops]

    f.write('\n'.join(lines))
    f.close()



if __name__ == '__main__':
    gen_data('test.in', [
        ('chain', 100000, 80000, 1e8, (0.3, 3, 0.06, 0.03)),
        ('chain', 200000, 160000, 2e8, (0.3, 3, 0.06, 0.03)),
        ('random', 300000, 240000, 3e8, ()),
        ('chain', 400000, 320000, 4e8, (0.3, 3, 0.06, 0.03)),
    ], 500000, 250000)

#!/usr/bin/python3

import sys
import random

INF = 10**9
MAXN = 3 * 10**5
MAXQ = 3 * 10**5

DX = [0,1,0,-1]
DY = [1,0,-1,0]

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

def inbounds(r,c):
    return r >= 0 and r < n and c < m and c >= 0

def tp(i):
    return (i//m, i%m)

def ti(r, c):
    return r*m+c

def bfs(sand_list):
    dist = [-1] * (n*m)
    Q = [start]
    dist[start] = 0
    p = 0
    while p < len(Q):
        i = Q[p]
        p += 1
        x1, y1 = tp(i)
        if sand_list[i] == 0:
            for ii in range(4):
                x2 = x1 + DX[ii]
                y2 = y1 + DY[ii]
                if inbounds(x2, y2) and dist[ti(x2,y2)] == -1:
                    j = ti(x2,y2)
                    dist[j] = dist[i]+1
                    Q.append(j)
    return dist

def change_ops(D_from, D_to):
    res = []
    for i in range(n*m):
        if D_from[i] != D_to[i]:
            r,c = tp(i)
            res.append(("!",r+1,c+1,D_to[i]))
    return res

def print_tc(n,m,q,D,ops):
    print(n,m,q)
    for i in range(n):
        row = []
        for j in range(m):
            row.append(D[i*m+j])
        print(*row)
    for p in ops:
        print(*p)

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
q = int(cmdlinearg('q', MAXQ))
mode = cmdlinearg('mode', 'random')
possible = int(cmdlinearg('possible', False))

m = min(m, MAXN//n)

if mode == "random":
    sand_density = float(cmdlinearg('sand_density', 0.5))
    q_density = float(cmdlinearg('q_density', 0.5))
    sand_changes = int(cmdlinearg('sand_changes', 1)) # <- increase to speed up
    start = random.randrange(n*m)
    sand_ind = random.sample(range(n*m), int(n*m*sand_density))
    sand_list = [0] * (n*m)
    for i in sand_ind:
        sand_list[i] = 1
    D = bfs(sand_list)
    D2 = D.copy()

    questions = int(q * q_density)
    modifications = q-questions

    m_ops = []
    valid_options = [0]
    while len(m_ops) < modifications:
        sand_c = random.sample(range(n*m), sand_changes)
        for i in sand_c:
            sand_list[i] ^= 1
        D3 = bfs(sand_list)
        m_ops += change_ops(D2, D3)
        valid_options.append(len(m_ops))
        D2 = D3
    
    valid_options.pop()
    m_ops = m_ops[:modifications]

    ops = []
    question_index = random.sample(range(q), questions)

    if possible:
        question_index = []
        for _ in range(questions):
            question_index.append(random.choice(valid_options))
        question_index.sort()
        for i in range(len(question_index)):
            question_index[i] += i


    is_question = [0] * q
    for qi in question_index:
        is_question[qi] = 1
    
    mp = 0
    for i in range(q):
        if is_question[i] == 1:
            r = random.randrange(n)
            c = random.randrange(m)
            ops.append(("?",r+1,c+1))
        else:
            ops.append(m_ops[mp])
            mp += 1
    
    print_tc(n,m,q,D,ops)

    
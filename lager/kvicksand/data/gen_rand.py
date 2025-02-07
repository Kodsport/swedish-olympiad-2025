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

def nei(i):
    r, c = tp(i)
    res = []
    for dx in DX:
        for dy in DY:
            r2 = dx+r
            c2 = dy+c
            if inbounds(r2,c2):
                res.append(ti(r2,c2))
    return res

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

def line_d(lo, hi, start, i):
    if i < lo or i > hi:
        return -1
    else:
        return abs(start-i)

def line_change_ops(lo_from, hi_from, lo_to, hi_to, start):
    cand = list(range(min(lo_from, lo_to), max(lo_from, lo_to)+1))
    cand += list(range(min(hi_from, hi_to), max(hi_from, hi_to)+1))
    res = []
    for i in cand:
        d_old = line_d(lo_from, hi_from, start, i)
        d_new = line_d(lo_to, hi_to, start, i)
        if d_old != d_new:
            r,c = tp(i)
            res.append(("!",r+1,c+1,d_new))
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

def sand_change(sand_list, sand_changes, mode="random"):
    if mode == "random":
        return random.sample(range(n*m), sand_changes)
    elif mode == "blob":
        boundary = [random.randrange(n*m)]
        ans = set()
        while len(ans) < sand_changes:
            i = boundary.pop()
            N = nei(i)
            boundary += N
            boundary = list(set(boundary))
            random.shuffle(boundary)
            ans.add(i)
        return list(ans)
    elif mode == "square":
        side = int(sand_changes**0.5)+1
        r = random.randint(0, n-side)
        c = random.randint(0, m-side)
        ans = []
        for dx in range(side):
            for dy in range(side):
                r2 = r+dx
                c2 = c+dy
                ans.append(ti(r2,c2))
        return ans
    elif mode == "dig" or mode == "fill":
        ans = []
        tries = 0
        want = 1
        if mode == "fill":
            want = 0
        while len(ans) < sand_changes:
            i = random.randrange(n*m)
            if sand_list[i] == want:
                ans.append(i)
                tries = 0
            else:
                tries += 1
            if tries > 100:
                break
        return ans
    elif mode == "avoid":
        ans = []
        while len(ans) < sand_changes:
            i = random.randrange(n*m)
            if i//m != start//m:
                ans.append(i)
        return ans


def sand_start(sand_density, start, mode="random"):
    if mode == "random":
        sand_ind = random.sample(range(n*m), int(n*m*sand_density))
        sand_list = [0] * (n*m)
        for i in sand_ind:
            sand_list[i] = 1
        return sand_list
    
    elif mode == "chess":
        sand_list = [0] * (n*m)
        black = []
        for i in range(n*m):
            if (i//m+i%m)%2 != (start%m+start//m)%2:
                black.append(i)
        random.shuffle(black)
        b = int(n*m*sand_density)
        if len(black) > b:
            black = black[:b]
        for i in black:
            sand_list[i] = 1
        return sand_list
    
    elif mode == "caves":
        sand_list = [1] * (n*m)
        sand_list[start] = 0
        no_sand = 1
        b = int(n*m*sand_density)
        while no_sand < b:
            L = random.randint(max(n,m),n+m)
            prev = -1
            now = start
            steps = 0
            for _ in range(L):
                N = nei(now)
                if 0 <= prev < len(N) and random.randint(1,10) != 10:
                    now = N[prev]
                else:
                    p = random.randrange(0, len(N))
                    now = N[p]
                    prev = p
                if sand_list[now] == 1:
                    sand_list[now] = 0
                    no_sand += 1
                steps += 1
                if steps > 3*L:
                    break
        return sand_list

    elif mode == "manhattan":
        sand_list = [0] * (n*m)
        black = []
        for i in range(n*m):
            if (i//m)%4 != (start//m)%4 and (i%m)%4 != (start%m)%4:
                black.append(i)
        random.shuffle(black)
        b = int(n*m*sand_density)
        if len(black) > b:
            black = black[:b]
        for i in black:
            sand_list[i] = 1
        return sand_list
    
    elif mode == "horizontal":
        sand_list = [1] * (n*m)
        for i in range(n*m):
            if i//m == start//m:
                sand_list[i] = 0
        return sand_list
        


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
q = int(cmdlinearg('q', MAXQ))
mode = cmdlinearg('mode', 'valid')
possible = int(cmdlinearg('possible', False))
sand_change_mode = cmdlinearg('sand_change_mode', 'random')
sand_start_mode = cmdlinearg('sand_start_mode', 'random')
q_density = float(cmdlinearg('q_density', 0.5))
noise = int(cmdlinearg('noise', 0))

m = min(m, MAXN//n)

if mode == "valid":
    sand_density = float(cmdlinearg('sand_density', 0.5))
    sand_changes = int(cmdlinearg('sand_changes', 1)) # <- increase to speed up
    start = random.randrange(n*m)
    
    sand_list = sand_start(sand_density, start, sand_start_mode)
    D = bfs(sand_list)
    D2 = D.copy()

    questions = int(q * q_density)
    modifications = q-questions

    m_ops = []
    valid_options = [0]
    while len(m_ops) < modifications:
        sand_c = sand_change(sand_list, sand_changes, sand_change_mode)
        for i in sand_c:
            sand_list[i] ^= 1
        D3 = bfs(sand_list)
        co = change_ops(D2, D3)
        random.shuffle(co)
        m_ops += co
        valid_options.append(len(m_ops))
        D2 = D3
    
    if len(valid_options) > 1:
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

elif mode == "random":
    maxd = int(cmdlinearg('maxd', n*m))
    D_possible = [-1] + list(range(1, maxd+1))
    start = 0
    D = [0] + [random.choice(D_possible) for _ in range(n*m-1)]
    ops = []
    for i in range(q):
        if random.randint(1,2) == 1:
            r = random.randrange(0,n)
            c = random.randrange(0,m)
            ops.append(("?",r+1,c+1))
        else:
            i = random.randrange(1, n*m)
            r = i//m
            c = i%m
            d = random.choice(D_possible)
            ops.append(("!", r+1,c+1,d))
    print_tc(n,m,q,D,ops)

elif mode == "line":
    start = random.randrange(1,m-1)
    n=1
    lo = random.randrange(start)
    hi = random.randrange(start+1,m)
    D = [line_d(lo,hi,start,i) for i in range(m)]
    d = int(cmdlinearg('d', 1))
    ops = []

    D_fake = D.copy()
    for _ in range(noise):
        i = random.randrange(m)
        while i == start:
            i = random.randrange(m)
        r = random.randint(1,3)
        if r == 1:
            D[i] += 1
        elif r == 2:
            D[i] -= 1
        elif r == 3:
            D[i] = -1
        if D[i] > MAXN or D[i] == 0 or D[i] < -1:
            D[i] = 1
    
    for i in range(m):
        if D[i] != D_fake[i]:
            j = random.randrange(m)
            ops.append(("?",1,j+1))
            ops.append(("!",1,i+1,D_fake[i]))

    random.shuffle(ops)

    while len(ops) < q:
        j = random.randrange(m)
        ops.append(("?",1,j+1))
        lo2 = lo + random.randint(-d,d)
        hi2 = hi + random.randint(-d,d)
        lo2 = max(0,lo2)
        lo2 = min(start-1,lo2)
        hi2 = min(m-1, hi2)
        hi2 = max(start+1, hi2)
        new_ops = line_change_ops(lo, hi, lo2, hi2, start)
        random.shuffle(new_ops)
        lo = lo2
        hi = hi2
        ops += new_ops
        for _ in range(len(new_ops)):
            j = random.randrange(m)
            ops.append(("?",1,j+1))
    
    if len(ops) > q:
        ops = ops[:q]

    print_tc(n,m,q,D,ops)


    
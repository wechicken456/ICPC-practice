#!/usr/bin/python3
from collections import defaultdict

import time
start = time.time()
n,k = map(int,input().split())
k = n-1-k

graph = defaultdict(set)
for i in range(n-1):
    a,b = map(int,input().split())
    a -= 1
    b -= 1
    graph[a].add(b)
    graph[b].add(a)

par = [-1 for _ in range(n)]
order = []
def dfs(x,p):
    par[x] = p
    for y in graph[x]:
        if y != p:
            dfs(y,x)
    order.append(x)

dfs(0,-1)
def get(first=-1):
    if len(avail) == 1:
        return 0,0
    
    if len(avail) == 2:
        if avail[0] in graph[avail[1]]:
            return 1,1
        else:
            return 0,0

    maxlen = 0
    sub = 1 if first != -1 else 0
    for i in avail:
        if i == first:
            continue
        clen = len(graph[i])
        if first in graph[i]:
            clen -= 1
        maxlen = max(maxlen, clen)
    mn = 1 if len(graph[first]) == len(avail)-1 or maxlen == len(avail)-sub-1 else 0

    mx = 0
    free = set()
    for node in order:        
        left = 2 if node != first else 1
        for child in graph[node]:
            if left > 0 and child in free:
                mx += 1
                left -= 1
        if left > 0:
            free.add(node)

    return mn,mx

prev = -1
ans = [-1 for _ in range(n)]
avail = list(range(n))
mn,mx = get()
if not mn <= k <= mx:
    print(-1)
    exit()

ce = 0
for i in range(n):
    for j in avail:
        mn,mx = get(first=j)
        ne = ce + (j in graph[prev])
        if mn + ne <= k <= mx + ne:
            ans[i] = j
            ce += j in graph[prev]
            prev = j
            break


    avail.remove(prev)
    order.remove(prev)
    for x in graph[prev]:
        graph[x].remove(prev)

print(" ".join(map(lambda x: str(x+1),ans)))

#!/usr/bin/python3

# rewritten version of victor.cpp using chatgpt
from heapq import heappop, heappush
from collections import defaultdict

def min_item_0_to_get_item_n_minus_1():
    # Read N and M
    n, m = map(int, input().split())
    
    # Input structures
    trades = []  # List of (result_item, remaining_terms)
    trades_cost = [0] * m  # Tracks the cumulative cost of each trade
    items = defaultdict(list)  # Maps items to a list of (coefficient, trade_id)
    
    # Read trades
    for trade_id in range(m):
        res, k = map(int, input().split())
        trades.append([res, k])  # Store result item and remaining terms
        for _ in range(k):
            coef, item = map(int, input().split())
            items[item].append((coef, trade_id))  # Track which trades this item contributes to
    
    # Distance array and priority queue
    vis = [0] * n
    pq = [(1, 0)]  # (distance, item)
    
    while pq:
        d, item = heappop(pq)
        
        if item == n - 1:
            return d
        
        if vis[item]:
            continue
        vis[item] = True
        
        for coef, trade_id in items[item]:
            trades[trade_id][1] -= 1  # Decrease the number of remaining terms for this trade
            trades_cost[trade_id] += coef * d  # Add the cost of this term to the trade's total cost
            
            if trades[trade_id][1] == 0:  # If the trade is now complete
                result_item = trades[trade_id][0]
                heappush(pq, (trades_cost[trade_id], result_item))

print(min_item_0_to_get_item_n_minus_1())

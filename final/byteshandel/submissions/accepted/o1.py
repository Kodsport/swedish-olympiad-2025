#!/usr/bin/python3
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
    dists = [float('inf')] * n
    dists[0] = 1
    pq = [(1, 0)]  # (distance, item)
    
    # Dijkstra's algorithm
    while pq:
        d, item = heappop(pq)
        
        if item == n - 1:
            return d  # Found the minimum cost to reach item n-1
        
        if d > dists[item]:
            continue
        
        for coef, trade_id in items[item]:
            trades[trade_id][1] -= 1  # Decrease the number of remaining terms for this trade
            trades_cost[trade_id] += coef * d  # Add the cost of this term to the trade's total cost
            
            if trades[trade_id][1] == 0:  # If the trade is now complete
                result_item = trades[trade_id][0]
                if trades_cost[trade_id] < dists[result_item]:
                    dists[result_item] = trades_cost[trade_id]
                    heappush(pq, (dists[result_item], result_item))
    
    return dists[n - 1]  # Minimum cost to reach item n-1

print(min_item_0_to_get_item_n_minus_1())

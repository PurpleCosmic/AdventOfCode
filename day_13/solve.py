import re

memo_dict = dict()
def _get_cost(prize, A, B, x, y, current_cost, A_presses, B_presses):
    if (A_presses, B_presses) in memo_dict:
        return memo_dict[(A_presses, B_presses)]
    if (x, y) == prize:
        res = current_cost
    elif x > prize[0] or y > prize[1]:
        res = float('inf')
    else:
        res = min(
            _get_cost(prize, A, B, x+A[0], y+A[1], current_cost+3, A_presses+1, B_presses  ),
            _get_cost(prize, A, B, x+B[0], y+B[1], current_cost+1, A_presses,   B_presses+1)
        )
    memo_dict[(A_presses, B_presses)] = res
    return res

from collections import deque

def get_cost_iterative(prize, A, B):
    visited = dict()
    queue = deque()
    queue.append((0, 0, 0, 0, 0))

    while queue:
        x, y, cost, a_presses, b_presses = queue.popleft()

        if (x, y) in visited and visited[(x, y)] <= cost:
            continue
        visited[(x, y)] = cost

        if (x, y) == prize:
            continue

        if x + A[0] <= prize[0] and y + A[1] <= prize[1]:
            queue.append((x + A[0], y + A[1], cost + 3, a_presses + 1, b_presses))
        if x + B[0] <= prize[0] and y + B[1] <= prize[1]:
            queue.append((x + B[0], y + B[1], cost + 1, a_presses, b_presses + 1))

    return visited.get(prize, float('inf'))

def get_cost(prize, A, B):
    global memo_dict
    memo_dict = dict()
    return _get_cost(prize, A, B, 0, 0, 0, 0, 0)

def read_machines_from_file(filename):
    machines = []
    machine = dict()
    with open(filename, 'r') as file:
        for line in file:
            m = re.search('X.([0-9]+), Y.([0-9]+)', line)
            if m:
                coord = (int(m.group(1)), int(m.group(2)))
                if 'Button A' in line:
                    machine['A'] = coord
                if 'Button B' in line:
                    machine['B'] = coord
                if 'Prize' in line:
                    machine['Prize'] = (coord[0] + 10000000000000, coord[1] + 10000000000000)
            else:
                machines.append(machine)
                machine = dict()
    if machine:
        machines.append(machine)
    return machines

        
if __name__ == '__main__':
    machines = read_machines_from_file('ex.txt')
    res = 0
    for machine in machines:
        cost = get_cost(machine['Prize'], machine['A'], machine['B'])
        if cost < float('inf'):
            print(cost)
            res += cost
    print(res)


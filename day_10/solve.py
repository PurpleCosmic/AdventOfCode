class Grid():
    def __init__(self, columns: int, rows: int, default='.'):
        self.grid = [ [default] * columns for _ in range(rows) ]
        self.rows = rows
        self.columns = columns
    
    def insert(self, element, x, y):
        if self.is_in_bounds(x, y):
            self.grid[y][x] = element
            return True
        else:
            return False
    
    def get(self, x, y):
        if self.is_in_bounds(x, y):
            return self.grid[y][x]
        else:
            return None

    def is_in_bounds(self, x, y):
        return x >= 0 and y >= 0 and y < self.rows and x < self.columns

    def __str__(self):
        return '\n'.join([''.join(row) for row in self.grid])

def file_to_grid(filename):
    characters = 0
    rows = 0
    elements = []
    with open(filename, 'r') as file:
        for y, line in enumerate(file):
            line = line.strip()
            for x, char in enumerate(line):
                elements.append((char, x, y))
                characters += 1
            rows += 1
    
    columns = characters // rows
    g = Grid(columns, rows, '.')

    for char, x, y in elements:
        g.insert(char, x, y)

    return g

def possible_options(num):
    return [str(int(num) + 1)]

def get_reachable_nines(grid: Grid, x, y):
    res = set()
    if grid.get(x, y) == '9':
        res.add((x, y))
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        xp, yp = x + dx, y + dy
        if grid.is_in_bounds(xp, yp) and grid.get(xp, yp) in possible_options(grid.get(x, y)):
            for coord in get_reachable_nines(grid, xp, yp):
                res.add(coord)
    return res 


if __name__ == '__main__':
    g = file_to_grid('ex6.txt')
    columns = g.columns
    rows = g.rows

    res = 0
    for y, row in enumerate(g.grid):
        for x, el in enumerate(row):
            if el == '0':
                score = len(get_reachable_nines(g, x, y))
                print(score)
                res += score

    print(res)
    


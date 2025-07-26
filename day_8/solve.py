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
    antennae = []
    with open(filename, 'r') as file:
        for y, line in enumerate(file):
            line = line.strip()
            for x, char in enumerate(line):
                if char != '.':
                    antennae.append((char, x, y))
                characters += 1
            rows += 1
    
    columns = characters // rows
    g = Grid(columns, rows, '.')

    for char, x, y in antennae:
        g.insert(char, x, y)

    return g



if __name__ == '__main__':
    g = file_to_grid('chal.txt')
    columns = g.columns
    rows = g.rows
    freq_grid = Grid(columns, rows)

    for x in range(columns):
        for y in range(rows):
            if g.get(x, y) != '.':
                for xp in range(columns):
                    for yp in range(rows):
                        if g.get(xp, yp) == g.get(x, y) and xp != x and yp != y:
                            dist = (x - xp, y-yp)
                            print(dist)
                            mult = 0
                            while freq_grid.insert('#', x + dist[0] * mult, y + dist[1] * mult):
                                mult += 1

    print(g)
    print()
    print(freq_grid)
    print()

    res = 0
    for x in range(columns):
        for y in range(rows):
            if freq_grid.get(x, y) == '#':
                res += 1
                g.insert('#', x, y)
    print(g)
    print(res)




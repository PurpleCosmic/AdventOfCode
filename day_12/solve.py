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

def _get_region(grid, region, coord):
    x, y = coord
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        xp, yp = x + dx, y + dy
        if grid.get(xp, yp) == grid.get(x, y):
            if (xp, yp) not in region:
                region.add((xp, yp))
                _get_region(grid, region, (xp, yp))

def get_region(grid, start_coord):
    s = {start_coord}
    _get_region(grid, s, start_coord)
    return s

def get_area(region):
    return len(region)

def get_perimeter(region):
    res = 0
    for x, y in region:
        empty_sides = 4
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            if (x+dx, y+dy) in region:
                empty_sides -= 1
        res += empty_sides
    return res

def get_corner_count(region):
    corners = set()
    for x, y in region:
        if (x+1, y) in region and (x, y-1) in region and (x+1, y-1) not in region:
            corners.add((x+1+0.1, y-1+0.1))
        if (x+1, y) in region and (x, y+1) in region and (x+1, y+1) not in region:
            corners.add((x+1+0.4, y+1+0.4))
        if (x-1, y) in region and (x, y+1) in region and (x-1, y+1) not in region:
            corners.add((x-1+0.3, y+1+0.3))
        if (x-1, y) in region and (x, y-1) in region and (x-1, y-1) not in region:
            corners.add((x-1+0.2, y-1+0.2))

        if (x+1, y) not in region and (x, y-1) not in region:
            corners.add((x+1+0.1, y-1+0.1))
        if (x-1, y) not in region and (x, y-1) not in region:
            corners.add((x-1+0.2, y-1+0.2))
        if (x-1, y) not in region and (x, y+1) not in region:
            corners.add((x-1+0.3, y+1+0.3))
        if (x+1, y) not in region and (x, y+1) not in region:
            corners.add((x+1+0.4, y+1+0.4))
    return len(corners)

if __name__ == '__main__':
    grid = file_to_grid('chal.txt')
    regions_l = []
    for y in range(grid.rows):
        for x in range(grid.columns):
            el = grid.get(x, y)
            regions_l.append(get_region(grid, (x, y)))
    regions = []
    for region in regions_l:
        if region not in regions:
            regions.append(region)


    res = 0
    for region in regions:
        res += get_corner_count(region) * get_area(region)
    print(res)


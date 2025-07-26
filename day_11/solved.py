memo_dict = dict()

class Multiset():
    def __init__(self) -> None:
        self.dict = dict()

    def add(self, element):
        if element in self.dict:
            self.dict[element] += 1
        else:
            self.dict[element] = 1
        return True

    def add_n(self, element, amount):
        if element in self.dict:
            self.dict[element] += amount
        else:
            self.dict[element] = amount
        return True

    def remove(self, element):
        if element in self.dict:
            self.dict[element] -= 1
            if self.dict[element] == 0:
                del self.dict[element]
            return True
        else:
            return False

    def remove_n(self, element, amount):
        if element in self.dict:
            self.dict[element] -= amount
            if self.dict[element] <= 0:
                del self.dict[element]
            return True
        else:
            return False

    def __iter__(self):
        return self.dict.__iter__()

    def __getitem__(self, key):
        return self.dict.__getitem__(key)

def get_next_stones(stone):
    if stone == '0':
        return ['1']
    elif len(stone) % 2 == 0:
        return [stone[:len(stone) // 2], str(int(stone[len(stone)//2:]))]
    else:
        return str(int(stone) * 2024)
    

def blink(stones):
    res = Multiset()
    for stone in stones:
        amount = stones[stone]
        if stone == '0':
            res.add_n('1', amount)
        elif len(stone) % 2 == 0:
            res.add_n(stone[:len(stone)//2], amount)
            res.add_n(str(int(stone[len(stone)//2:])), amount)
        else:
            res.add_n(str(int(stone) * 2024), amount)
    return res

init_stones = ['27', '10647', '103', '9', '0', '5524', '4594227', '902936']

stones = Multiset()
for stone in init_stones:
    stones.add(stone)

for i in range(75):
    stones = blink(stones)


count = 0
for k in stones:
    count += stones[k]

print(f'Total stones: {count}')

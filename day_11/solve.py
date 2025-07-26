memo_dict = dict()

def blink(stones):
    res = []
    for stone in stones:
        if stone == '0':
            res.append('1')
        elif len(stone) % 2 == 0:
            res.append(stone[:len(stone)//2])
            res.append(str(int(stone[len(stone)//2:])))
        else:
            res.append(str(int(stone) * 2024))
    return res

def memoized_blink_priv(stones, init_amount, amount):
    if amount == 0:
        return stones
    res = []
    for i, stone in enumerate(stones):
        if init_amount == amount:
            print(i)
        if stone in memo_dict:
            jumpahead_amount = min(len(memo_dict[stone]), amount)
            stone_result = memo_dict[stone][jumpahead_amount-1]
            for stone in memoized_blink_priv(stone_result, init_amount, amount - jumpahead_amount):
                res.append(stone)
        else:
            stone_result = [stone]
            memo_dict[stone] = []
            iters = min(20, amount)
            for i in range(iters):
                stone_result = blink(stone_result)
                memo_dict[stone].append(stone_result)

            for stone in memoized_blink_priv(stone_result, init_amount, amount-iters):
                res.append(stone)
    return res

def memoized_blink(stones, amount):
    return memoized_blink_priv(stones, amount, amount)

stones = ['27', '10647', '103', '9', '0', '5524', '4594227', '902936']
stones = memoized_blink(stones, 40)

print(f'Total stones: {len(stones)}')

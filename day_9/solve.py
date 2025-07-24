def convert_diskmap_to_filesystem(diskmap):
    res = []
    for i, char in enumerate(diskmap):
        if i % 2 == 0:
            id = i // 2 
            [res.append(str(id)) for _ in range(int(char))]
        else:
            [res.append('.') for _ in range(int(char))]
    return res

def compact_filesystem(filesystem):
    res = list(filesystem)
    sys_len = len(filesystem)
    last_dot_pos = 0
    for i in range(sys_len-1, 0, -1):
        if res[i] != '.':
            for j in range(last_dot_pos, i):
                if res[j] == '.':
                    last_dot_pos = j
                    res[i], res[j] = res[j], res[i]
                    break
    return res

def calc_checksum(compacted_filesystem):
    res = 0
    for i, char in enumerate(compacted_filesystem):
        if char != '.':
            res += i * int(char)
    return res

if __name__ == '__main__':
    file = open('ex.txt', 'r')
    diskmap = file.read().strip()
    file.close()

    print(diskmap)
    filesystem = convert_diskmap_to_filesystem(diskmap)
    print(filesystem)
    compacted_filesystem = compact_filesystem(filesystem)
    print(''.join(compacted_filesystem))

    checksum = calc_checksum(compacted_filesystem)
    print(checksum)


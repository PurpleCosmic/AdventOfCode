def convert_diskmap_to_filesystem(diskmap):
    res = []
    for i, char in enumerate(diskmap):
        if i % 2 == 0:
            id = i // 2 
            res.append([str(id) for _ in range(int(char))])
        else:
            [res.append('.') for _ in range(int(char))]
    return res

def compact_filesystem(filesystem):
    res = list(filesystem)
    sys_len = len(filesystem)
    for i in range(sys_len-1, 0, -1):
        if res[i] != '.':
            filesize = len(res[i])
            free_space = 0
            for j in range(i):
                if res[j] == '.':
                    free_space += 1
                else:
                    free_space = 0

                if free_space >= filesize:
                    free_space_start_index = j - free_space + 1
                    res[free_space_start_index] = res[i]
                    res[i] = '.'
                    for _ in range(1, filesize):
                        res.insert(i, '.')

                    for ii in range(0, free_space-1):
                        del res[j - ii]
                    break
    return res

def flatten(l):
    res = []
    for el in l:
        if isinstance(el, list):
            ll = flatten(el)
            for elel in ll:
                res.append(elel)
        else:
            res.append(el)
    return res

def calc_checksum(compacted_filesystem):
    res = 0
    for i, char in enumerate(compacted_filesystem):
        if char != '.':
            res += i * int(char)
    return res

if __name__ == '__main__':
    file = open('chal.txt', 'r')
    diskmap = file.read().strip()
    file.close()

    print(diskmap)
    filesystem = convert_diskmap_to_filesystem(diskmap)
    print(filesystem)
    compacted_filesystem = compact_filesystem(filesystem)

    cmp_fs_flat = flatten(compacted_filesystem)
    print(''.join(cmp_fs_flat))

    checksum = calc_checksum(cmp_fs_flat)
    print(checksum)


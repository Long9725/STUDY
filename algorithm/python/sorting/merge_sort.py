def mergeSort(l):
    if len(l) < 2:
        return l
    mid=len(l) // 2
    left = mergeSort(l[:mid])
    right = mergeSort(l[mid:])
    return merge(left, right)

l = [38, 27, 43, 3, 9, 82, 10]
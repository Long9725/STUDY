# if n = 1, done
# Recursively sort A[1 ... n/2] and A[n/2+1 ... n].
# Merge the 2 sorted lists

def mergeSort(l):
    if len(l) < 2:
        return l
    mid=len(l) // 2
    left = mergeSort(l[:mid])
    right = mergeSort(l[mid:])
    return merge(left, right)

l = [38, 27, 43, 3, 9, 82, 10]
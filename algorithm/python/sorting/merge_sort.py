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

def merge(left, right):
    i = 0
    j = 0
    sorted_list = []

    while(i < len(left)) & (j < len(right)):
        if left[i] < right[j]:
            sorted_list.append(left[i])
            i += 1
        else:
            sorted_list.append(right[j])
            j += 1
    
    while (i < len(left)):
        sorted_list.append(left[i])
        i += 1

    while (j < len(right)):
        sorted_list.append(right[j])
        j += 1
    
    return sorted_list
# import 하려면 main 함수를 주석처리
# import insertion_sort.py
def main():
    print("merge_sort")
    l = [38, 27, 43, 3, 9, 82, 10]
    l = mergeSort(l)
    print(l)

if __name__ == "__main__":
    main()
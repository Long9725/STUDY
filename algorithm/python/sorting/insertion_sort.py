def insertion_sort(arr):
    for end in range(1, len(arr)):
        to_insert = arr[end]
        i = end
        while i > 0 and arr[i-1] > to_insert:
            arr[i] = arr[i-1]
            i -= 1
        arr[i] = to_insert

# import 하려면 main 함수를 주석처리
# import insertion_sort.py
def main():
    print("insertion_sort")
    arr = [1, 4, 6, 3, 12]
    insertion_sort(arr)
    print(arr)

if __name__ == "__main__":
    main()


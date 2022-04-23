# 목표
> + Insertion sort algorithm을 이해한다.
> + Insertion sort algorithm을 구현할 수 있다.
> + Insertion sort algorithm을 라인 별로 수행시간을 분석할 수 있다.
> + Insertion sort algorithm의 best, worst case를 분석할 수 있다.
> + Insertion sort algorithm의 runtime을 계산할 수 있다.
> + Insertion sort algorithm의 시간복잡도를 계산할 수 있다.

---

## 목차

1. [Insertion sort algorithm](#insertion-sort-algorithm)
2. [Pseudocode](#pseudocode)
3. [Loop invariant](#loop-invariant)
4. [Time complexity](#time-complexity)
5. [Reference](#references)

---

## Insertion sort algorithm
+ 손 안의 카드를 정렬하는 방법과 비슷하다.
    1. 오른손에는 정리되지 않은 카드가 있다.
    2. 왼손으로 카드를 한 장 보낸다.
    3. 왼손에 있는 카드의 순서를 정렬한다.
    4. 오른손에 카드가 남지 않을 때까지 반복한다.
+ 삽입 정렬의 Key 값은 두 번째 자료부터 시작한다. (첫 번째 자료는 다른 자료들이 없기 때문에 이미 정렬된 상태로 간주한다.)
+ 삽입 정렬의 Key에 해당하는 자료는 앞(배열 상 왼쪽)의 자료들과 비교하여 삽입할 위치를 찾는다.
+ 삽입할 위치를 찾은 자료는 다른 자료를 한 칸씩 뒤로 이동시킨다.
+ 이렇게 정렬되고 나면 각 사이클마다 Key 값 기준 앞(왼쪽)에 있는 자료들은 정렬이 되어있다. 

## Pseudocode
pseudocode: 의사코드, 프로그램을 작성할 때 각 모듈이 작동하는 논리를 표현하기 위한 언어

    INSERTION-SORT(A, n)
        for j <- 2 to n // 두번째 자료부터 시작한다.
            do key <- A[j] // j번째 자료는 키가 된다.
                i <- j-1 
                while i > 0 and A[i] > key // 키 값보다 크면 뒤로 한 칸 미룬다.
                    do A[i+1] <- A[i]
                        i <- i - 1
                A[i+1] = key
                
## Loop invariant
0부터 index-1의 원소들은 입력 배열에서 0부터 index-1까지 있던 원소들이고 모두 정렬되어 있다.
pseudocode에서 index의 범위는 1 to n이다. Array의 index 범위는 0 to n-1 이므로 주의바람.

### 1. Initialization
Loop를 시작하려는 시점에 loop invariant가 참인지를 증명한다.

    for j <- 2 to n <-- for문을 시작하려는 시점

1. j = 2(index로는 1)일 때, j = 1(index로는 0)이다.
2. A의 첫번째 원소는 입력 배열의 첫번째에 위치한 원소이다.
3. 원소가 하나이므로 정렬되어 있다.
4. 따라서 for-loop를 시작하기 전에 loop invariant는 참이다.

### 2. Maintenance
Loop를 반복하기 전 loop invariant가 참이라면, 다음 Loop 후 loop invariant도 참이다.

    while i > 0 and A[i] > key
                    do A[i+1] <- A[i]
                        i <- i - 1
                A[i+1] = key
                
1. while-loop에서 A[i]의 삽입 위치를 찾기 위해 A[i-1], A[i-2], A[i-3], ... 순으로 오른쪽 shift한다.
2. 찾은 위치에 A[i]를 삽입한다.
3. 1 to i까지의 원소들은 입력 배열의 1 to i에 있던 원소들이며 정렬되어 있다.
4. 따라서 1회 반복 후, Loop invariant는 참이다.

### 3. Termination
Loop가 종료 되었을 때, loop invariant가 참이다.

    for j <- 2 to n

1. for-loop의 j 값이 n(=A의 길이)이 되면 loop를 종료한다.
2. 1 to n까지의 원소들은 원래 입력배열의 1 to n까지 있던 원소들이고 모두 정렬되어 있다.
3. n 대신 length을 넣어보면 1부터 length까지 모두 정렬되어있다.
4. loop 수행 후, loop invariant는 참이다.
5. 따라서 해당 알고리즘은 Correct하다.

## Property
+ 장점
    + 구현이 간단하다
    + 안정적인 정렬이다

+ 단점
    + 배열이 길어질수록 효율이 떨어진다
    + 레코드들의 많은 이동을 포함하는 편이다.

## Time complexity
추후 분석
+ Best case
    + 정렬하려는 순서에 맞게 이미 정렬된 배열
    + Best T(n) = O(n)

+ Worst case
    + 정렬하려는 순서와 정반대로 정렬된 배열
    + Worst T(n) = O(n^2)

## References
> + Insertion sort: https://gmlwjd9405.github.io/2018/05/06/algorithm-insertion-sort.html
> + Wiki: https://ko.wikipedia.org/wiki/%EC%82%BD%EC%9E%85_%EC%A0%95%EB%A0%AC
> + Insertion sort loop invariant: https://jehogu.tistory.com/entry/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EC%A6%9D%EB%AA%85%EB%B2%95-Loop-Invariant
## 목차

1. [Knapsack problem](#knapsack-problem)
2. [Naive approach](#naive-approach)
3. [Optimal substructure](#optimal-substructure)
4. [Recurrence](#recurrence)
5. [Pseudocode](#pseudocode)
6. [Table](#table)
7. [Performance](#performance)
8. [References](#references)

---

## Knapsack problem
담을 수 있는 무게가 정해진 배낭이 있다. 일정 가치와 무게가 있는 짐들을 배낭에 넣을 때, 가치의 합이 최대가 되도록 짐을 고르는 방법을 찾는 문제이다.

+ Item(짐) i는 무게 w<sub>i</sub> > 0과 가치 v<sub>i</sub> > 0이다.
+ Knapsack(배낭)은 W만큼의 무게를 수용할 수 있다.
+ W와 w는 단위가 같다.

## Naive approach
+ n 개의 아이템에 대해서 2<sup>n</sup>-1 개의 조합이 있다.
+ Max 값을 비교하기 위해서 모든 조합을 한 번씩 비교해야하므로 θ(n)이 걸린다.
+ 시간 복잡도는 θ(n2<sup>n</sup>)이다.

## Optimal substructure
OPT(i, w)는 무게 제한 W에 가까운 w를 가지는 subset 1, ..., i의 최대 가치라고 정의한다.

+ Case 1: OPT는 item i를 고르지 않는다.
    + OPT는 <1, 2, ..., i-1>이 최대 가치이다. 이 때, 무게 제한은 w이다.

+ Case 2: OPT는 item i를 고른다.
    + OPT는 <1, 2, ..., i-1>이 최대 가치이다. 이 때, 무게 제한은 w - w<sub>i</sub>이다.

## Recurrence
+ Base case는 OPW(0, w) = 0이다. (0 <= w <= W)
+ Recursive step은 다음과 같다.
    + 현재 아이템의 무게가 무게 제한을 넘겼을 경우(w<sub>i</sub> > w)라면 OPT(i, w) = OPT(i-1, w)이다.
    + 현재 아이템의 무게가 무게 제한을 넘기지 않았을 경우, OPT(i, w) = max(OPT(i-1, w), v<sub>i</sub> + OPT(i-1, w-w<sub>i</sub>))이다. (1 <= i <= n, 1 <= w <= W)

![](../../image/dynamic_programming/knapsack_problem/knapsack%20recurrence.png)

## Pseudocode
![](../../image/dynamic_programming/knapsack_problem/fill%20up%20table%20pseudocode.png)

## Table
OPT(i, w)에 대해서 경로는 다음과 같이 유추한다.
+ OPT table(i, w)의 값과 OPT table(i-1, w)의 값이 같다면 경로는 OPT table(i, w) -> OPT table(i-1, w)이다. (위로 한 칸 이동)
+ OPT table(i, w)의 값과 OPT table(i-1, w)의 값이 다르다면, OPT table의 (i-1)번째 행에서 OPT(i, w) - Item table(i, value)인 값을 찾는다. 그 곳으로 이동한다. 

### OPT table
![](../../image/dynamic_programming/knapsack_problem/table%201.png)

### Item table
![](../../image/dynamic_programming/knapsack_problem/table%202.png)


## Performance
### Time complexity
+ OPT table를 만드는데 θ(nW)가 필요하다.
+ OPT 경로를 출력하는데 θ(n)이 걸린다.

=> 시간복잡도는 θ(nW)이다.

### Space complexity
OPT table를 만드는데 θ(nW)가 필요하다.

## References
> + 2022 봄 알고리즘 수업
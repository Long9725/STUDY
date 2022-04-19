## 목차

1. [Dynamic programming](#dynamic-programming)
2. [Divide and conquer & dynamic programming 비교](#divide-and-conquer--dynamic-programming-비교)
3. [References](#references)

---

## Dynamic programming
작은 문제들의 해결 방법을 합쳐 기존 문제를 해결하는 방법이다. Bottom-up approach이다. 가장 작고, 간단한 문제부터 해결한다. 해결된 문제의 결과값을 표에 저장하고, 이 값을 활용해 다음 문제를 해결한다. 보통 최소값, 최대값 등 가장 최적화된 값을 찾는 문제에 사용한다. (Greedy는 항상 최적화된 값은 아니다.) \
만약 문제를 해결하는 과정에서 분할-정복 알고리즘이 많은 중복을 발생시킨다면, DP를 활용하는 것이 더 효율적이다.

1. 최적화된 해결책(optimal solution)의 구조(structure of an optimal solution)를 정한다. 문제가 이러한 해결책의 하위구조(optimal substructure)임을 보인다. 
    + 문제가 Optimal substructure이라는 것은 optimal solution이 하위 문제(subproblems)의 optimal solutions를 포함하고 있다는 것을 의미한다. 
    + 하위 문제의 해결책으로부터 기존 문제의 해결책을 얻을 수 있도록 구성한다.
2. 재귀함수를 통해 최적화된 값을 정한다.
3. 이전 단계에서 최적화한 값들 중, 가장 최적의 값을 계산한다. 표를 사용한다.
4. 이 값으로부터 최적의 해결책을 정한다.

### Divide and conquer & dynamic programming 비교
+ 분할 정복은 기존 문제를 "독립적인" 작은 문제로 나눠서 해결한다.
+ DP는 기존 문제를 "겹치는" 작은 문제로 나눠서 해결한다.

=> DNA 염기서열 2개의 유사성을 파악하는 문제, 이항 정리 등
 
### Greedy algorithm & dynamic programming 비교
문제를 해결하는 방법에 대해 선택권이 주어질 때, 고르는 방법이 다르다.

+ Greedy는 현재 주어진 선택 중에서 최적의 선택을 고른다
+ DP는 현재 주어진 선택들에 대해서 하나 하나 고려한다.

## Key ingredients
해결하고자 하는 문제가 최적화를 해야하며, 다음 특성을 가지면 DP를 활용한다.

+ Optimal substructure
    + Optimal solution은 optimal substructure으로부터 얻어진다.
+ Overlapping problems

### Optimal substructure
1. 문제를 해결하는 방법에 대해 선택권이 주어진다. 그 문제가 어떻게 해결되는지, 선택을 하고 나면 무슨 일이 생기는지 등은 고려하지 않는다. 
2. Subproblems의 범위를 결정한다.
3. Subproblems의 solutions이 항상 최적인지 증명한다. 'cut-and-paste' 기법을 사용한다.

## Cut-and-paste
Optimal substructure이 최적인지 증명하는 방법이다.
1. Subproblem solution이 최적이 아니라고 가정한다.
    + 다른 Optimal solution이 있을 것이다.
2. 최적이 아닌 subproblem solution을 cut하고 Optimal subproblem solutions을 붙인다. 그렇다면 원래 문제에 대한 더 나은 해결 방법이 있다.
3. 하지만 contradiction이 발생한다.

<details><summary>LCS</summary>

### LCS 
Z = < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>k</sub>>가 X, Y의 LCS(Optimal solution)라고 하자.

1. x<sub>m</sub> = y<sub>n</sub>이라면 z<sub>k</sub> = x<sub>m</sub> = y<sub>n</sub>이고, z<sub>k-1</sub>은 X<sub>m-1</sub>와 Y<sub>n-1</sub>의 LCS이다.
2. x<sub>m</sub> != y<sub>n</sub>이고 z<sub>k</sub> != x<sub>m</sub>이면 Z는 X<sub>m-1</sub>와 Y의 LCS이다.
3. x<sub>m</sub> != y<sub>n</sub>이고 z<sub>k</sub> != y<sub>n</sub>이면 Z는 X와 Y<sub>n-1</sub>의 LCS이다.

+ x<sub>m</sub> = y<sub>n</sub>이라면 z<sub>k</sub> = x<sub>m</sub> = y<sub>n</sub>이고,
    + (Cut) z<sub>k</sub> != x<sub>m</sub>이라고 가정하자. 
    + (Paste) LCS를 얻기 위해서 x<sub>m</sub> = y<sub>n</sub>이므로 둘 중 하나를 Z에 붙인다. 그러면 길이가 k+1인 X와 Y의 LCS가 생긴다.
    + (Contadiction) 하지만 Z는 < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>k</sub> >이라고 가정했으므로, 이에 모순이 생긴다. 따라서 Cut의 가정이 틀렸다.


 + z<sub>k-1</sub>은 X<sub>m-1</sub>와 Y<sub>n-1</sub>의 LCS이다.
    + (Cut) W를 길이가 k-1보다 큰 X<sub>m-1</sub>와 Y<sub>n-1</sub>의 LCS라고 가정한다.
    + (Paste) LCS를 얻기 위해서 x<sub>m</sub> = y<sub>n</sub>이므로 둘 중 하나를 W에 붙인다. 그러면 길이가 k+1보다 큰 X와 Y의 LCS가 생긴다.
    + (Contadiction) 하지만 Z는 < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>k</sub> >이라고 가정했으므로, LCS의 길이에 모순이 생긴다. 따라서 Cut의 가정이 틀렸다.    


+ x<sub>m</sub> != y<sub>n</sub>이고 z<sub>k</sub> != x<sub>m</sub>이면 Z는 X<sub>m-1</sub>와 Y의 LCS이다.
    + (Cut) Z는 X<sub>m-1</sub>와 Y의 LCS가 아니다.
    + (Paste) W는 길이가 k보다 긴 X<sub>m-1</sub>와 Y의 LCS이다. x<sub>m</sub> != y<sub>n</sub>이므로 W는 X<sub>m</sub>와 Y<sub>n</sub>의 LCS이 된다.
    + (Contadiction) 하지만 Z는 < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>k</sub> >이라고 가정했으므로, LCS의 길이에 모순이 생긴다. 따라서 Cut의 가정이 틀렸다.
    

+ x<sub>m</sub> != y<sub>n</sub>이고 z<sub>k</sub> != y<sub>n</sub>이면 Z는 X와 Y<sub>n-1</sub>의 LCS이다.
    + (Cut) Z는 X와 Y<sub>n-1</sub>의 LCS가 아니다.
    + (Paste) W는 길이가 k보다 긴 X와 Y<sub>n-1</sub>의 LCS이다. x<sub>m</sub> != y<sub>n</sub>이므로 W는 X<sub>m</sub>와 Y<sub>n</sub>의 LCS이 된다.
    + (Contadiction) 하지만 Z는 < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>k</sub> >이라고 가정했으므로, LCS의 길이에 모순이 생긴다. 따라서 Cut의 가정이 틀렸다.

</details>

## References
> + 2022 봄 알고리즘 수업
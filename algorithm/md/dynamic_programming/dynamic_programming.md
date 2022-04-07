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

## Divide and conquer & dynamic programming 비교
+ 분할 정복은 기존 문제를 "독립적인" 작은 문제로 나눠서 해결한다.
+ DP는 기존 문제를 "겹치는" 작은 문제로 나눠서 해결한다.

=> DNA 염기서열 2개의 유사성을 파악하는 문제, 
 
## References
> + 2022 봄 알고리즘 수업
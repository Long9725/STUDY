## 목차

1. [The longest common subsequence](#the-longest-common-subsequence)
2. [Definition](#definition)
3. [Problem](#problem)
4. [Naive approach](#naive-approach)
5. [Four-step method](#four-step-method)
6. [Pseudocode](#pseudocode)
7. [Performance](#performance)
8. [References](#references)

---

## The longest common subsequence
두 문자열의 유사성을 비교하는 문제이다.

## Definition
The longest common subsequence에서 사용될 용어들을 정의한다.

<details><summary> Terms </summary>

+ Subsequence

문자열 X = < x<sub>1</sub>, x<sub>2</sub>, ..., x<sub>m</sub> >에 대해서, Z = < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>n</sub>>는 X의 원소 순서가 유지되면서, 다음을 만족할 때 X의 subsequence라고 한다. \
Indices of X에 대한 오름차순 배열 I = < i<sub>1</sub>, i<sub>2</sub>, ... i<sub>k</sub>>라고 하자. I는 j = 1, 2, ..., k에 대하여 X<sub>i<sub>j</sub></sub> = Z<sub>j</sub>를 만족해야한다. 

Ex) X = < A, B, D, F, M, Q >, Z = < B, F, M >이라 하자. Z는 < 2, 4, 5 >라는 I를 가지는 X의 subsequence이다. 

+ Common subsequence

두 개의 문자열 X, Y가 주어진다. 문자열 Z가 X와 Y의 subsequence를 만족한다면 common subsequence라고 정의한다.

*Subsequence는 서로 연속될 필요가 없지만, substring은 연속되어야 한다.
Ex) X = 'abcde'라고 하자.
Z = 'bd'는 X의 subsequence이지만, substring은 아니다.
Z = 'abc'는 X의 subsequence면서 substring이다.

+ Prefix of a subsequence

문자열 X = < x<sub>1</sub>, x<sub>2</sub>, ..., x<sub>m</sub> >에 대해서, i = 0, 1, ..., m일 때 X의 i번째 prefix는 X = < x<sub>1</sub>, x<sub>2</sub>, ..., x<sub>i</sub> >이다.

Ex) X = < A, B, C, D, E, F, H, I, J, L > 일 때
+ X<sub>4</sub> = < A, B, C, D >
+ X<sub>2</sub> = < A, B >
+ X<sub>0</sub> = <>

</details>

## Problem
2개의 문자열 X = < x<sub>1</sub>, x<sub>2</sub>, ..., x<sub>m</sub> >, Y = < y<sub>1</sub>, y<sub>2</sub>, ..., y<sub>n</sub> >이 있다. 이 때 X와 Y의 the longest common subsequence를 찾아라. Subsequence는 연속일 필요는 없지만, 기존 문자열의 순서는 지켜야한다.

*The longest common subsequence는 여러 개일 수 있다. 길이도 같이 출력할 수 있다.
 
## Naive approach
시간복잡도는 θ(n2<sup>m</sup>)이다.

1. 문자열 X가 만들어낼 수 있는 모든 subsequence를 찾는다. 이 때 (2<sup>m</sup>-1)개의 subsequence가 생긴다.
2. 문자열 Y의 첫번째 문자부터 일치하는지 차근차근 찾아본다. 이 때 문자열 Y의 길이 n만큼 패턴매칭을 한다.

## Recursive approach
시간복잡도는 θ(2<sup>m+n</sup>)이다.

<details><summary> Four-step method </summary>

## Four-step method

### Optimal substructure
약자로 OPT라고 한다. \
Z = < z<sub>1</sub>, z<sub>2</sub>, ..., z<sub>k</sub>>가 X, Y의 LCS(Optimal solution)라고 하자.

+ x<sub>m</sub> = y<sub>n</sub>이라면 z<sub>k</sub> = x<sub>m</sub> = y<sub>n</sub>이고, z<sub>k-1</sub>은 X<sub>m-1</sub>와 Y<sub>n-1</sub>의 LCS이다.
+ x<sub>m</sub> != y<sub>n</sub>이고 z<sub>k</sub> != x<sub>m</sub>이면 Z는 X<sub>m-1</sub>와 Y의 LCS이다.
+ x<sub>m</sub> != y<sub>n</sub>이고 z<sub>k</sub> != y<sub>n</sub>이면 Z는 X와 Y<sub>n-1</sub>의 LCS이다.

x<sub>m</sub> != y<sub>n</sub>일 때, LCS(X<sub>m</sub>, Y<sub>n</sub>)는 LCS(X<sub>m-1</sub>, Y)와 LCS(X, Y<sub>n-1</sub>) 중 길이가 큰 것이다.

따라서 두 가지 케이스는 다음과 같은 subproblems를 해결해야한다.
1.  x<sub>m</sub> = y<sub>n</sub>이라면 LCS(X<sub>m-1</sub>, Y<sub>n-1</sub>)를 찾는다.
2. x<sub>m</sub> != y<sub>n</sub>이라면
    + LCS(X<sub>m-1</sub>, Y)를 찾는다.
    + LCS(X, Y<sub>n-1</sub>)를 찾는다.
    + 두 가지 중, 더 긴 LCS를 찾는다.

### Cost & Compute
Cost는 common subsequence의 길이(OPT)이다.  
+ c[i, j]는 LCS(X<sub>i</sub>, Y<sub>j</sub>)의 길이이다.
+ Base case는 c[i, j] = 0인 empty subsequence이다. i = 0 또는 j = 0이다.

![](../../image/dynamic_programming/LCS/recurrence%20for%20LCS.png)

다음과 같은 표를 만들며 OPT를 Compute한다.

![](../../image/dynamic_programming/LCS/compute%20cost.png)


</details>

## Pseudocode
+ 화살표의 끝은 이전 단계 subsequence의 OPT, 시작은 현재 단계의 subsequence의 OPT이다. 
+ Table c는 OPT를 저장한다.
+ Table b는 OPT가 도출되는 방향의 포인터를 저장한다.
+ Print는 X이든 Y이든 상관없다. X와 Y에 공통으로 들어가있는 원소를 출력하기 때문이다.

![](../../image/dynamic_programming/LCS/LCS%20pseudocode.png)
![](../../image/dynamic_programming/LCS/LCS%20print%20pseudocode.png)

## Performance
### Time complexity
+ Table b와 c를 계산하는데 θ(mn)이 걸린다.
+ LCS를 출력하는데 θ(n)이 걸린다.

### Space complexity
Table b와 c를 만드는데 θ(mn)이 필요하다.

## References
> + 2022 봄 알고리즘 수업
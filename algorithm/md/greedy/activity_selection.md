## 목차

1. [Activity selection](#activity-selection)
2. [Optimal substructure](#optimal-substructure)
3. [DP](#DP)
4. [Greedy choice](#greedy-choice)
5. [References](#references)

---

## Activity selection
N 개의 활동이 공통 자원을 초과한 사용을 요구하는 문제이다. 예를 들어 여러 개의 대학 강의가 한 개의 교실을 사용하려 할 때, 이를 스케쥴링 하는 문제가 있다.

+ Problem: 각 활동의 시작 시간과 종료 시간이 주어진다. 이를 스케쥴링 한다.
+ Goal: 활동 간 시간이 겹치지 않도록 하면서 가장 많은 활동이 가능하도록 하는 집합을 구한다.

### 가정
+ 활동들의 집합 S = < a<sub>1</sub>, a<sub>2</sub>, ..., a<sub>n</sub> >이라고 가정한다.
+ 한 번에 하나의 활동만 가능하다.
+ 각 액티비티 a<sub>i</sub>는 시작 시간 s<sub>i</sub>과 끝나는 시간 f<sub>i</sub>를 가진다. (0 <= s<sub>i</sub> <= f<sub>i</sub> <= ∞)
+ 각 액티비티 a<sub>i</sub>는 [s<sub>i</sub>, f<sub>i</sub>)를 필요로 한다.
+ 액티비티 a<sub>i</sub>와 a<sub>j</sub>에 대하여 [s<sub>i</sub>, f<sub>i</sub>)와 [s<sub>j</sub>, f<sub>j</sub>)가 겹치지 않을 경우, compatible하다고 한다.

+ 시작 시간과 끝나는 시간은 배열 s와 f에 저장되어 있다.
+ 모든 활동은 끝나는 시간 기준 오름차순으로 정렬되어 있다. 따라서 s는 오름차순이 아닐 수 있다.

## Optimal substructure
OPT가 subproblems의 OPT으로부터 얻어지는지 확인한다.

+ S<sub>ij</sub> = { a<sub>k</sub> ∈ S | f<sub>i</sub> <= s<sub>k</sub> <= f<sub>k</sub> <= s<sub>j</sub> }으로 정의한다. (0 <= i <= j <= n+1) a<sub>i</sub>가 끝나는 시간 이후, a<sub>j</sub>가 시작하는 시간 전에 있는 활동들의 집합이다.
    + a<sub>0</sub>와 a<sub>n+1</sub>에 대하여 f<sub>0</sub> = 0, s<sub>n+1</sub> = ∞이라고 가정한다.
    + S의 범위 바깥에 있는 활동들과 S는 compatible하다. 
+ S<sub>ij</sub>는 a<sub>k</sub>를 포함한다고 가정한다. 2가지 subproblems가 생긴다
    + S<sub>ik</sub> (a<sub>i</sub>가 끝나고, a<sub>k</sub>가 시작하기 전)
    + S<sub>kj</sub> (a<sub>k</sub>가 끝나고, a<sub>j</sub>가 시작하기 전)
+ S<sub>ij</sub>의 solution은 (solution to S<sub>ik</sub>) U { a<sub>k</sub> } U (solution to S<sub>kj</sub>)이다. 

이러한 OPT가 실제로인지 optimal인지 S<sub>ik</sub>와 S<sub>kj</sub>에 대하여 증명한다.

1. A<sub>ij</sub>는 S<sub>ij</sub>의 optimal solution이라고 가정한다.
2. A<sub>ij</sub> = A<sub>ik</sub> U { a<sub>k</sub> } U A<sub>kj</sub>이다. 
    + S<sub>ij</sub>는 공집합이 아니다.
3. A<sub>ik</sub>가 S<sub>ik</sub>의 optimal solution이 아니다.
    + (Cut) A'<sub>ik</sub>는 S<sub>ik</sub>의 optimal solution이라고 하자. A'<sub>ik</sub>는 A<sub>ik</sub>보다 더 많은 활동을 골라야 하므로, 개수가 더 많다. |A'<sub>ik</sub>| > |A<sub>ik</sub>|
    + (Paste) 따라서 |A'<sub>ik</sub>| + 1 + |A<sub>kj</sub>| > |A<sub>ik</sub>| + 1 |A<sub>kj</sub>| = |A<sub>ij</sub>|이다. Optimal solution은 activity의 개수이기 때문에 이렇게 표현할 수 있다.
    + (Contradiction) 하지만 이러한 표현은 A<sub>ij</sub>의 개수보다 많아지므로 가정에 모순이 된다.
4. A<sub>kj</sub>가 S<sub>kj</sub>의 optimal solution이 아니다.
    + (Cut) A'<sub>kj</sub>는 S<sub>kj</sub>의 optimal solution이라고 하자. A'<sub>kj</sub>는 A<sub>kj</sub>보다 더 많은 활동을 골라야 하므로, 개수가 더 많다. |A'<sub>kj</sub>| > |A<sub>kj</sub>|
    + (Paste) 따라서 |A<sub>ik</sub>| + 1 + |A'<sub>kj</sub>| > |A<sub>ik</sub>| + 1 |A'<sub>kj</sub>| = |A<sub>ij</sub>|이다. Optimal solution은 activity의 개수이기 때문에 이렇게 표현할 수 있다.
    + (Contradiction) 하지만 이러한 표현은 A<sub>ij</sub>의 개수보다 많아지므로 가정에 모순이 된다.

## DP
c[i, j] = S<sub>ij</sub>의 optimal solution size라고 하자.
+ A<sub>ij</sub> = A<sub>ik</sub> + 1 A'<sub>kj</sub>
+ c[i, j] = c[i, k] + 1 + c[k, j]

![](../../image/greedy/activity_selection/activity%20selection%20dp.png)

## Greedy choice
가장 빨리 끝나는 활동을 고른다. 활동 시간이 짧을 수록 다른 활동을 고를 수 있는 기회가 많아진다. 
+ 배열 f에서 첫 번째 것을 고르면 된다는 이득도 생긴다. 
+ a<sub>1</sub>를 고르면 오른쪽 subproblems만 고려하면 된다.

S<sub>k</sub> = { a<sub>i</sub> ∈ S | s<sub>i</sub> >= f<sub>k</sub> }

### Proof
각 선택 a<sub>m</sub>이 optimal solution의 일부분인지 증명해야한다.

+ A<sub>k</sub>를 S<sub>k</sub>의 optimal solution이라고 가정한다.
+ a<sub>j</sub>는 A<sub>k</sub>에서 끝나는 시간이 가장 빠른 활동이다.
1. 만약 a<sub>j</sub> = a<sub>m</sub>이 같다면, a<sub>m</sub>는 S<sub>k</sub>의 완벽히 compatible한 활동이다.
2. 만약 a<sub>j</sub> != a<sub>m</sub>이 같다면, A'<sub>k</sub> = A<sub>k</sub> - { a<sub>j</sub> } U { a<sub>m</sub> }이라고 하자.
    + A<sub>k</sub>는 compatible하다.
    + A'<sub>k</sub>도 compatible하다.
    + f<sub>m</sub> <= f<sub>k</sub>
3. A'<sub>k</sub>는 disjoint이고, |A'<sub>k</sub>| = |A<sub>k</sub>| 이다. 따라서 A'<sub>k</sub>은 S<sub>k</sub>의 활동들 중 서로 시간이 겹치지 않는 활동들과 a<sub>m</sub>을 포함한 최대 크기 부분집합이다.
4. 따라서 A'<sub>k</sub>는 a<sub>m</sub>을 포함한 S<sub>k</sub>의 optimal solution이다.

## Simplifying the recursive solution
S<sub>k</sub> = { a<sub>i</sub> ∈ S | s<sub>i</sub> >= f<sub>k</sub> } 에 대하여 subproblems는 다음과 같은 패턴을 가진다.
1. Original problem: S = S<sub>0</sub>
2. S에 있는, 가장 빨리 활동이 종료되는 a<sub>m1</sub> 고른다. (f는 정렬되어 있으므로 m1 = 1이다.)
3. 다음 subproblem은 S<sub>m1</sub>이다.
4. S<sub>m1</sub>에 있는, 가장 빨리 활동이 종료되는 a<sub>m2</sub> 고른다. (m2 = 2는 아닐 수도 있다.)
5. 다음 subproblem은 S<sub>m2</sub>이다.

+ 각 subproblem의 형태는 a<sub>mi</sub>에 대하여 S<sub>mi</sub>이다.

## Recursive greedy algorithm

    REC-ACTIVITY-SELECTOR(s, f, k, n)
    
    m = k + 1
    while m <= n and s[m] < f[k]
        m = m + 1
    if m <= n
        return { a_m } U REC-ACTIVITY-SELECTOR(s, f, m, n)
    else return ∅    

## Performance
Θ(n)이 걸린다. 배열 f가 정렬되어 있다는 가정 하에, 각 활동은 정확히 한 번만 고려된다.

## References
> + 2022 봄 알고리즘 수업
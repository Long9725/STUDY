## 목차

1. [Synchronization이란?](#synchronization이란)
2. [Critical section](#critical-section)
3. [References](#references)

## Synchronization이란?
공유되는 자원에 대해서 접근 권한을 관리하는 기법이다. Concurrency를 추구하다보면, Threads에서 비결정론적 결과를 발생시키기 때문이다. Concurrency를 저해하기 때문에 성능적인 측면에 영향을 끼친다. 프로그래머가 컨트롤할 수 있는 것이 아니고, OS에서 컨트롤해야하기 때문에 어려운 기법이다.

+ 비결정론적: Non-determistic, 동일한 입력이 주어지더라도 매번 다른 과정을 거쳐 다른 결과를 낳는다. Threads끼리 Shared resource에 대해서 값이 맞지 않아 예상과는 다른 결과를 낳을 수 있다.


![](../image/synchronization/concurrecny%20in%20the%20kernel.png)

이처럼 다양한 Threads가 Kernel에 존재하고, 이들 사이에 Shared resource에 대해서 값을 맞춰줘야 하는 문제가 생긴다.
+ Race condition: 동시에 여러 개의 스레드가 같은 공유 자원에 접근했을 때를 뜻한다.

## Critical section
공유 자원을 접근하는 코드를 뜻한다. 동시접근하려는 자원에서 문제가 발생하지 않도록, 독점을 보장해줘야하는 영역이다. 가장 쉬운 방법은 앞뒤로 락하는 것이다. Critical section의 해결책은 다음 3가지를 만족해야 한다.
+ Mutual exclusion
    + 하나의 프로세스가 Critical section을 사용 중이면, 다른 프로세스는 Critical section 코드를 수행할 수 없다.
    + Atmoic하게 관리되어야 한다.
    + 한 번에 하나의 스레드만 critical section에 접근해야 한다.
    + 다른 스레드는 기다려야 한다.
    + 한 스레드가 사용을 다하면 다음 하나의 스레드가 자원을 사용한다.
+ Progress
    + Critical section에서 수행되고 있는 프로세스가 없을 때, Critical section을 접근하고자 하는 프로세스가 있다면 곧바로 수행시켜야 한다.
+ Bounded waiting
    + Critical section을 접근하고자 하는 프로세스는 Starvation이 발생하면 안 된다.

### Perterson's solution

    do {
        flag[i] = true;
        turn = j;
        while (flag[j] && turn == j);
            critical section
        flag[i] = false;
            remainder section
    } while (true);

1. Mutual exclusion를 보장한다. 두 프로세스 중 하나만 접근 가능하다.
2. Progress를 만족한다. 다음 번에 사용될 프로세스를 결정한다.
3. Bounded-waiting을 만족한다.

하지만 3개 이상은 불가능하다. 왜냐하면 위 코드에서 Critical section에서 사용하고 나면, 다음 번에 사용될 프로세스를 결정할 수 없다.

## References
* 2022 봄 운영체제 강의

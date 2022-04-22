## 목차

1. [Locks](#locks)
2. [Semaphores](#semaphores)
3. [References](#references)

## Locks
acquire() & release() 함수를 통해 critical section을 접근하고 사용한다. 대기할 때에는 lock을 계속 체크하는 spin(spinlock), lock이 풀릴 때까지 다른 일을 하는 block(mutex)이 있다. 

+ Correctness
    + Mutual exclusion, Progress(deadlock-free), Bounded waiting(starvation-free)를 필요로 한다.
+ Fairness
+ Performance

Critical section에 접근함에 따라 lock을 하기 위해서 레지스터에서 값을 불러온다. 이 과정에서 Instruction 단위에서 lock이 atomic하게 일어나지 않는 문제가 생긴다. 

![](../image/synchronization/Incorrect%20lock.png)

### Architectural support for synchronization
앞서 언급한 atomic lock의 문제를 해결하기 위해서, 하드웨어에서 Atomic instructions으로 "read-modify-write"를 한 번에 실행하는 instruction들을 제공한다.
+ Test-And-Set instruction - Test를 해보고 값을 만족하면 set을 하고 아니면 하지 않는 instruction이다. 새로운 값 / 기존 값을 반환한다.
+ Compare and swap  

## Semaphores
Lock을 얻으려고 spin하는 것은 CPU의 낭비이다. 다만 lock이 짧으면 spin하는 것이 이득일 수 있다.(Context switch overhead) Semaphore는 기본적으로 block(mutex)를 사용하며, interger value를 활용한다. Buffer의 개수를 값으로 가진다. 각 스레드는 각 buffer에 값을 읽고 쓸 수 있다. 
+ wait(): 일단 semaphore 값을 감소 시키고, 0보다 크거나 같다면 값을 사용하기 시작한다.
+ signal(): Lock이 해제 됨에 따라 일단 semaphore값을 증가 시키고, 기다리고 있던 프로세스를 깨운다.

### Binary semaphore (Mutex)
초기값을 1로 준다. 한 번에 하나의 스레드만 허용한다.

### Counting semaphore
Thread 개수 N으로 초기화한다. 하난의 리소스를 여러 개의 단위로 이용가능하게 한다. 여러 개의 스레드가 여러 개의 단위 자원을 활용할 수 있게 한다.

### Deadlock and starvation
+ Deadlock은 많은 프로세스들이 이벤트를 기다리고 있는데, 이러한 이벤트가 발생할 수 없는 경우를 뜻한다. 각자 자신의 자원을 가지고 있으면서 상대방의 자원을 필요로 할때 순환 문제가 생긴다. (signal 함수를 실행할 수 없는 경우) 
+ Starvation은 한 프로세스만 semaphore가 부족해서 사용하지 못 하고, 나머지 프로세스는 사용하는 경우를 뜻한다. (LIFO인 경우)
+ Priority inversion - 우선 순위가 높은 프로세스가 실행하려고 보니, 이렇게 preemptive하면 낮은 우선순위의 프로세스가 lock을 풀 수 없는 경우이다.

## References
* 2022 봄 운영체제 강의
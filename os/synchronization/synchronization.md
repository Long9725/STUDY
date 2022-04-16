## 목차

1. [CPU Scheduling이란?](#cpu-scheduling이란)
2. [Scheudling Criteria](#scheudling-criteria)
3. [Approaches](#approaches)
4. [General CPU Scheduler](#general-cpu-scheduler)
5. [Real-Time CPU Scheduling](#real-time-cpu-scheduling)
6. [Linux scheduling](#linux-scheduling)
7. [References](#references)

## Synchronization이란?
공유되는 자원에 대해서 접근 권한을 관리하는 기법이다. Concurrency를 저해하기 때문에 성능적인 측면에 영향을 끼친다. 프로그래머가 컨트롤할 수 있는 것이 아니고, OS에서 컨트롤해야하기 때문에 어려운 기법이다.

+ Race condition: 동시에 여러 개의 스레드가 같은 공유 자원에 접근했을 때를 뜻한다.

## Critical section
공유 자원을 접근하는 코드를 뜻한다. 가장 쉬운 방법은 앞뒤로 락하는 것이다.

### Mutual exclusion
+ Atmoic하게 관리되어야 한다.
+ 한 번에 하나의 스레드만 critical section에 접근해야 한다.
+ 다른 스레드는 기다려야 한다.
+ 한 스레드가 사용을 다하면 다음 하나의 스레드가 자원을 사용한다.

## Locks
acquire() & release() 함수를 통해 critical section을 접근하고 사용한다. 대기할 때에는 lock을 계속 체크하는 spin(spinlock), lock이 풀릴 때까지 다른 일을 하는 block(mutex)이 있다. 

+ Correctness
    + Mutual exclusion, Progress(deadlock-free), Bounded waiting(starvation-free)를 필요로 한다.
+ Fairness
+ Performance

Critical section에 접근함에 따라 lock을 하기 위해서 레지스터에서 값을 불러온다. 이 과정에서 Instruction 단위에서 lock이 atomic하게 일어나지 않는 문제가 생긴다. 

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

하지만 3개 이상은 불가능하다.

## Architectural support for synchronization
+ Atomic instructions - "read-modify-write"를 한 번에 실행하는 instruction이다.
+ Test-And-Set instruction - Test를 해보고 값을 만족하면 set을 하고 아니면 하지 않는 instruction이다. 새로운 값 / 기존 값을 반환한다.

## Semaphores
Lock을 얻으려고 spin하는 것은 CPU의 낭비이다. 다만 lock이 짧으면 spin하는 것이 이득일 수 있다.(Context switch overhead) Semaphore는 interger value를 활용한다. Buffer의 개수를 값으로 가진다. 각 스레드는 각 buffer에 값을 읽고 쓸 수 있다. 
+ wait(): 일단 semaphore 값을 감소 시키고, 0보다 크거나 같다면 값을 사용하기 시작한다.
+ signal(): Lock이 해제 됨에 따라 일단 semaphore값을 증가 시키고, 기다리고 있던 프로세스를 깨운다.



### Binary semaphore (Mutex)
초기값을 1로 준다. 한 번에 하나의 스레드만 허용한다.

### Counting semaphore
Thread 개수 N으로 초기화한다. 하난의 리소스를 여러 개의 단위로 이용가능하게 한다. 여러 개의 스레드가 여러 개의 단위 자원을 활용할 수 있게 한다.

## Deadlock and starvation
+ Deadlock은 많은 프로세스들이 이벤트를 기다리고 있는데, 이러한 이벤트가 발생할 수 없는 경우를 뜻한다. 각자 자신의 자원을 가지고 있으면서 상대방의 자원을 필요로 할때 순환 문제가 생긴다. (signal 함수를 실행할 수 없는 경우) \
+ Starvation은 한 프로세스만 semaphore가 부족해서 사용하지 못 하고, 나머지 프로세스는 사용하는 경우를 뜻한다. (LIFO인 경우)
+ Priority inversion - 우선 순위가 높은 프로세스가 실행하려고 보니, 이렇게 preemptive하면 낮은 우선순위의 프로세스가 lock을 풀 수 없는 경우이다.

## Classical problems of synchronization
### Bounded buffer problem
Producer / consumer problem이라고도 한다. Producer는 버퍼에 값을 넣고, consumer을 버퍼의 값을 빼온다. 이전에 배운 Pipes는 single producer, single consumer이다.

### Readers-Writers Problem
공유 자원을 여러 개의 readers와 writers가 공유한다. 여러 개의 스레드는 읽을 수만 있고, 하나의 스레드만 쓸 수 있다. 즉 여러 개의 reader가 있더라도 하나의 writer가 등장하면 reader는 critical section을 벗어나야 한다.

Semaphores
+ readcount: 값을 읽는 스레드들 
+ mutex: readcount 컨트롤
+ rw: 읽기 쓰기를 도와줌

Writer가 끝나면 다음에는 Writer일지, Reader일지 결정해야한다. 그리고 Reader가 모두 끝날 때까지 기달려야 한다.

### Dining-Philosophers problem
한 사람당 양쪽에 포크가 1개씩 있다.

1. 생각하고 -> 두 개의 포크를 들고(왼쪽의 포크를 먼저 집는다.)-> 먹고 -> 포크를 내려놓는다.
2. 한 번에 하나의 포크만을 고를 수 있다.

동시에 모든 인원이 포크를 잡으면 Deadlock이 걸린다. 따라서 포크를 집으려는 인원의 수가 모든 인원인지, 아닌지를 판단해 포크를 잡는 순서를 바꾼다. 

## References
* 2022 봄 운영체제 강의
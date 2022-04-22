## 목차

1. [Bounded buffer problem](#bounded-buffer-problem)
2. [Readers-Writers Problem](#readers-writers-problem)
3. [Dining-Philosophers problem](#dining-philosophers-problem)
4. [References](#dining-philosophers-problem)

## Bounded buffer problem
Producer / consumer problem이라고도 한다. Producer는 버퍼에 값을 넣고, consumer을 버퍼의 값을 빼온다. 이전에 배운 Pipes는 single producer, single consumer이다.

+ 공통 code

다음과 같다.

    int n;
    semaphore mutex = 1; // 0 또는 1
    semaphore empty = n; // 0, ..., n, 현재 버퍼의 빈 칸 
    semaphore full = 0; // 0, ..., n, 현재 버퍼를 채운 공유 자원의 개수

+ Producer code

다음과 같다.


    while(true) {
        wait(empty); // empty 값을 1 감소시킨다.
        wait(mutex); // Mutual exclusion을 만족시키기 위한 바이너리 세마포어, Critical section 진입

        /*
            critical section
        */

        signal(mutex); // Critical section 탈출을 알리는 시그널
        signal(full); // 버퍼의 공간을 하나 채웠으니 1 증가
    }

 + Consumer code

 다음과 같다.

    int n;
    semaphore mutex = 1; 
    semaphore empty = n;
    semaphore full = 0;

    while(true) {
        wait(full); // full 값을 1 감소시킨다.
        wait(mutex); // Mutual exclusion을 만족시키기 위한 바이너리 세마포어, Critical section 진입

        /*
            critical section
        */

        signal(mutex); // Critical section 탈출을 알리는 시그널
        signal(empty); // 버퍼의 공간을 하나 비웠으니 1 증가
    }   

## Readers-Writers Problem
공유 자원을 여러 개의 readers와 writers가 공유한다. 여러 개의 스레드는 읽을 수만 있고, 하나의 스레드만 쓸 수 있다. 즉 여러 개의 reader가 있더라도 하나의 writer가 등장하면 reader는 critical section을 벗어나야 한다.

Semaphores
+ readcount: 값을 읽는 스레드들 
+ mutex: readcount 컨트롤
+ rw: 읽기 쓰기를 도와줌

Writer가 끝나면 다음에는 Writer일지, Reader일지 결정해야한다. 그리고 Reader가 모두 끝날 때까지 기달려야 한다.

+ 공통 코드

다음과 같다.

    semaphore rw_mutex = 1; // 바이너리 세마포어
    semaphore mutex = 1; // 바이너리 세마포어
    int read_count = 0;

+ Writer 코드

다음과 같다.

    while(true) {
        wait(rw_mutex); // 1 -> 0

        // write 수행

        signal(rw_mutex); // 0 -> 1
    }

+ Reader 코드

다음과 같다.

    while(true) {
        wait(mutex); // read_count에 대한 Mutual exclusion을 보장한다.
        read_count++;

        if(read_count == 1)
            wait(rw_mutex); // read를 하는 동안 writer의 접근을 막는다.
        signal(mutex); // read_count에 대한 mutual exclusion 설정 해제, critical section 접근

        // reading 수행

        wait(mutex); // // read_count에 대한 Mutual exclusion을 보장한다.
        read_count--;
        if(read_count == 0)
            signal(rw_mutex); // Writer에게 사용을 알린다.
        signal(mutex); // read_count에 대한 mutual exclusion 설정 해제
    }

## Dining-Philosophers problem
한 사람당 양쪽에 포크가 1개씩 있다.

1. 생각하고 -> 두 개의 포크를 들고(왼쪽의 포크를 먼저 집는다.)-> 먹고 -> 포크를 내려놓는다.
2. 한 번에 하나의 포크만을 고를 수 있다.

동시에 모든 인원이 포크를 잡으면 Deadlock이 걸린다. 따라서 포크를 집으려는 인원의 수가 모든 인원인지, 아닌지를 판단해 포크를 잡는 순서를 바꾼다. 

+ Solution code

다음과 같다.

    // Intialized to 1
    semaphore forks[N];

    #define L(i) (i)
    #define R(i) ((i+1) % n)

    void philosopher(int i) {
        while (1) {
            think();
            pickup(i);
            eat();
            pickdown(i);
        }
    }

    void pickup(int i) {
        if (i == n-1) {
            wait(forks[L(i)]);
            wait(forks[R(i)]);
        } else {
            wait(forks[R(i)]);
            wait(forks[L(i)]);
        }
    }

    void pickdown(int i) {
        signal(forks[L(i)]);
        signal(forks[R(i)]);
    }

## References
* 2022 봄 운영체제 강의
* 동기화 관련 여러 문제 - https://wookkingkim.tistory.com/23
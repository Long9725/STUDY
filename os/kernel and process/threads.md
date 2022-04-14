## 목차

1. [Thread란?](#Thread란)
2. [Multi-Thread](#multi-thread)
3. [Concurrency-vs-paralleslism](#concurrency-vs-paralleslism)
4. [Amdahl's law](#amdahl's-law)
5. [Multithreading model](#multithreading-model)
6. [Thread pools](#thread-pools)
7. [Threading issues](#threading-issues)
8. [References](#references)

## Thread란?
Process는 자원을 할당하는 단위라면, Thread는 process 내에서 CPU를 활용하는 기본 단위이며 스케쥴링 단위이다. Program은 기본적으로 Single process & Single thread 환경이다. Pthreads(POSIX Threads)라는 표준이 있다. 

### Pthread
A POSIX standard (IEEE 1003.1.c) API for thread creation and synchronization. \
정의만 있고, 구현할 필요는 없다. UNIX 계열 OS(Solaris, Linux, Mac OS X) 등에서 사용한다.

## Multi-Thread
한 프로세스 내에서 여러 개의 Thread가 있는 환경이다. Multi-Thread 환경에서 각 Thread는 Code, data, files 영역을 공유하며, registers, stack 영역을 독립적으로 사용한다. 따라서 Multi-Thread에서  도 context switch가 일어난다. 각 Thread는 공유하는 영역이 있으므로 process에 비해 context switch cost가 적다.

### 장점
+ Responsiveness - 응답성이 좋아진다. 프로세스의 일부가 실행이 막히더라도, 나머지를 활용해 계속해서 실행할 수 있는 Thread가 있기 때문이다. 이는 특히 서버 환경에서 사용자 인터페이스 등에서 중요하게 활용된다. 
+ Resource Sharing - 각 Thread는 공유하는 영역이 있으므로, 중복된 정보가 아닌 하나의 정보를 사용한다. Shared memory나 message passing보다 접근이 쉽다.
+ Economy - 프로세스를 새로 만드는 것보다 cost가 낮고, context switching overhead가 적다.  
+ Scalability - 현대 CPU는 multiprocessor architectures인 경우가 대부분이다. 따라서 프로세스는 각 Thread를 각 processor에 동시에 실행할 수 있으므로, 이러한 CPU의 장점을 활용할 수 있게 된다.

## Concurrency vs Paralleslism
Concurrency는 single core processor에서 각 task에게 주어진 시간 안에 일을 처리하는 것을 뜻한다. 이는 한 번에 하나의 Task만 처리하지만, 동시에 Task들을 처리하는 것처럼 보이게 한다. \
반면 Parallesigm은 여러 개의 core processor에서 실제로 각 Task를 동시에 처리하는 것을 뜻한다.

## Amdahl's Law
아무리 프로그램을 최적화하더라도 실행 속도를 빠르게 할 수 없는 영역이 존재한다. 왜냐하면 항상 Multithreading 환경을 사용할 수 있는 것이 아니며, 프로그램은 제일 처음에는 Single process, Single thread 환경으로 시작하기 때문이다.  

## Multithreading model
대략적으로 3개의 모델이 있으며, 각 모델을 혼합해서 쓰는 경우도 존재한다.
### Many-to-One
여러 개의 user thread가 하나의 kernel thread에 mapping되는 것을 뜻한다. 하나의 user thread가 block되면, 같은 kernel thread에 mapping 돼있던 모든 user thread가 block된다. Single core 시절에 사용하던 방법이다.

### One-to-one
하나의 user thread가 하나의 kernel thread에 mapping 되는 것을 뜻한다.

### Many-to-Many
여러 개의 user thread가 여러 개의 kernel thread에 mapping 되는 것을 뜻한다.

## Thread pools
미리 여러 개의 threads를 만들어놓고, 모아놓은 곳을 뜻한다. multithreading이 필요할 때마다 thread를 만들고, 필요 없어지면 kill하는 것은 비용이 많이 들어간다. (Process도 마찬가지이다.) 따라서 multithreading이 필요해지면 thread pools에 threads를 요구하는 형식으로 사용한다. 이를 위해서 scheduling이 필요하다.

## Threading issues
+ Multithreading 환경에서 어느 한 thread가 fork() & exec() 시스템 콜을 호출하면?
    + fork()를 호출한 thread만 복제할 것인지, 모든 thread를 복제할 것인지?
        + UNIX는 2가지를 가지고 있고, Linux는 전자를 주로 쓴다. 정답 X
    + exec()를 호출하면 보통 모든 thread를 대체한다. 이런 경우에는 모든 thread가 필요가 없어지므로, 하나의 thread만 복제한다.(보통 Linux)
+ Signal이 발생하면 어느 특정 thread가 받아야 하는지, 아니면 모든 thread가 받아야 하는지, 어느 thread가 handling 해야 하는지
    + Default signal handler가 있고, user-defined signal handelr도 있다. 그리고 default를 user-defined로 정의하여 override 할 수 있다. 따라서 상황에 맞게 override하면 된다.
+ Thread 중단은 어떻게 하는지
    + thread id를 사용해 종료시킬 수 있다. Asynchronous cancellation은 즉시 종료이고, Deferred cancellation은 나중에 종료를 결정한다. 기본은 Deferred이다. Memory leak이나, critical setion 등의 문제가 있기 때문이다.
+ Thread-local storage
    + static data처럼 사용한다.

## References
* 2022 봄 운영체제 강의
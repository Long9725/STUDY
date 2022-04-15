## 목차

1. [CPU Scheduling이란?](#cpu-scheduling이란)
2. [Scheudling Criteria](#scheudling-criteria)
3. [Approaches](#approaches)
4. [General CPU Scheduler](#general-cpu-scheduler)
5. [Real-Time CPU Scheduling](#real-time-cpu-scheduling)
6. [Linux scheduling](#linux-scheduling)
7. [References](#references)

## CPU Scheduling이란?
실행 가능한 프로세스들 중에서 다음에 실행할 프로세스를 결정하는 정책이다.

+ Mechanism: How to transition? 
    + Ex) context switching
+ Policy: When to transition?

### 용어
+ Workload: 일의 양, 프로세스에 대한 설명
    + arrival time, execution time, etc.
+ Scheduler: 언제 작업을 실행시킬지 결정하는 로직
+ Metric: 스케쥴링 품질을 측정할 수 있는 척도
    + turnaround time, response time, fairness, etc.

## Scheudling Criteria
+ CPU utilization: CPU가 바쁜 정도, 100%를 목표로 스케쥴을 최적화해야한다.
+ Throughput: 시간당 실행된 프로세스의 양
+ Turnaround time: 프로세스 하나가 실행을 마치는 데 필요한 시간
+ Waiting time: 프로세스가 ready queue에서 대기한 시간
+ Response time: 어떤 Task에 대해서 request가 왔고, 이를 처리해서 첫 response가 제공되는 데 걸리는 시간(결과물이 아닌 응답)

## Approaches
### Workload Assumptions
1. 각자의 프로세스는 동일한 시간이 걸린다.
2. 모든 작업은 동시에 도착했다.
3. 한 번 실행되면, 각 작업은 완료될 때까지 실행된다.
4. 모든 작업은 CPU만 사용한다.
5. 각 작업의 모든 실행 시간은 알고 있다.

+ Metric: Turnaround time, Turnaround time = Completion time - Arrival time 

### Non-preemptive scheduling
스케쥴러는 현재 실행 중인 프로세스가 자발적으로 CPU를 내려놓는 것을 기다린다. 그러므로 프로세스들이 협력적으로 실행되어야 하는데, 비협력적인 프로세스가 있다면?

<details><summary> Non-preemptive schedulings </summary>

### FIFO
First-In, First-Out. First-Come, First-Served(FCFS)라고도 한다. 각 작업은 먼저 도착했으면 먼저 실행된다. Non-preemptive 접근법이다. 특정 작업만 실행되지 않는다.(no starvation) \
=> Convoy effect, 대기 작업 줄이 늘어지는 단점이 있다. 그리고 작은 작업 앞에 큰 작업들이 존재하면 평균 대기 시간이 길어진다. 그리고 CPU 작업이 크면 I/O 작업이 놀게 된다. 반대로 I/O 작업이 많으면 이를 기다리느라 CPU가 놀게 된다. 

### Shortest Job First (SJF)
+ 각각의 작업이 서로 다른 실행 시간을 가진다. (가정 1 폐기)
가장 작은 실행 시간을 가진 작업을 고르는 스케쥴 방식이다. 가정한 상태에서는 최적의 Turnaround time을 가진다. Non-preemptive 접근법이다. 따라서 큰 작업 실행 도중, 매우 작은 작업이 들어왔다하더라도 큰 작업을 중단하고 실행할 수 없다.

</details>

### Preepmtive scheduling
스케쥴러가 프로세스에 간섭하며, 강제로 context switch를 진행한다.

<details><summary> Preemptive schedulings </summary>

### Shortest-next-CPU-burst
+ 작업은 동시에 도착하지 않아도 된다. (가정 2 폐기)
+ SJF의 Preemptive 버전이다. Arrival time이 추가된다. (가정 3 폐기) 

새로운 작업의 실행 시간이 현재 작업의 남은 실행 시간보다 작다면, 현재 작업을 중단하고 새로운 작업을 실행시킨다.

### Round Robin
각 작업을 Time slice(또는 Time quantum)이라는 시간 단위로 자른다. 작업을 실행하다가 이 시간이 지나면 다음 작업으로 넘어간다. 이를 위해 OS는 tick을 활용해 시그널을 보낸다.

+ Time slice가 너무 짧으면 context switch overhead가 높아진다.
+ Time slice가 너무 길면 responsive가 떨어진다.

Circular FIFO queue 구조를 가지므로 no starvation이다. 그리고 Response time을 향상 시킬 수 있는 기본적인 방법이다. 만약 ready queue에 프로세스가 없고 run queue에만 프로세스가 1개 있을 경우, context switch 없이 실행을 계속한다.

RR은 Metric이 response time에 초점이 맞춰져있다. Reponse time = First-run time - Arrival time이다. RR은 SJF보다 높은 turnaround time을 가지지만, response time은 더 좋다.   

### Priority Scheduling
우선순위에 따라 작업을 처리한다. 경우에 따라 Preemptive, non-preemptive를 오간다. 높은 우선순위의 작업이 계속 들어오면 낮은 우선순위의 작업이 starvation이 된다.

### Multi-level feedback queue
각 우선순위에 따라 특정 큐에 넣어 작업을 처리한다. 큐 안에서 우선순위에 따라 스케쥴링 된다. RR은 모든 큐에 적용된다.

</details>

## General CPU Scheduler
일반적인 상황에서의 CPU 스케쥴러를 고려한다.

<details><summary> General CPU Scheduler</summary>

### Incorporating I/O
I/O 사용이 가능한 스케쥴링을 고려함에 따라 가정 4를 폐기한다. CPU와 I/O가 상호작용하는 작업 A와 CPU만 사용하는 작업 B가 있다. 그렇다면 A가 CPU를 사용한 뒤, I/O 작업을 한다면 이 작업을 하는 동안 B를 실행시킨다.

### Goals & Challenge
Turnaround time과 Response time을 최적화 하는 것을 목표로 한다. 하지만 시간이 얼마나 걸리는지 모르는 프로세스의 작업이 들어온다. (가정 5 폐기) 그렇기 때문에 RR이 자주 사용된다. 과거의 패턴을 분석해 작업을 예측하는 방법도 있다.(branch predictors or cache algorithms) 그런데 os 특성 상 빠르게 진단하고 결정을 내려야하기 때문에, 알고리즘적으로 완벽하지 않아도 간단하면서 효과적인 알고리즘을 활용하는 편이다.

### NUMA and CPU Scheduling
Non-Uniform Memory Access(뷸균일 기억 장치 접근), 멀티프로세서 시스템에서 사용되고 있는 컴퓨터 메모리 설계 방법이다. 1개의 프로세서와 메모리 등을 통틀어 노드라는 단위를 쓴다. 각 노드 내에서 프로세서에 가까운 메모리는 빠르게 접근할 수 있지만, 멀리 있는 다른 노드의 메모리는 느리게 접근한다. (다른 노드의 CPU를 통해서 접근) \
CPU 스케쥴러는 이에 대해서 작업을 좀 더 빠르게 하기 위해서, 다른 노드의 메모리에 직접 접근하지 않고 인터페이스를 통해 작업을 다른 노드에 할당할 수 있다. 현재 노드의 메모리가 꽉차면 다른 노드의 메모리에 할당하고, 그 노드에서 작업을 처리할 수도 있다. 이렇게 다른 노드의 메모리에 할당된 메모리는 메모리 관리자가 현재 노드로 다시 가져오는 작업을 한다.

### Multiple-Processor Scheduling - Load Balancing
여러 개의 CPU에 작업을 골고루 분산해, 효율을 높이는 방법이다.
+ Push migration - 과부화된 CPU에서 다른 CPU를 작업을 밀어넣는다.
+ Push migration - 대기 중인 CPU에서 다른 바쁜 CPU의 대기 작업을 가져온다.

</details>

## Real-Time CPU Scheduling
1. Interrupt latency - interrupt가 발생해서 interrupt service routine이 제공되는 데 걸리는 시간
2. Dispath latency - 현재 실행 중인 프로세스에서 다음 프로세스로 스케쥴하는 데 걸리는 시간
    + Kernel mode에서 프로세스를 선점하는데 걸리는 시간
    + 우선순위가 낮은 프로세스의 자원을 반환받고, 그 자원을 선점하는데 걸리는 시간

<details><summary> Real-Time CPU Scheduling </summary>

### Soft real-time systems
작업이 Deadline을 무조건 맞출 필요까지는 없다.

### Hard real-time systems
작업은 Deadline을 무조건 맞춰야한다.

### Priority-based Scheduling in Real-time
스케쥴러는 Preemptive를 지원해야하므로 우선순위 기반 스케쥴링을 한다. Hard real-time에서는 deadlines에 대한 스케쥴링도 제공해야한다.

+ 정해진 시간마다 CPU를 요구하는 p(periodic)
+ 프로세스의 deadline을 뜻하는 d
+ 실제 실행 시간 t

0 <= t <= d <= p

### Rate monotic scheduling
우선순위가 period의 역으로 매겨진다. Period가 짧으면 높은 우선순위, period가 길면 낮은 우선순위를 가진다. P(period, processing time)을 입력값으로 한다. 

### Earliest deadline first scheduling
EDF라고 한다. 우선순위가 deadline에 따라 부여된다. Deadline이 짧으면 높은 우선순위, 낮으면 낮은 우선순위이다.

### Proportional Share Scheduling
프로세스마다 CPU를 일부분 점유한다. 새로운 프로세스가 CPU 점유를 요청했는데, 이를 수용 시 100%가 넘치면 관리 컨트롤러가 요구를 거부한다. Virtualied System에서 주로 사용한다. 

+ Virtual CPU의 스케쥴링
+ Virtual CPU와 Physical CPU 간의 스케쥴링 

### Algorithm evaluation
1. Criteria를 정한다.
2. Algorithm을 고려한다.
3. Modeling을 고려한다.
    + 각 알고리즘의 평균 대기 시간 중, 최소값을 계산한다.
    + Queue에 관련된 시간들을 수학적으로 계산한다.
    + Simulations
    + Implementation, 실제 시스템에 테스트 해보는 것은 비용이 굉장히 비싸다.

</details>

## Linux scheduling
2가지 우선 순위를 가진다.
+ Nice value: -20 ~ +19, default는 0이다.
    + Nice가 높으면 낮은 우선 순위이다.
+ Real-time priority: 0 ~ 99
    + 값이 높으면 높은 우선순위이다.
+ Time slice에 관해 default를 정하는게 쉽지 않다.
    + 작업의 종류와 스케쥴링 목적에 맞게 Time slice한다.
    + 시스템의 부하와 프로세스의 우선순위에 따라 다르다.
        + TS = P * (weight / runqueue's total weight)
    + 현재 실행 중인 프로세스에 비해 새로운 프로세스가 소비한 CPU 점유율이 낮다면, 현재 실행 중인 프로세스가 더 자주 실행된 것이므로 새로운 프로세스를 스케쥴링한다.(이 프로세스는 스케쥴링된 회수가 적다고 판단한다.)   
    + 우선순위가 똑같다면 Time sliced의 upper bound와 lower bound를 설정해, 프로세스의 개수에 따라 가변적인 Time slice를 사용하여 RR로 스케쥴링한다.
        + n = 작업의 개수, nr_latency는 동적인 Time slice를 결정 할 수 있는 작업의 개수 제한
        + n < nr_latency, P = sched_latency
        + otherwise, P = min_granularty * n (default는 1ms)
    
CFS를 지향한다.
+ 스케쥴링을 위한 Process를 고르기 위해서, vruntime으로 인덱싱된 rbtree를 사용한다.

## References
* 2022 봄 운영체제 강의
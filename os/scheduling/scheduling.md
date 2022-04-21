## 목차

1. [CPU Scheduling이란?](#cpu-scheduling이란)
2. [Scheudling Criteria](#scheudling-criteria)
3. [Workload assumptions](#workload-assumptions)
4. [References](#references)

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

### 목적
모든 스케쥴러가 공평하게 작업할 수 있도록 해야한다. 하지만 안전성과 효율성을 높이기 위하여 공평성의 일부분을 희생한다.
+ 공평성 : 모든 프로세스가 자원을 공평하게 배정받아야 하며, 특정 프로세스가 배제되어서는 안 된다.

+ 효율성 : 시스템 자원을 놀리는 시간 없이 스케줄링해야 한다.

+ 안정성 : 우선순위를 사용하여 중요한 프로세스가 먼저 처리되도록 해야 한다.

+ 반응 시간 보장 : 응답이 없는 경우 사용자는 시스템이 멈춘 것으로 가정하기 때문에 시스템은 적절한 시간 안에 프로세스의 요구에 반응해야 한다.

+ 무한 연기 방지 : 특정 프로세스의 작업이 무한히 연기되어서는 안 된다.

### 단계
+ 고수준 스케쥴링: Long-term scheduling, 가장 큰 틀에서 이루어지는 CPU 스케쥴링으로 시스템 내의 전체 작업 수를 조절한다. 시스템 과부하를 막기 위해서 시스템이 받아들일지 말지를 결정하므로, 시스템 내에서 동작 시에 실행 가능한 프로세스의 총 개수가 정해진다.
+ 중간 수준 스케쥴링: 중지(Suspend)와 활성화로 전체 시스템의 활성화된 프로세스 수를 조절한다. 이로 인해 저수준 스케줄링이 원만하게 이루어지도록 완충하는 역할을 한다.
+ 저수준 스케쥴링: Short-term scheduling, 가장 작은 단위에 스케쥴링으로 어떤 프로세스에 CPU를 할당할지, 어떤 프로세스를 대기 상태로 보낼 것인지 등을 결정한다. 

### 고려사항
+ Preemptive vs Non-preemptive
    + Context switching overhead와 프로세스의 배치를 고려한다.
+ CPU bound vs I/O bound
    + 프로세스가 대기 상태에 있다가 CPU를 할당받아 실행하면 CPU burst, 입출력 작업을 하면 I/O burst라고 한다.
    + CPU bound process: CPU를 많이 사용하여 CPU burst가 많은 프로세스이다.
    + I/O bound process: 입출력을 많이 사용해 I/O burst가 많은 프로세스이다.
+ 전면 프로세스 vs 후면 프로세스
    + 전면 프로세스: GUI를 사용하는 운영체제에서 화면의 맨 앞에 놓여 현재 입출력이 사용되고, 사용자와 상호작용이 가능한 프로세스이다.
    + 후면 프로세스: 사용자의 입력 없이 작동한다.
    + 전면 프로세스는 사용자의 요구에 즉각 반응해야 하지만, 후면 프로세스는 그럴 필요가 없다. 따라서 전면 프로세스의 우선순위를 높게 하여 먼저 처리해줘야 한다.

### 우선순위
+ 커널 프로세스 > 일반 프로세스

+ 전면 프로세스 > 후면 프로세스

+ 대화형 프로세스 > 일괄 처리 프로세스

+ 입출력 집중 프로세스 > CPU 집중 프로세스

* * *

## Scheudling Criteria
스케줄링 알고리즘의 효율성을 판단하는 기준이다. CPU의 입장에서 프로세스가 들어와 작업을 처리하고 나갔을 때를 기준으로 한다.

### CPU
+ CPU utilization: CPU가 바쁜 정도, 100%를 목표로 스케쥴을 최적화해야한다.
+ Throughput: 시간당 실행된 프로세스의 양

### Process
+ Turnaround time: 프로세스 하나가 실행을 마치는 데 필요한 시간
    + 대기 시간 + 실행 시간
+ Waiting time: 프로세스가 ready queue에서 대기한 시간
+ Response time: 어떤 Task에 대해서 request가 왔고, 이를 처리해서 첫 response가 제공되는 데 걸리는 시간(결과물이 아닌 응답)

* * *

## Workload assumptions
1. 각자의 프로세스는 동일한 시간이 걸린다.
2. 모든 작업은 동시에 도착했다.
3. 한 번 실행되면, 각 작업은 완료될 때까지 실행된다.
4. 모든 작업은 CPU만 사용한다.
5. 각 작업의 모든 실행 시간은 알고 있다.

+ Metric: Turnaround time, Turnaround time = Completion time - Arrival time 

* * *

## References
* 2022 봄 운영체제 강의
* 보통의 개발자 - https://bnzn2426.tistory.com/65
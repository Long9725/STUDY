## 목차

1. [Linux scheduling](#linux-scheduling)
2. [Time slice](#time-slice)
3. [Complete Fair Scheduling (CFS)](#complete-fair-scheduling-cfs)
4. [References](#references)

## Linux scheduling
현재 실행 중인 프로세스에 비해 새로운 프로세스가 소비한 CPU 점유율이 낮다면, 현재 실행 중인 프로세스가 더 자주 실행된 것이므로 새로운 프로세스를 스케쥴링한다.(이 프로세스는 스케쥴링된 회수가 적다고 판단한다.) \
2가지 우선 순위를 가진다.
+ Nice value: -20 ~ +19, default는 0이다.
    + Nice가 높으면 낮은 우선 순위이다.
+ Real-time priority: 0 ~ 99
    + 값이 높으면 높은 우선순위이다.
+ 리눅스 입장에서는 0 ~ 139이다.
    + Real-time priority + Nice value

* * *

## Time slice
Time slice에 관해 default를 정하는게 쉽지 않다.

+ 작업의 종류와 스케쥴링 목적에 맞게 Time slice한다.
+ 시스템의 부하와 프로세스의 우선순위에 따라 다르다.
    + TS = P * (weight / runqueue's total weight)
+ 우선순위가 똑같다면 Time sliced의 upper bound와 lower bound를 설정해, 프로세스의 개수에 따라 가변적인 Time slice를 사용하여 RR로 스케쥴링한다.
    + n = 작업의 개수, nr_latency는 동적인 Time slice를 결정 할 수 있는 작업의 개수 제한
    + n < nr_latency, P = sched_latency
    + otherwise, P = min_granularty * n (default는 1ms)

* * *

## Complete Fair Scheduling (CFS)
2007년 발표 된 리눅스 커널의 스케줄러로, CFS는 RSDL(Rotating Staircase Deadline) 스케줄러를 기초로 한다. vruntime으로 인덱싱된 RB-트리 구조를 사용하야 O(logN) 성능을 가지는 스케줄러이다.
+ vruntime(Virtula runtime)은 가상의 CPU 사용 시간을 의미하며, 우선순위(가중치)가 부여된 CPU 시간을 의미한다.
    + vruntime += execution time x (default weight / process weight)
    + 우선순위가 높을수록 weight 값은 높아진다.
    + vruntime이 가장 작은 프로세스를 선택한다. 
    + 오랫동안 실행되지 못한 프로세스는 상대적으로 vruntime이 작아지므로, starvation이 발생하지 않는다.

* * *

## References
* 2022 봄 운영체제 강의
+ 프로세스 및 리눅스 스케줄링(CFS)의 이해 - https://velog.io/@ba159sal/OS-%EB%A6%AC%EB%88%85%EC%8A%A4-%EC%83%88%EB%A1%9C%EC%9A%B4-System-Call-%EC%B6%94%EA%B0%80-vpw772m0
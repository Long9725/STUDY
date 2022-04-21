## 목차

1. [OS(Operating System)란?](#osoperating-system란)
2. [역할](#역할)
3. [목적](#목적)
4. [References](#references)


## OS(Operating System)란?
OS는 컴퓨터 시스템의 하드웨어, 소프트웨어적인 자원들을 효율적으로 운영 및 관리한다. 이로써 사용자가 컴퓨터를 편리하고, 효과적으로 사용할 수 있도록 하는 시스템 소프트웨어이다. 컴퓨터 하드웨어 바로 위에 설치되어, 사용자 및 다른 소프트웨어와 하드웨어를 연결하는 소프트웨어 계층이다. 즉, 중개자 역할을 해주는 프로그램이다. \
OS의 역할은 소프트웨어로도 가능하다. 하지만 비효율적이거나 보안에 문제가 생기기 때문에, OS를 통해 하드웨어적으로도 컨트롤하는 것이다.

## 역할
1. 자원관리
컴퓨터 시스템 자원의 효율적인 관리
2. 자원보호
프로그램이나 다른 사용자가 데이터를 삭제하거나 중요 파일에 접근하지 못하게 컴퓨터 자원들을 보호
3. 인터페이스 제공
하드웨어 인터페이스와 사용자 인터페이스 제공하여 편리하게 사용하도록 지원

## 목적
더 좋은 컴퓨터 시스템을 만들기 위해서
* Functionally
* Performance / cost
* Reliability
* Energy efficiency
* etc.

여기서 처리능력(Throughput), 반환시간(Turn around time), 사용가능도(Availability), 신뢰도(Reliabilty)는 운영체제의 성능을 평가하는 기준이 된다.
* Throughput - 일정 시간 내에 시스템이 처리하는 일의 양
* Turn around time - 시스템에 작업을 의뢰한 시간부터 처리가 완료될 때까지 걸린 시간
* Availability - 시스템을 사용할 필요가 있을 때 즉시 사용 가능한 정도
* Reliability - 시스템이 주어진 문제를 정확하게 해결하는 정도
-> 어떻게 측정하지?

## Issues

### I/O
I/O Devices는 기본적으로 CPU보다 매우 느리다. 규모가 큰 I/O 작업을 하는 동안 CPU는 가만히 있게 되는데, 이러한 것을 어떻게 방지할 것인지?

+ 각각의 I/O Device controller는 특정한 설정과 자신만의 buffer를 가진다.
    + Device controller는 보통 Device driver이라고 생각하면 된다.
+ CPU는 I/O Devices에게 특정한 명령을 줌으로써 관리한다.
+ CPU는 main memory에 있는 data를 local buffer에 쓰거나, 반대로 가져온다. 

=> I/O가 CPU의 명령을 끝냈는지 상태를 체크할 필요가 있으며, main memory와 device buffers 간의 data 움직임도 관리해야 한다.

## References
* 2022 봄 운영체제 강의
* https://coding-factory.tistory.com/300


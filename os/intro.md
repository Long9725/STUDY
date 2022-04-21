## 목차

1. [OS(Operating System)란?](#osoperating-system란)
2. [Issues](#issues)
3. [References](#references)


## OS(Operating System)란?
OS는 컴퓨터 시스템의 하드웨어, 소프트웨어적인 자원들을 효율적으로 운영 및 관리한다. 이로써 사용자가 컴퓨터를 편리하고, 효과적으로 사용할 수 있도록 하는 시스템 소프트웨어이다. 컴퓨터 하드웨어 바로 위에 설치되어, 사용자 및 다른 소프트웨어와 하드웨어를 연결하는 소프트웨어 계층이다. 즉, 중개자 역할을 해주는 프로그램이다. \
OS의 역할은 소프트웨어로도 가능하다. 하지만 비효율적이거나 보안에 문제가 생기기 때문에, OS를 통해 하드웨어적으로도 컨트롤하는 것이다.

### 역할
1. 자원관리
컴퓨터 시스템 자원의 효율적인 관리
2. 자원보호
프로그램이나 다른 사용자가 데이터를 삭제하거나 중요 파일에 접근하지 못하게 컴퓨터 자원들을 보호
3. 인터페이스 제공
하드웨어 인터페이스와 사용자 인터페이스 제공하여 편리하게 사용하도록 지원

### 목적
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

* * *

## Issues

## I/O
I/O Devices는 기본적으로 CPU보다 매우 느리다. 규모가 큰 I/O 작업을 하는 동안 CPU는 가만히 있게 되는데, 이러한 것을 어떻게 방지할 것인지?

+ 각각의 I/O Device controller는 특정한 설정과 자신만의 buffer를 가진다.
    + Device controller는 보통 Device driver이라고 생각하면 된다.
+ CPU는 I/O Devices에게 특정한 명령을 줌으로써 관리한다.
+ CPU는 main memory에 있는 data를 local buffer에 쓰거나, 반대로 가져온다. 

=> I/O가 CPU의 명령을 끝냈는지 상태를 체크할 필요가 있으며, main memory와 device buffers 간의 data 움직임도 관리해야 한다.

* * *

## Protection
사용자 어플리케이션이 시스템을 망치는 것을 어떻게 방지하는가?
+ 어플리케이션이 디스크에 직접 접근하면?
+ 어플리케이션이 HLT instruction을 수행하면?
    + 더이상 수행할 instruction이 없다는 명령어로, 시스템은 idle 상태가 된다.

=> OS에 의해서 수행된다.

* * *

## Protected or privilged instructions
사용자 모드에서 실행이 불가능한 명령어이다.
+ I/O에 직접 접근하는 것
+ System register에 접근하는 것
    + Program counter 등
+ Memory state management  
    + Page table updates, page table pointers, TLB loads, etc.
+ HLT instruction IA-32 

=> 접근하면 Segmentation fault를 자주 보게 된다. 접근 권한이 없는데, 접근하지 말라는 뜻이다. (다른 뜻도 있겠지만 이 경우에 주로)

### CPU Modes of operation
운영체제는 다음과 같은 최소 2개의 mode를 지원해야 한다.
+ Kernel mode
+ User mode

대표적인 CPU는 다음으로 지원한다.
+ 4 privilege level in IA-32(Intel x86/AMD): Ring 0 > 1 > 2 > 3
+ 2 privilege level in ARM: User vs Supervisor

Mode는 protected register에 status bit를 통해 결정된다.
+ IA-32: Current Privilege Level(CPL) in CS register
    + CS register: Code Segment register, 코드 세그먼트를 가리키는 레지스터이다. 프로그램의 코드 세그먼트의 시작 주소를 포함한다. 이 세그먼트 주소에 명령어 포인터(IP) 레지스터의 오프셋 값을 더하면, 실행하기 위해 메모리로부터 가져와야 할 명령어의 주소가 된다.

+ ARM: Mode field in CPSR register
    + PSR: Program Status Register, 프로그램 상테 레지스터이다. Current와 Saved가 있다.
    + CPSR: 현재 코어의 내부 동작을 모니터링하고 제어하는데 사용되는 레지스터이다.
    + SPSR: 프로세스의 동작 모드가 변경될 때, CPSR의 내용을 저장하는 역할을 한다.

* * *

## Servicing requests
운영체제에게 서비스를 제공을 요청하기 위해서 어떻게 해야할까?
+ Disk drives에 접근하지 못하는 어플리케이션은 어떻게 파일을 읽어야 할까?
+ 사용자 프로그램은 privileged한 무언가를 접근하려면 운영체제에게 요청해야 한다.
    + printf()를 한다고 하면, Standard library가 OS에게 write()를 요청한다. OS는 System call을 통해 그래픽 드라이버에 write()를 실행하여, 화면에 내용을 출력해준다.

### System calls
운영체제는 보호된 함수를 실행한다. 이를 System calls라고 한다. OS 코드 내에 있다. System calls를 사용하기 위해서 kernel mode로 진입하고, 다 끝나면 user mode로 되돌아간다. Calling convention을 사용한다.

+ 어플리케이션에서 System calls를 이용하지 않고 직접 접근하는 것을 거부한다.
+ OS는 특정 자원이 한 어플리케이션에 의해서 독점되지 않도록 관리한다.
+ OS는 공유되는 자원이 공평하게 사용되도록 관리한다.

### Exception
Interrupts는 하드웨어적으로 발생하는 것이라면, Exceptions은 소프트웨어가 instructions를 실행하면서 발생하는 것이다.
+ Synchronous하다고 말한다. 언제 interrupts가 걸릴 지 알 수 있기 때문이다.
+ IA-32에서는 Traps, Faults, Aborts로 나눈다.
    + Traps: 의도한 Exception이다. System call traps 등이 있다.
        + 다음 instruction에 대한 제어 권한을 얻는다.
        + INT(IA-32), SVC(ARM)라는 TRAP이 있다. Calling convetion으로 정의된 숫자를 같이 넘겨주면, 그것에 맞는 System calls을 진행한다. 숫자와 맞는 함수의 포인터를 가져와 함수를 실행하고 다시 user mode로 돌아간다.
    + Faults: 의도하지 않은 Exception이다. Page faults(회복가능), protection faults(회복 불가능) 등이 있다.
        + 현재 instruction을 다시 실행하거나, 중단시킨다.
    + Aborts: 무언가 에러가 났을 때, 회복이 불가능하여 현재 프로그램을 중단시킨다.

* * *

## Control
CPU는 실행 중인 프로그램으로부터 어떻게 제어를 가져올 수 있을까?

+ Cooperative approach
+ A non-cooperative apporach
    + 하드웨어적으로 Inetrrupts를 발생시키는 타이머를 사용한다. 이를 통해 운영체제는 프로세스로부터 CPU 제어권을 되가져온다. 스케쥴링에 사용된다.
    + 이러한 타이머는 privileged 되어 OS만 가져올 수 있다. 

* * *

## Memory protection
Memory를 어떻게 보호할 것인가? 어플리케이션은 OS의 간섭 없이 memory에 직접 접근할 수 있다. 따라서 운영체제는 다음과 같은 역할을 한다.

+ 다른 어플리케이션의 메모리에 접근하는 것을 방지한다.
+ 보호된 메모리 공간에 접근하는 것을 방지한다.

### Simplest memory protection
각각의 process에 base와 limit registers를 정의해서, 이 범위를 넘어가면 abort 시킨다.

### Virtual memory
한정된 physical memory의 한계를 극복하고자 디스크와 느린 저장장치를 활용해, 애플리케이션들이 더 많은 메모리를 활용하게 할 수 있게 해주는 기술이다. 모든 프로세스는 자신만의 공간을 가지고 있다. 그리고 프로세스가 소유한 메모리에만 접근이 가능하다. 다른 프로세스에 의해 소유된 메모리는 숨겨져 있고, 접근이 불가능하다. 자세한 내용은 해당 문서 참고.

+ Page table pointers, page protection, TLBs

* * *

## Synchronization
동시에 수행 가능한 어플리케이션을 어떻게 조화롭게 수행할 것인가? 동시에 공유 자원에 여러 개의 어플리케이션이 접근하면 어떻게 할 것인가?

+ Interrupts를 사용하고, 사용하지 않는 관리 방법 => 멀티 코어에서는 이것으로만 관리 불가능하다.
+ 하드웨어에서 제공해주는 special atomic instruction을 사용한다.        
    + Lock이라는 자물쇠를 사용한다.



## References
* 2022 봄 운영체제 강의
* https://coding-factory.tistory.com/300


## 목차

1. [Virtual memory란?](#virtual-memory란)
2. [Paging file](#paging-file)
3. [Page](#page)
4. [Demanding page](#demanding-page)
5. [Paging table](#paging-table)
6. [Page fault](#page-fault)
7. [용어](#용어)
8. [References](#references)

## Virtual memory란?
한정된 physical memory의 한계를 극복하고자 디스크와 느린 저장장치를 활용해, 애플리케이션들이 더 많은 메모리를 활용하게 할 수 있게 해주는 기술이다. 모든 프로세스는 자신만의 공간을 가지고 있다. 그리고 프로세스가 소유한 메모리에만 접근이 가능하다. 다른 프로세스에 의해 소유된 메모리는 숨겨져 있고, 접근이 불가능하다. 이렇게 서로 완전히 독립되어있는 프로세스의 logical memory와 physical memory를 분리하기 위해 사용한다. physical memory <= logical memory가 가능하다. 프로세스가 실제 필요로 하는 부분만 메모리로 올리는 Demand-Paging 기법을 사용한다. 여기서 메모리가 전부 소진되면 디스크 공간을 메모리처럼 활용한다. 

## Paging file
Swap file이라고도 한다. 디스크를 메모리처럼 활용할 때, 모든 프로세스가 사용할 수 있는 가상 메모리로 사용할 수 있는 파일이다. 하드 스왑이라는 페이징 파일에서 실제 physical memory로 데이터를 올리고 내리고 하는 작업을 진행한다. \
만일 4GB의 램이 있고 디스크에 4GB의 페이징 파일이 있다면, 수행 중인 애플리케이션은 8GB의 램이 있는 것과 유사한 효과를 누릴 수 있다. 물론 실제 8GB의 램보다는 성능이 떨어진다. 

## Page
가상 메모리를 사용하는 최소 단위이다. 원하는 크기의 데이터를 physical memory로 로드하지 못하게 되는 상황을 막기 위함이다. \
데이터의 크기를 무작위로 로드하고 언로드하면 메모리 공간에 fragmentation이 발생하기 때문이다.

### Fragmentation
![](./image/virtual_memory/FragmentationDefragmentation.gif)

## Demanding page
메모리 관리 메커니즘(MMU 메커니즘)을 사용해서 여러 프로세스가 시스템의 메모리를 효율적으로 공유할 수 있도록 하는 기술이다. \
실제로 필요한 Page만 물리 메모리로 가져오는 방식이다. 페이징 테이블을 사용하여 가상 메모리에 대응하는 물리 메모리 주소를 찾아낸다. 

## Page table
![](./image/virtual_memory/page_table.png)
프로세스의 virtual address space를 physical memory와 mapping 시켜주는 표이다. 프로세스들은 자신의 고유한 Page table이 있다. \
Page table은 page table entry로 구성되어 있다. 각 PTE는 해당 entry가 커버하는 virtual address나 physical memory의 상태를 기록하는 형태로 구성되어 있다. 

### Page table entry
![](./image/virtual_memory/page_table_entrys.png)

## Page fault
프로세스가 어떤 페이지에 처음 접근하거나 swap-out 된 페이지에 접근했을 때, 해당 페이지가 논리적으로는 존재하나 실제 물리 메모리에 로딩되지 않은 경우이다. 
1. 요청한 메모리 페이지가 정당한 요청인지 확인한다.
2. Page table을 확인하여 Page fault인지 확인한다.
3. Trap을 발생시켜 해당 명령어의 수행을 중지시킨다. Page fault를 해결하는 동안 다른 프로세스를 실행시킨다.
4. Physical memory에서 가용한 Free frame을 찾는다. 이 때 가용한 Free frame이 없다면 swap하여 만든다.
5. 디스크로부터 데이터를 로딩하여 해당 Frame에 저장한다. (swap in) 저장을 완료하면 Disk I/O subsystem이 OS에게 interrupt를 보내준다.
6. 페이지 테이블에 해당 페이지가 몇 번 프레임에 저장되었는지와 valid bit를 1로 변경하여 저장한다.
7. 중지시켰던 명령어를 수행한다.

## 용어
* Frame: physical memory의 최소 단위
* Swap-out: 메모리가 가득 찼을 때, 일시적으로 특정 페이지를 디스크로 보내는 것
* Swap-in: 디스크에 백업했던 페이지를 프로세스에 요청해서 다시 메모리로 불러들이는 것


## References
* 가상 메모리(virtual memory) - https://brownbears.tistory.com/47
* Swap이란? - https://it-serial.tistory.com/53
* Demand Paging - https://bubble-dev.tistory.com/entry/Demand-paging
* 페이지 테이블이란? Page Table 원리와 역할 - https://jhnyang.tistory.com/443
* Paging and Page Tables - https://velog.io/@jieuni/Paging-and-Page-Tables

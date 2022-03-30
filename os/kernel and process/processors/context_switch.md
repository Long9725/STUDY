## 목차

1. [Context switch란?](#context-switch란)
2. [Context란?](#context란)
3. [Pseudocode](#pseudocode)
4. [Cost](#cost)
5. [References](#references)

## Context switch란?
멀티프로세스 환경에서 CPU가 어떤 하나의 프로세스를 실행하고 있는 도중, 인터럽트 요청에 의해 다음 우선 순위의 프로세스가 실행되어야 할 때 발생하는 작업이다. \
기존의 프로세스 또는 레지스터 값(Context)을 저장하고, CPU가 다음 프로세스를 수행하도록 새로운 프로세스의 상태 또는 레지스터 값을 교체한다. \
Context switching을 하는 동안 CPU는 프로세스에 관해 아무런 일을 하지 못한다. 따라서 잦아지면 Context switching을 하기 위한 코드 실행 횟수가 많아지기에, 오히려 오버헤드가 발생해 성능이 떨어진다.

## Context란?
사용자와 다른 사용자, 사용자와 시스템 또는 디바이스 간 상호작용에 영향을 미치는 사람, 장소, 개채 등의 현재 상태를 규정하는 정보를 의미한다. \
OS에서의 Context는 해당 프로세스를 실행하기 위한 프로세스의 정보들이다. PCB에 저장된다. 

![](../../image/process/context%20switch.png)

## Pseudocode
```
context_switch(old, new) {
    int in_progress = 0;
    save_context(old);
    if (in_progress == 1) return;
    else in_progress = 1;
    restore_context(new);
}

yield() {
    pid_t old, new;
    old = current_pid();
    new = schedule();
    context_switch(old, new);
}

void main() {
    int i = 10;
    yield();

    i = 20;
    yield();
}
```
## Cost
* Cache 초기화
* Memory mapping 초기화
* Kernel은 항상 실행

## References
* wiki - https://ko.wikipedia.org/wiki/%EC%9D%B8%ED%84%B0%EB%9F%BD%ED%8A%B8
* OS - Context Switch(컨텍스트 스위치)가 무엇인가? - https://jeong-pro.tistory.com/93
* Context switch란? - https://nesoy.github.io/articles/2018-11/Context-Switching
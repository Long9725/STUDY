## 목차

1. [Simple state management](#simple-state-management)
2. [Responsive state management](#responsive-state-management)
3. [Lifecycle](#lifecycle)
4. [Find](#find)
5. [IsRegistered](#isregistered)
6. [static get to pattern](#static-get-to-pattern)
7. [References](#references)

## Simple state management
단순 상태 관리로 GetxController class와 update() 함수를 사용한다. 상태값 변경 이후에 update()를 사용하면 화면 갱신이 일어나며, 사용하지 않으면 상태값만 변경된다. 따라서 StatefulWidget를 사용할 필요성을 줄여준다. 
~~~dart
class MyController extends GetxController {
  ...
  void increment() {
    count++;
    update(); // count 1 증가 이후, 화면 갱신
  }
}
~~~

사용할 위젯에서 Get.put method를 통해 controller를 등록해준다.

~~~dart
final controller = Get.put(MyController());
~~~

상태의 변화를 감지하고 변경된 상태값의 적용을 위해서 GetBuilder를 사용한다. 사용하지 않으면 상태 변경을 인지하지 못하며, 화면에도 반영할 수 없다. update() 함수를 통해 직접 통보한다.
~~~dart
GetBuilder<MyController>(builder:(controller) {
    return Text('${controller.count}';)
}),
~~~
현재 여기까지의 내용은 Provider 패턴에서 비슷하다는 생각이 든다.
~~~dart
class MyProvider extends ChangeNotifier {
    ...
    void increment() {
        count++;
        notifyListener();
    }
}
~~~
~~~dart
final provider = context.watch<MyProvider>();
...
Text('${provider.count}')
~~~

## Responsive state management
Simple state management와는 달리 내부 로직으로 값의 상태 변화를 감지하고 화면에 변경된 값을 적용한다. 변수명.obs를 사용하며 일반적인 변수명이 아닌 Rx 변수가 된다.
~~~dart
class MyController extends GetxController {
  final count = 0.obs; // RxInt count = 0.abs;

  void increment() {
    count.value++; // count의 값 1 증가 이후 화면 갱신
    // count(count.value + 1); 과 같다.
  }
}
~~~
이를 다음처럼 사용한다.
~~~dart
final controller = Get.put(MyController());
...
Obx(
    () => Text(
        '${controller.count.value}'
    )
)

~~~

## LifeCycle
StatefulWidget의 initState(), dispose()와 같은 위젯의 라이프 사이클 함수처럼 GetxController에서도 사용 가능한 라이플 사이클 함수가 있다.
~~~dart
class MyController extends GetxController {
    // initState(), 컨트롤러가 생성될 때 호출된다.
    @override
    void onInit() {
        super.onInit();
    }
    
    // dispose(), 컨트롤러가 더이상 필요없어져 메모리에서 제거될 때 호출된다.
    @override
    void onClose() {
        super.onClose();
    }
}
~~~

## Worker
반응형 상태 값의 변화가 발생하였을 때, 이를 감지하고 특정 콜백 함수를 호출한다. 컨트롤러 혹은 클래스가 생성될 때만 사용할 수 있다.
+ Controller의 onInit()
+ StatefulWidget의 initState()
+ 클래스 생성자
Worker의 함수에는 다음과 같은 종류가 있다.
~~~dart
// 반응형 상태값이 변경될 때마다 호출된다.
ever(Rx variable, (_) => callback function);

// 반응형 상태값이 최초로 변경될 때 한 번만 호출된다.
once(Rx variable, (_) => callback function);

// 마지막 변경 이후 특정 시간 동안 변경이 없으면 호출된다.
debounce(Rx variable, (_) => callback function, time: Duration());

// 반응형 상태값이 변경되는 동안, 일정 간격으로 호출된다.
interval(Rx variable, (_) => callback function. time: Duration());
~~~

### Debouncing
디바운싱이란 어설프게 타이머를 삽입해 모든 타이머스레드를 진행한 것과 다르게,
타이머 다 가기 전 상위의 행동이 바뀌면 해당 스레드의 타이머와 그 뒤의 콜백들이 없어지는 역할을 한다.

## Find
GetX의 상태 값을 사용하기 위한 또 다른 방법이다. 먼저 컨트롤러를 Get.put으로 등록해야 다음처럼 사용할 수 있다. 만약 등록하지 않으면 에러가 발생한다.
~~~dart
Get.find<MyController>()
~~~
~~~dart
Obx(
    () => Text(
        '${Get.find<MyController>().count.value}'
    )
)
~~~
Provider 패턴에서 다음과 비슷하다는 생각이 든다.
~~~dart
Text('${context.watch<MyProvider>().count}')
~~~

## isRegistered
Get.find는 Get.put으로 등록된 컨트롤러만 사용할 수 있기에, 에러 방지를 위해서 isRegistered로 검사한다. 사용하고자 하는 컨트롤러가 등록되었는지 확인해보고 등록되었다면 true, 아니면 false를 반환한다.
~~~dart
Get.isRegistered<MyController>()
~~~

## static get to pattern
Get.find를 사용하여 상태 값에 자주 접근하게 되므로, 다음과 같은 패턴을 이용한다.
~~~dart
class MyController extends GetxController {
    static MyController get to => Get.find<MyController>();
    ...

}
~~~
~~~dart
Obx(
    () => Text(
        '${MyController.to.count.value}'
    )
)
~~~

## References
* 『프로그래밍 예술가, DeKu』 - https://dev-yakuza.posstree.com/ko/flutter/getx/state/
* 자동차명 insane_인생 - https://zionh.tistory.com/155
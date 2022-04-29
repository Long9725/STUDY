## 목차

1. [애자일 프로세스](#애자일-프로세스)
2. [Simple state management](#simple-state-management)
3. [Responsive state management](#responsive-state-management)
4. [Lifecycle](#lifecycle)
5. [Find](#find)
6. [IsRegistered](#isregistered)
7. [static get to pattern](#static-get-to-pattern)
8. [References](#references)

## Route
기본적으로 Get.to(), Get.back()을 통해 화면을 이동한다.

## Named route
Route 관리를 위해서 각각 이름을 붙인다. 처음 앱을 실행했을 때, 표시될 첫 화면의 이름을 initialRoute로 지정한다. 이후 GetPage(name: name, page: page)를 통하여 각 Route의 이름을 설정한다. Flutter는 웹에서도 사용 가능하기 때문에 URL 형식을 사용한다. 페이지 이동은 Get.toNamed(page name)을 통해서 이동한다.

~~~dart
...
@override
Widget build(BuildContext context) {
    return GetMaterialApp(
        title: 'Flutter Demo',
        theme: ThemeData(
            primarySwatch: Colors.blue,
        ),
        initialRoute: '/',
        getPages: [
            GetPage(name: '/', page: () => const MyHomePage()),
            GetPage(name: '/second', page: () => const Second()),
        ],
    );
}
...
~~~
~~~dart
Get.toNamed('/second')
~~~

## Arguments 전달
화면을 이동할 때, 다음처럼 parameters를 전달할 수 있다. dynamic 타입으로 모든 변수를 전달할 수 있다.

~~~dart
Get.toNamed("/second", arguments: "Hello");
~~~

전달한 parameters는 다음처럼 접근하여 사용한다.

~~~dart
Get.arguments
~~~

URL 형식도 가능하기에 URL parameters 형식으로 전달할 수도 있다.

~~~dart
getPages: [
            GetPage(name: '/', page: () => const MyHomePage()),
            GetPage(name: '/second/:id', page: () => const Second()),
        ],
...

Get.toNamed("/second/1?name=hello")

...

Get.parameters["id"]
Get.parameters["name"]
~~~

## 화면 이동 방법 & 애니메이션

https://dev-yakuza.posstree.com/ko/flutter/getx/route/ 전체 함수는 참고

애니메이션은 다음과 같이 추가한다.

~~~dart
getPages: [
            GetPage(name: '/', page: () => const MyHomePage()),
            GetPage(
                name: '/second/:id', 
                page: () => const Second(), 
                transition: Transition.leftToRight, 
                transitionDuration: const Duration(milliseconds: 400), 
                curve: Curves.fastOutSlowIn
            ),
        ],
~~~

## 스와이프하여 뒤로가기
popGesture이 true인 경우, 스와이프하여 뒤로 가기 기능을 사용할 수 있다. false인 경우 사용할 수 없다.
~~~dart
GetPage(
    name: '/second/:id', 
    page: () => const Second(),
    popGesture: true,
),
~~~

GetX에서는 다음과 같이 이전 화면이 무엇인지 알 수 있다.
~~~dart
Get.previousRoute
~~~

## References
* 『프로그래밍 예술가, DeKu』 - https://dev-yakuza.posstree.com/ko/flutter/getx/route/
* 자동차명 insane_인생 - https://zionh.tistory.com/155
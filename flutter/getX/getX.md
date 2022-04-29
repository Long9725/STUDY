1. [애자일 프로세스](#애자일-프로세스)
2. [Simple state management](#simple-state-management)
3. [Responsive state management](#responsive-state-management)
4. [Lifecycle](#lifecycle)
5. [Find](#find)
6. [IsRegistered](#isregistered)
7. [static get to pattern](#static-get-to-pattern)
8. [References](#references)

## GetX
Flutter의 상태 관리 패키지이다. Route, 다국어 지원, 화면 크기, API 호출 기능 등 다양한 기능을 제공한다.

플러그인: https://pub.dev/packages/get

## GetMaterialApp
GetX 기능을 사용하기 위해서는 MaterialApp 대신에 GetMaterialApp을 사용해야 한다.
~~~dart
...
@override
Widget build(BuildContext context) {
  return GetMaterialApp(
    title: 'Flutter Demo',
    theme: ThemeData(
      primarySwatch: Colors.blue,
    ),
    home: const MyHomePage(),
  );
}
...
~~~

## References
* 『프로그래밍 예술가, DeKu』 - https://dev-yakuza.posstree.com/ko/flutter/getx/state/
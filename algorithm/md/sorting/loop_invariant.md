# Loop invariant

## 정의
루프 불변성, 알고리즘의 루프 안에서 항상 참이 되는 일련의 구문들이다. 알고리즘의 상태는 항상 변하지만, loop invariant는 상태에 상관 없이 참이다.

## 증명
수학적 귀납법을 이용하여 종종 증명한다.

1. Initialization : 첫 반복과 초기 조건 전에 루프 불변성이 참이어야 한다.
2. Maintenance : 루프 반복 전에 참이었다면 다음 루프 시작 전까지 계속 참이어야 한다.
3. Termination : 루프가 끝날 때 불변성이 알고리즘의 타당성을 보이는데 도움이 될 유용한 특성을 가져야 한다.
* 너무 쉬운 조건이나 너무 강력한 조건의 loop invariant은 피하자.

## Reference
https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=ryutuna&logNo=100123255308
https://medium.com/@lsrock125/%EB%A3%A8%ED%94%84-%EB%B6%88%EB%B3%80%EC%84%B1-6ca7b3128ee4
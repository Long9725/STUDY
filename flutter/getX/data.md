## 목차

1. [Route](#route)
2. [Named route](#named-route)
3. [Arguments 전달](#arguments-전달)
4. [화면 이동 방법 & 애니메이션](#화면-이동-방법--애니메이션)
5. [스와이프하여 뒤로가기](#스와이프하여-뒤로가기)
6. [IsRegistered](#isregistered)
8. [References](#references)

## Data
데이터와 관련된 파일들을 모아놓는 폴더이다. Provider, Model, Repository 등이 포함되는 폴더이다. 여기서의 Provider는 Provider pattern과는 다르다.

## Provider
API 통신 혹은 DB에 접근한다. 단일 파일로 관리해도 되지만, 요청이 많을 경우에는 Entity 별로 분류해서 작성하는 것도 선택할 수 있다.

## Model
데이터 모델이다. API 작업을 할 때, json 변환 메소드를 포함한다.

## Repository
Entity를 분리한다. DB의 테이블 모델을 가져와, 앱에서 사용하는 모델로 변환하는 과정을 포함한다. Controller와 Data 사이를 연결하는 역할을 맡는다.


## References
* leeeeeoy.log - https://velog.io/@leeeeeoy/Flutter-GetXpattern-%EC%9D%B5%ED%98%80%EB%B3%B4%EA%B8%B0
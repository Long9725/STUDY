## 목차

1. [논리적 설계](#논리적-설계)
2. [규칙](#규칙)
3. [복합 및 유도 속성](#복합-및-유도-속성)
4. [일반화 관계](#일반화-관계)
5. [테이블 명세서 작성](#테이블-명세서-작성)
6. [References](#references)

## 물리적 설계
DBMS로 구현 가능한 물리적 구조를 설계한다. 하드웨어나 운영체제의 특성을 고려하여 필요한 인덱스 구조나 내부 저장 구조 등에 대한 물리적인 구조를 설계한다. 결과물은 물리적 스키마이다.
+ 성능, 보안 그리고 편의성을 위해 필요한 경우 뷰를 생성한다.
+ 인덱스를 생성한다.
+ 내부 자동 생성 열 추가
    + 필요한 경우, 기본키를 대신하는 내부키를 추가한다.
    + 내부키 값은 DBMS에 의해 자동 생성되는 값으로 각 투플을 식별한다.
    + 보통 기본키가 많은 열로 구성된 복합키이거나 기본키 값의 크기가 커서 빈번한 비교 검색에 따른 성능 저하가 우려될 때, 내부키 열을 고려한다.

## 구현
SQL로 작성한 명령문을 DBMS에서 실행하여 데이터베이스를 실제로 생성한다.

## References
* 2022 봄 데이터베이스 강의
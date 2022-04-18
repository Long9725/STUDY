## 목차

1. [삽입 SQL이란?](#삽입-SQL이란)
2. [커서](#커서)
3. [References](#references)

## 삽입 SQL이란?
Embedded SQL(ESQL), 프로그래밍 언어로 작성된 응용 프로그램 안에 삽입하여 사용하는 SQL 문이다. 

    EXEC SQL (SQL 문);
    
    EXEC SQL BEGIN DECLARE SECTION;
        (code)
    EXEC SQL END DECLARE SECTION;

+ 프로그램 안에서 일반 명령문이 위치할 수 있는 곳이면 어디든 삽입 가능하다.
+ 일반 명령문과 구별하기 위해 삽입 SQL 문 앞에 EXEC SQL을 붙인다.
+ 프로그램에 선언된 일반 변수를 SQL 문에서 사용할 때는 이름 앞에 :를 붙여서 구분한다.

+ BEGIN DECLARE SECTION과 END DECLARE SECTION 사이에 사용할 변수를 선언한다.


## 커서
Cursor, 수행 결과로 반환되는 여러 행을 한 번에 하나씩 가리키는 포인터이다. SELECT 문을 프로그램에서 사용할 때 필요하다.

    EXEC SQL DECLARE 커서_이름 CURSOR FOR SELECT 문;

    EXEC SQL OPEN 커서_이름;

    EXEC SQL FETCH 커서_이름 INTO 변수_리스트;

    EXEC SQL CLOSE 커서_이름;

+ 커서를 사용하기 전에 커서의 이름과 커서가 필요한 SELECT 문을 선언한다.
+ OPEN 문을 통해 커서에 연결된 SELECT 문을 실행한다.
+ FETCH 문을 통해 커서를 이동하여 다음 행을 가리키도록 한다. 이 행으로부터 속성 값을 가져와 변수에 저장한다.
    + 결과 테이블에는 여러 행이 존재하므로 FETCH 문은 여러 번 수행해야 한다.
+ 커서가 필요 없는 삽입 SQL
    + CREATE TABLE 문, INSERT 문, DELETE 문, UPDATE 문
    + 결과로 행 하나만 반환하는 SELECT 문



## References
* 2022 봄 데이터베이스 강의
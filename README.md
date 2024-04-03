# 데이터베이스 프로그램
이 프로그램은 데이터베이스를 관리하고 상호작용할 수 있는 간단한 CLI(Command Line Interface) 도구입니다.
사용자는 명령어 (list, add, get, del, exit) 를 입력하여 데이터베이스에 항목을 추가하거나 가져오거나 삭제할 수 있습니다.
이 프로젝트에는 main.cpp, util.cpp, database.cpp, database.h 네 개의 파일이 포함되어 있습니다.

## 파일 구성
### main.cpp
* main(): 데이터 베이스 프로그램을 전체적으로 동작시킵니다.
### util.cpp
* get_command(): 커맨드의 종류를 출력합니다.
* print_error(): 에러 메세지를 출력합니다. code 1 - 잘못된 입력, code 2 - 값을 찾을 수 없음.
* print_array(): 배열 관련 함수(1) 배열을 출력합니다.
* make_array(): 배열 관련 함수(2) 배열을 만듭니다.
* print_list(): list 명령어.
* add_entry(): add 명령어.
* get_entry(): get 명령어.
* del_entry(): del 명령어.
### database.cpp
 - 위 파일은 database.h 을 구성한 것으로 자세한 코드는 database.h 에서 확인할 수 있습니다.
* destroy(): 프로그램 종료 시 동적 할당한 개체를 delete 합니다.
### database.h

## 실행 방법
프로젝트를 다운로드하고 소스 코드를 가져옵니다.
컴파일러가 C++11 이상을 지원하는지 확인합니다.
미리 작성한 Makefile을 통해 실행하므로, Mingw를 설치했는지 확인합니다.
* 본 프로그램에서는 mingw32-make를 사용했습니다.

```
git clone https://github.com/leebarang/cpp-week4.git database 
cd database

mingw32-make # make
./main.exe
```

## 실행 예시
command (list, add, get, del, exit): add   
key: 1   
type (int, double, string, array): int   
value: 100   
   
command (list, add, get, del, exit): list   
1: 100   

command (list, add, get, del, exit): exit   

## 주의사항
이 프로젝트는 동적 할당으로 이론상 무한한 값을 저장할 수 있으나, 각 속성 배열의 최대 크기 등은
넘을 수 없습니다. 이 프로그램의 동작의 최적의 효율성이 고려되지 않았으므로 프로그램 동작 속도가
항상 최적화 되어있지 않을 수 있습니다.

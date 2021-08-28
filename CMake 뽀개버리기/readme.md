
# CMake 뽀개버리기 진행 노트

## 진행 계획

진행 및 일정 조율을 위한 연락처

* 박동하 luncliff@gmail.com
* 김정택 kjtkjt21@gmail.com

### 학습 시간

* 주 1회, 2021년 7월 10일부터 7주 동안 진행
* 매 주 토요일 03:00 PM ~ 04:30 PM (1시간 30분)

[Google Calendar Event: "CMake 뽀개버리기(C++ Korea 2021)"](https://calendar.google.com/event?action=TEMPLATE&tmeid=MWltZmM0bXV0NmVlM3VwZjVrbzZ0NHY1azBfMjAyMTA3MTdUMDYwMDAwWiBsdW5jbGlmZkBt&tmsrc=luncliff%40gmail.com&scp=ALL)

### 학습 목표

참가자들이 주로 타인이 작성한 내용을 읽고, 쓰는 방법에 익숙해지는 것입니다

시간적인 한계로 모든 플랫폼에서 CMake를 다루는 방법을 설명하지는 않습니다.
CMake를 사용하기 위해 알아야 하는 용어를 먼저 살펴본 후,
공식 문서의 내용, 출력되는 메시지에 대한 해석 등을 함께 다룹니다.

## 학습 내용

### [1. 빌드 시스템에 대한 시야 가지기](./ch1.md)

C++ 프로젝트의 빌드에 영향을 미치는 요인들을 분석합니다.
CMake가 빌드 시스템 전체에서 어떤 역할을 수행하는지 이해합니다.

1. 기본 연습 환경 구성 
1. CMake CLI 살펴보기
1. CMake Target
1. CMake Command
1. CMake Variable
1. CMake Cache

### [2. CMakeLists.txt 읽고쓰기](./ch2.md)

CMakeLists.txt가 어떤 내용으로 구성되어있는지 읽을 수 있도록 지식을 넓힙니다.
CMake 고유 문법의 기초적인 부분과, 먼저 알아야 하는 개념들을 다룹니다.

1. Build Target, Custom Target
1. Command
1. CMake 문서 읽는 방법 - 1
1. 알려진 변수들, 패턴, 표현식
1. 오류 메시지 이해하기 - 1

### [3. CMake 프로젝트의 Test, Import](./ch3.md)

프로젝트가 어떻게 검증되는지, 다른 프로젝트와 연결하기 위해선 어떤 내용이 필요한지 다룹니다.

1. CTest
1. 용어 - CMake Package
1. Export 하기
1. Imported Target
1. CMake 문서 읽는 방법 - 2
1. Target Property

### [4. CMake Script 작성하기](./ch4.md)

빌드 설정과 절차를 분할하는 방법에 대해 다룹니다

1. CMake Function
1. CMake Macro
1. Built-in 스크립트 (.cmake)
1. CMake 설치 후에 스크립트들의 위치 찾기
    * Header, Library 찾기
    * FindXXX.cmake
    * 툴체인 (toolchain.cmake)
      https://github.com/leetal/ios-cmake ios.toolchain.cmake
1. CMake 문서 읽는 방법 - 3
1. 오류 메시지 이해하기 - 2

### [5. 빌드 구조 분석과 평가](./ch5.md)

여러 오픈소스 라이브러리들의 빌드 설정과 절차를 분석해봅니다

1. CMake를 사용하는 라이브러리들을 blame
   * Header only
   * Static
   * Dynamic
1. ~~C++ 20 Modules (CMake 기능 지원 확인 중)~~
1. 오류 메시지 이해하기 - 3

### [6. 소스 코드, 패키징, 의존성 관리](./ch6.md)

프로젝트의 소스코드를 조직화하고, 빌드 결과물을 패키징 하는 과정을 다룹니다
외부 의존성을 관리하는 방법도 함께 살펴봅니다.

1. 파일트리 관리
1. 프로젝트 레벨
1. ~~프로젝트 간의 충돌 상황 만들어보기~~
1. CPack
1. Conan 패키지 매니저
    * conanfile 작성
    * Conan에서 생성하는 CMake 스크립트 분석
1. ~~pkg-config~~

### [7. Cross Compile 프로젝트의 빌드 설계](./ch7.md)

Native 빌드와 Cross 빌드의 차이점에 대해서 다룹니다.

1. Android NDK - Gradle, Android Gradle Plugin
1. Apple 플랫폼 (iOS)
1. 오류 메시지 이해하기 - 4

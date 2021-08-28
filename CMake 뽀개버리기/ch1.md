# 빌드 시스템에 대한 시야 가지기

### 참고자료

* CMake
  * https://cmake.org/cmake/help/latest/guide/tutorial/index.html
  * https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html
* [CMake 할때 쪼오오금 도움이 되는 문서](https://gist.github.com/luncliff/6e2d4eb7ca29a0afd5b592f72b80cb5c)
* C++ Korea 7회 세미나 - [Practical(현실적인) CMake](https://youtu.be/wnBRg5c5-bk?t=5379) [PDF](https://github.com/CppKorea/Seminars/tree/main/200725%20-%207th%20Seminar/2%20-%20현실적인(Practical)%20CMake) [PPT](https://1drv.ms/p/s!AvzH7Qt0Bc-Uia1b_0M137cl_BuBtA?e=yg2JKw)

#### 참고자료의 참고자료(?)

* CGold - https://cgold.readthedocs.io/en/latest/
* An Introduction to Modern CMake - https://cliutils.gitlab.io/modern-cmake/
* [C++Now 2017: Daniel Pfeifer "Effective CMake"](https://www.youtube.com/watch?v=bsXLMQ6WgIk)

## 스터디 노트

### 빌드의 구성 요소들

* 소스코드
    * VCS (Version Control System)
    * 권한 관리
* 빌드 도구
    * Codegen
    * Compiler, Linker
    * Packaging
* 빌드 머신 / 환경
    * Operating System
    * SDK (library, toolset, etc.)
    * 빌드 시점의 환경변수

#### 빌드 시스템과 과정에 대한 평가

시스템 전체를 여러가지 기준을 가지고 평가해볼 수 있습니다.
보통 2가지를 중요하게 생각합니다.

##### 편의성

"빌드 환경과 도구가 개발과정을 얼마나 돕고 있는가?"

* 도구들을 쉽게 설치할 수 있는가?
* SDK의 갱신 방법이 복잡하지는 않은가?
* 빌드를 다변적으로 수행할 수 있는가?

##### 정확성(투명성)

"빌드 과정에 문제가 발생했을 때 원인을 파악하기 쉬운가?"

* 빌드 머신과 타겟 머신의 상이한 부분들이 잘 드러나는가?
* 같은 SDK의 여러 버전을 설치한 경우

#### 절차 설계

```
[ 소스 파일 -> 오브젝트 파일 ]+ -> 프로그램
[ 프로그램, 리소스, 메타 파일 ]+ -> 패키지
```

여기서 말하는 "패키지"는 "배포의 단위"라는 의미로 사용되었습니다.

배포: 타겟 머신이나 저장소로 전송하는 행위

Delivery? Deployment?

#### CMake의 역할

[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)을 보면 어디까지 가능한지 확인할 수 있습니다.

### 기본 연습 환경 구성

### CMake CLI 살펴보기

#### 버전 확인

```console
$ cmake --version
# ...
```

#### 위치 찾기

```ps1
Get-Command cmake
```

```bash
which cmake
```

#### 기본 구조

Source 폴더와 Build 폴더가 분리되어 있는 구조.

```console
$ cmake --help
Usage

  cmake [options] <path-to-source>
  cmake [options] <path-to-existing-build>
  cmake [options] -S <path-to-source> -B <path-to-build>

...
```

같은 폴더에서 동작시키는 것은 소스 폴더를 지저분하게 만들 수 있습니다.
[gitignore.io](https://www.toptal.com/developers/gitignore)에서 CMake 관련파일들을 무시하도록 필터링 목록를 만들어 쓰는것을 권장.

```
cmake --debug-output
```

### [CMake Target](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html)

Target은 빌드 설정을 관리하는 단위. 

'빌드 설정'이라고 하면 떠오르는 것들?

#### Unix Makefiles와 CMake의 차이?

Makefile은 파일 단위로 작성. https://github.com/axboe/liburing/blob/master/src/Makefile

```makefile
liburing_srcs := setup.c queue.c syscall.c register.c

liburing_objs := $(patsubst %.c,%.ol,$(liburing_srcs))
liburing_sobjs := $(patsubst %.c,%.os,$(liburing_srcs))

$(liburing_objs) $(liburing_sobjs): include/liburing/io_uring.h

%.os: %.c
	$(QUIET_CC)$(CC) $(CPPFLAGS) $(SO_CFLAGS) -c -o $@ $<

%.ol: %.c
	$(QUIET_CC)$(CC) $(CPPFLAGS) $(L_CFLAGS) -c -o $@ $<

# ...
liburing.a: $(liburing_objs)
	@rm -f liburing.a
	$(QUIET_AR)$(AR) r liburing.a $^
	$(QUIET_RANLIB)$(RANLIB) liburing.a

```

CMake에서는 Target 단위로 작성. https://github.com/pytorch/FBGEMM/blob/master/CMakeLists.txt

```cmake
add_library(fbgemm_generic OBJECT ${FBGEMM_GENERIC_SRCS})
add_library(fbgemm_avx2 OBJECT ${FBGEMM_AVX2_SRCS} ${FBGEMM_AVX2_INLINE_SRCS})
add_library(fbgemm_avx512 OBJECT
  ${FBGEMM_AVX512_SRCS} ${FBGEMM_AVX512_INLINE_SRCS})
# ...

if(FBGEMM_LIBRARY_TYPE STREQUAL "default")
  add_library(fbgemm
    $<TARGET_OBJECTS:fbgemm_generic>
    $<TARGET_OBJECTS:fbgemm_avx2>
    $<TARGET_OBJECTS:fbgemm_avx512>)
# ...
```

### [CMake Command](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html)

크게 3가지 종류로 구성. Scripting, Project, CTest. 
이번 시간에는 몇가지만 살펴보고 사용법에 대해서는 다음 시간에 확안

#### Scripting

* [`cmake_minimum_required`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html)
* [`find_file`](https://cmake.org/cmake/help/latest/command/find_file.html)
* [`message`](https://cmake.org/cmake/help/latest/command/message.html)
* ...

#### Project

* [`project`](https://cmake.org/cmake/help/latest/command/project.html)
* [`enable_language`](https://cmake.org/cmake/help/latest/command/enable_language.html)
* [`add_executable`](https://cmake.org/cmake/help/latest/command/add_executable.html)
* [`target_sources`](https://cmake.org/cmake/help/latest/command/target_sources.html)
* ...


### CMake Variable / CMake Cache

CGold에서 확인 https://cgold.readthedocs.io/en/latest/


# CMake Script 작성하기

### 참고자료

* CMake
    * [Modules](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html)
    * [Toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#introduction)
    * cmake-language: [Organization](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#organization)
* CMake [`find_package`](https://cmake.org/cmake/help/latest/command/find_package.html)
    * [FindThreads.cmake](https://cmake.org/cmake/help/latest/module/FindThreads.html)
* [CppCon 2017: Mathieu Ropert "Using Modern CMake Patterns to Enforce a Good Modular Design"](https://www.youtube.com/watch?v=H14CSWkLGUY)  
  [Channel 9 GoingNative](https://channel9.msdn.com/events/GoingNative/CppCon-2017/046?term=cmake&lang-en=true)

## 스터디 노트

오늘은 .cmake 파일을 작성하기 위해 알아야 하는 내용들을 중심으로 다뤄보겠습니다.

### [용어](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#organization)

내용을 좀 요약해보자면...

* Directory `CMakeLists.txt`  
  소스코드 관리 및 Build system 파일 생성
* Scripts `<script>.cmake`  
  CMake CLI를 통해 사용하는 것을 전제로 한 파일들. Build Target 정의를 작성하지 않기 때문에, 실행해도 Build system 파일이 생성되지 않는다.
* Modules `<module>.cmake`
  프로젝트에서 사용하는 

### 정돈된 CMake command

CMake command 중에는 [`function/endfunction`](https://cmake.org/cmake/help/latest/command/function.html)과 [`macro/endmacro`](https://cmake.org/cmake/help/latest/command/macro.html)가 있습니다.
이 둘은 case-insensitive 하다는 공통점이 있습니다.
[차이점에 대한 CMake의 설명](https://cmake.org/cmake/help/latest/command/macro.html#macro-vs-function)을 먼저 본 뒤에, 어떻게 작성하는지 가볍게 살펴보겠습니다.

#### Function

```cmake
function(...)
    message(STATUS "argc: ${ARGC}") # https://cmake.org/cmake/help/latest/command/function.html#arguments
    message(STATUS "argv: ${ARGV}")
    return()
endfunction()
```

간단한 function을 작성하자면 이런 식입니다.

```cmake
function(print_folders LABEL DIRS)
    list(LENGTH DIRS length)
    if(NOT length)
        return()
    endif()
    message(STATUS "  ${LABEL}:")
    foreach(name ${DIRS})
        message(STATUS "    - ${name}")
    endforeach()
endfunction()
```

위와 같이 작성한 function은 아래처럼 사용할 수 있습니다.

```cmake
message(STATUS "CMAKE_SYSTEM_INCLUDE_PATH:")
print_folders("include" ${CMAKE_SYSTEM_INCLUDE_PATH})
```

#### Macro

Function에 비해 Macro는 보다 제한된 영역에서, 특정한 CMake 변수들을 대상으로 사용하는 느낌이 강합니다. 

```cmake
macro(print_XXX)
    message(STATUS "XXX: ${XXX}")
endmacro()

print_XXX()
set(XXX 1234)
print_xxx()
```

Macro 중에서 종종 볼 수 있는 것 중 하나가 [find_dependency](https://cmake.org/cmake/help/latest/module/CMakeFindDependencyMacro.html)입니다.

```cmake
include(CMakeFindDependencyMacro)
find_dependency(OpenSSL [...])
```

### [Built-in .cmake 파일](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html) - Utility

Build Target을 생성하는데 사용하는 `target_*` command들이 전처리-컴파일-링킹을 표현하하던 것을 기억하시나요?
그 형태와 지금 부터 다뤄볼 CMake 모듈들의 용례를 비교하면서 공부하시면 좋을 것 같습니다

아래의 CLI 옵션을 써서 결과를 확인하는 것도 같이 하면서요.
```
cmake --debug-output
```

#### [CheckCXXCompilerFlag](https://cmake.org/cmake/help/latest/module/CheckCXXCompilerFlag.html)

먼저 컴파일러 입니다.

```cmake
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-march=native supports_native_arch)
```

#### [CheckIncludeFileCXX](https://cmake.org/cmake/help/latest/module/CheckIncludeFileCXX.html)

헤더 파일을 검사할 일이 없으면 좋겠지만, 가끔은 필요한 경우가 있죠.

```cmake
include(CheckIncludeFileCXX)

list(APPEND CMAKE_REQUIRED_FLAGS "...")
check_include_file_cxx("sys/stat.h" found_sys_stat)
```

#### [CheckCXXSymbolExists](https://cmake.org/cmake/help/latest/module/CheckSymbolExists.html)

이 모듈은 Macro, Function을 찾을 때 사용합니다.

```cmake
include(CheckCXXSymbolExists)

list(APPEND CMAKE_REQUIRED_FLAGS "...")
list(APPEND CMAKE_REQUIRED_INCLUDES "...")
check_cxx_symbol_exists(... "...h" have_symbol)
```

### [Built-in FindXXX.cmake](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html#find-modules)

물론 위와 같은 Utility만 있는 것은 아닙니다.

보통 FindXXX.cmake형태로 작성된 모듈들은 [`find_package`의 Module 모드](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature-and-module-mode)를 위해서 작성된 경우입니다.

따라서 앞서와 같이 include를 하는 것 보다는,

```cmake
include(FindThreads) # Bad & ambiguous
```

아래와 같이 사용하는 것을 상정하고 있습니다.

```cmake
find_package(Threads) # Threads::Threads
```

지금 언급한 [FindThreads](https://cmake.org/cmake/help/latest/module/FindThreads.html) 부터 시작해서, CMake에서 어떤 패턴을 가지고 작성하였는지 확인해보겠습니다.

#### [FindPkgConfig](https://cmake.org/cmake/help/latest/module/FindPkgConfig.html)

프로젝트 의존성을 관리할 때 사용하는 여러 도구들 중 하나로 `pkg-config`가 있습니다.
CMake에서도 이 모듈을 사용하면 .pc 파일을 재사용할 수 있습니다.
꽤 오래전부터 있던 모듈이지만, 개인적으로는 Imported Taget들은 프로젝트 전체에서 사용할 수 있도록 해주는 GLOBAL 옵션이 사용할 수 있도록 3.15 버전 이상을 권합니다.

```cmake
cmake_minimum_required(VERSION 3.15)
find_package(PkgConfig REQUIRED)
```

`PkgConfig::` 네임스페이스에 module spec에 사용한 target 이름이 추가됩니다.
간단히 `target_link_libraries`를 하는 것으로 import를 마칠 수 있습니다.

```cmake
pkg_check_modules(liburing REQUIRED IMPORTED_TARGET GLOBAL liburing>=2.0)
    
target_link_libraries(main
PRIVATE
    PkgConfig::liburing
)
```

#### [FindPNG](https://cmake.org/cmake/help/latest/module/FindPNG.html)

간단히 libpng를 찾는것 부터 시작해보겠습니다.

```cmake
find_package(PNG)
```

CMake 문서를 보면, Imported Targets, Result variables가 있는 것을 볼 수 있습니다.
만약 아래와 같은 상황이라면 Result variables의 결과가 달라지는 경우가 있을까요?

```cmake
# CMakeLists.txt
find_package(PNG)
add_subdirectory(sub1)
```

```cmake
# sub1/CMakeLists.txt
find_package(PNG)
```

혹은 그 순서가 반대라면 어떨까요?

```cmake
# CMakeLists.txt
add_subdirectory(sub1)
find_package(PNG)
```

#### [FindPython3](https://cmake.org/cmake/help/latest/module/FindPython3.html)

개발자 생태계의 큰 부분을 지탱하고 있는 언어를 물으면 많은 분들이 Python3를 언급하실 겁니다. [CMake 또한 PIP(Package Installer for Python)로 설치가 가능합니다](https://cmake-python-distributions.readthedocs.io/en/latest/).

```cmake
# find_package(Python3 REQUIRED) # Interpreter is default component
find_package(Python3
COMPONENTS
    Interpreter
)

if(Python3_FOUND)
    message(STATUS "Python3:")
    message(STATUS "  version: ${Python3_VERSION}")
    message(STATUS "  executable: ${Python3_EXECUTABLE}")
    message(STATUS "  Interpreter: ${Python3_INTERPRETER_ID}")
    message(STATUS "  include:")
    foreach(folder ${Python3_INCLUDE_DIRS})
        message(STATUS "    - ${folder}")
    endforeach()
endif()
```

CMake 3.14 에서는 NumPy 관련된 내용이 추가되었는데, NumPy 바인딩을 위한 헤더파일들이 어디에 있는지 한번 찾아보겠습니다.

```bash
python3 -m pip install numpy
```

```cmake
cmake_minimum_required(VERSION 3.14)
find_package(Python3 COMPONENTS NumPy)

if(TARGET Python3::NumPy)
    message(STATUS "NumPy:")
    message(STATUS "  version: ${Python3_NumPy_VERSION}")
    message(STATUS "  include:")
    foreach(folder ${Python3_NumPy_INCLUDE_DIRS})
    message(STATUS "    - ${folder}")
    endforeach()
endif()
```

그런데 이번에는 Hints 영역이 추가된 것을 확인할 수 있습니다.
이것에 대해서는 다음 모듈에서 다뤄보겠습니다.

#### [FindBoost](https://cmake.org/cmake/help/latest/module/FindBoost.html)

개인적으로 Hint와 Cache 변수가 많으면서, 사용법이 잘 정리가 안되어있다고 느끼는 것이 바로 이 FindBoost인 것 같습니다. [공식 문서의 설명](https://cmake.org/cmake/help/latest/module/FindBoost.html#examples)과 함께 살펴보겠습니다.

```cmake
cmake_minimum_required(VERSION 3.15)
find_package(Boost 1.75 REQUIRED
COMPONENTS
    date_time filesystem
)

if(TARGET Boost::headers)
    # ...
endif()
```

### [CMake 툴체인](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#introduction) (toolchain.cmake)

CMake를 사용할 때 가장 어려운 부분이면서, 스크립트 관련해 정수를 모은 것이 보통 toolchain.cmake 라고 명명된 파일들입니다.
이 파일들은 [User Interaction Guide](https://cmake.org/cmake/help/latest/guide/user-interaction/index.html)에서 설명한 것처럼, [CMAKE_TOOLCHAIN_FILE](https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html)변수를 사용해서 스크립트 파일의 경로를 지정하는 식으로 사용됩니다.

관련된 CMake 문서를 한번 살펴본 뒤에,
https://github.com/leetal/ios-cmake 의 ios.toolchain.cmake 파일을 한번 읽어보겠습니다.

### 생각해보기

##### Q. 언제 Script를 사용해야 하는걸까?

Mathieu Ropert의 발표 내용을 보면 어느정도 추론해낼 수 있는 부분입니다. https://youtu.be/H14CSWkLGUY?t=171 (~4:50)

[CMake의 역할은 Build system 파일을 만드는 것입니다](https://cmake.org/overview/). 주 내용은 어디까지나 프로젝트의 빌드 절차를 기술(describe)하는 것이죠.

CMake의 기원(Origin)에 대한 설명을 보면 configure의 일부 기능들을 가져오려 했다는 것을 알 수 있습니다.
[Make 프로젝트들은 보통 `configure`를 사용하는 사전 절차를 두고 있는데](https://www.gnu.org/prep/standards/html_node/Configuration.html), 이 파일은 shell script입니다. Makefile을 만들어내는 역할을 하죠. 일례로 https://github.com/erlang/otp 를 한번 확인해볼까요?

비록 이번 스터디에서 `cmake --build .` 와 같은 사용법을 보이긴 했었지만, 
CMake의 역할은 빌드를 하는 것이 아닙니다. "파일을 생성"하는 것이죠.
그리고 이런 생성을 위해 필요한 정보들을 조직화할 때 CMake script 관련 지식을 사용하게 됩니다.

##### Q. Script 기능을 실제로 사용하는 사례?

가장 적극적으로 사용하는 경우가 바로 https://github.com/microsoft/vcpkg 인 것 같습니다.

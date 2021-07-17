# CMakeLists.txt 읽고쓰기

### 참고자료

* CMake
    * [Step 1: A Basic Starting Point](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html#step-1-a-basic-starting-point)
    * [User Interaction Guide](https://cmake.org/cmake/help/latest/guide/user-interaction/index.html)
* [CLion: Quick CMake tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)
* Meeting C++ 2019 [Oh No! More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y9kSr5enrSk)
* Meeting C++ 2018 [More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y7ndUhdQuU8)

## 스터디 노트


먼저 간단히 CMakeLists.txt 를 만들고 시작해보겠습니다.

```cmake
cmake_minimum_required(VERSION 3.18)
project(hell_world LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Create shared libraries if ON" OFF)

# ...
```

CMakeLists.txt 를 작성할때는 2가지를 생각해야 합니다.

1. 모호하거나 복잡하지 않게 작성한다
2. 1번을 위반하지 않는지 자주 확인한다

모호한 CMakeLists.txt는 어떻게 만들어질까요? 오늘 스터디를 마칠 때 한번 생각해보겠습니다.

### Build Target

빌드를 수행할때는 소스코드로부터 프로그램을 만드는 과정을 생각하면 간단합니다.
먼저 프로그램의 타입부터 결정합니다.

#### [add_library](https://cmake.org/cmake/help/latest/command/add_library.html)

```cmake
add_library(main
    main.cpp
    src1.c
)
```

Header-only 라이브러리를 만들 때는 [Interface target](https://cmake.org/cmake/help/latest/command/add_library.html#id4)을 사용합니다.
이때는 소스 파일들을 주지 않아도 괜찮습니다. 물론 다른 설정들이 나중에 추가되어야합니다.

```cmake
add_library(main INTERFACE)
```

#### [add_executable](https://cmake.org/cmake/help/latest/command/add_executable.html)

```cmake
add_executable(main
    main.cpp
    src1.c
)
```

Apple 플랫폼을 위한 프로젝트라면 Objective-C++, Swift를 써야 할수도 있겠죠...

```cmake
enable_language(OBJCXX)

add_executable(main
    AppDelegate.mm
    # ...
)
```

```cmake
enable_language(Swift)

add_executable(main
    AppDelegate.swift
    # ...
)
```

#### [set_target_properties](https://cmake.org/cmake/help/latest/command/set_target_properties.html)

CMake가 Target들을 바탕으로 프로젝트 파일들을 생성하기 위해선 필요한 설정들이 있습니다. CMake에서는 [Property](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties)라고 부릅니다.

[`CXX_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html) 부터 시작하죠.

```cmake
if(WIN32)
    set_target_properties(main
    PROPERTIES
        CXX_STANDARD 17
        WINDOWS_EXPORT_ALL_SYMBOLS OFF
    )
endif()
```

빌드 Config에 따라서 이름을 다르게 하도록 할 수 있습니다.
[`<CONFIG>_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/CONFIG_POSTFIX.html#prop_tgt:%3CCONFIG%3E_POSTFIX)

혹은 특별한 이름을 사용하고 싶다면 [`LIBRARY_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_NAME.html)을 바꾸면 됩니다.

```cmake
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set_target_properties(main_static
    PROPERTIES
        DEBUG_POSTFIX D
        LIBRARY_OUTPUT_NAME main
    )
endif()
```

Xcode 에서 필요한 설정들은 아주 많은데,  [`XCODE_ATTRIBUTE_<an-attribute>`](https://cmake.org/cmake/help/latest/prop_tgt/XCODE_ATTRIBUTE_an-attribute.html) 를 사용합니다. 구체적인 사용법은 다음 기회에 다루는게 좋겠네요.

```cmake
if(APPLE)
    get_filename_component(PLIST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist ABSOLUTE)
    set_target_properties(main
    PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${PLIST_PATH}
    )
endif()
```

#### [target_sources](https://cmake.org/cmake/help/latest/command/target_sources.html)

Target에서 보유한 소스 코드의 집합을 늘릴 때 사용합니다.
PUBLIC / PRIVATE 를 사용할 수 있는데, PUBLIC을 쓸 일은 거의 없습니다.

```cmake
if(ANDROID)
    target_sources(main
    PRIVATE
        impl_android.cpp
    )

elseif(WIN32)
    target_sources(main
    PRIVATE
        impl_windows.cpp
    )

endif()
```

Q. 이런 식으로 소스코드 집합을 관리하면 어떤 장점이 있을까요?

#### [target_include_directories](https://cmake.org/cmake/help/latest/command/target_include_directories.html)

이제 전처리기가 Translation Unit을 만들어야 하는데, 이 과정에서는 `#include`가 먼저 처리됩니다. [lex.phases] 5.2.3~4

그렇다면 그 header 파일들을 **어디서** 찾을 것인지 알려줄 필요가 있겠죠.
더해서 이 시점에 [Generator Expression](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html)에 대해서 맛보기를 하고 가는 것도 좋겠습니다.
바로 [BUILD_INTERFACE와 INSTALL_INTERFACE](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#interface-include-directories)입니다.

```cmake
target_include_directories(main
PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/public>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> # for which purpose?
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
PRIVATE
    include # relative to ${CMAKE_CURRENT_SOURCE_DIR}
    externals
)
```

#### [target_compile_definitions](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html)

다음에는 매크로 처리입니다. [lex.phases] 5.2.4~7

마찬가지로 PUBLIC/PRIVATE를 지원합니다.

```cmake
target_compile_definitions(main
PRIVATE
    WIN32_LEAN_AND_MEAN NOMINMAX
)
```

이 직후 whitespace 처리와 같은 몇단계를 더 거치면, 이를 Translation Unit이라고 합니다.

#### [target_compile_options](https://cmake.org/cmake/help/latest/command/target_compile_options.html)

이제 Translation Unit의 처리로 넘어갑니다. 컴파일러 옵션들을 설정할 필요가 있겠군요.

각 컴파일러의 ID는 [이 문서에서](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#supported-compilers) 확인할 수 있습니다.

```cmake
if(CMAKE_CXX_COMPILER_ID MATCHES GNU) # https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
    target_compile_options(main
    PRIVATE
        -fconcepts
    )

elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang) # https://clang.llvm.org/docs/ClangCommandLineReference.html
    if(WIN32) # clang-cl
        target_compile_options(main
        PRIVATE
            "/clang:-fcoroutines-ts"
            -fms-compatibility
        )
    else() # AppleClang or Clang on Linux
        target_compile_options(main
        PRIVATE
            -std=c++2a
        )
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC) # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-160
    target_compile_options(main
    PRIVATE
        /JMC-
    )

endif()
```

#### [target_link_libraries](https://cmake.org/cmake/help/latest/command/target_link_libraries.html)

C++ 프로젝트의 관리자는 많은 라이브러리를 알고 있어야 합니다.
컴파일러, C++ 표준, 플랫폼 3가지를 모두 생각해야 하죠. 만약 이들이 특정한 폴더에 설치되어 있다면 [find_library](https://cmake.org/cmake/help/latest/command/find_library.html)를 사용하게 됩니다.

https://youtu.be/rgWwrzZLVR8?t=970

```cmake
if(WIN32)
    target_link_libraries(main
    PUBLIC
        kernel32
        WindowsApp # == pragma comment(lib, "windowsapp")
    )

elseif(APPLE) # expect AppleClang
    target_compile_options(main
    PUBLIC
        -stdlib=libc++
    )
    target_link_libraries(main
    PUBLIC
        c++
    )

endif()
```

Q. 여기서는 왜 PUBLIC이 사용되었을까요? 어떤 경우에 PRIVATE이 사용되어야 할까요?

여기서 라이브러리 대신 Build Target 혹은 Imported Target을 주는 것이 가능합니다.

```cmake
add_library(sub1 # Build Target
    src1.cpp
)

target_link_libraries(main
PRIVATE
    sub1
)
```

```cmake
find_package(Threads REQUIRED)

target_link_libraries(main
PRIVATE
    Threads::Threads # Imported Target
)
```

#### [target_link_options](https://cmake.org/cmake/help/latest/command/target_link_options.html)

마지막으로 Linker 설정입니다.

```cmake
if(MSVC) # https://docs.microsoft.com/en-us/cpp/build/reference/linker-options?view=msvc-160
    target_link_options(main
    PRIVATE
        /ERRORREPORT:SEND
    )
endif()
```

### Custom Target

#### [add_custom_target](https://cmake.org/cmake/help/latest/command/add_custom_target.html)

어떤 파일을 생성해야 할때는 `add_custom_command`를 사용하고, 그렇지 않을때는 이 command를 사용합니다.
순서를 제어해야 할때는 [`add_dependencies`](https://cmake.org/cmake/help/latest/command/add_dependencies.html)를 사용합니다.

```cmake
find_package(Git REQUIRED)

add_custom_target(check1
    COMMAND ${GIT_EXECUTABLE} --version
    COMMENT "target - check1"
)
add_custom_target(check2
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    COMMENT "target - check2"
)
add_dependencies(check2 check1)
```

이렇게 생성된 Target들을 CLI에서 실행해볼 수 있습니다.

```console
user@host$ cmake .
...
-- Configuring done
-- Generating done
-- Build files have been written to: ...
user@host$ cmake --build . --target check1
...
  target - check1
  git version 2.31.1.windows.1
user@host$ cmake --build . --target check2
...

  target - check1
  git version 2.31.1.windows.1
  target - check2
  b8f4223ebfc59f7e1b57f93995832406afadbc2b
```

### Command

보통 [`find_program`](https://cmake.org/cmake/help/latest/command/find_program.html)과 함께 사용하게 됩니다.

#### [add_custom_command](https://cmake.org/cmake/help/latest/command/add_custom_command.html)

이 command는 생성된 빌드 시스템 파일에 Custom Rule(사용자 정의 절차)을 추가할때 사용합니다.
2가지 목적으로 사용할 수 있는데, 보통은 코드를 생성할 때 사용됩니다.

```cmake
# protocol buffer compiler
find_program(proto_compiler_path
    NAMES   protoc.exe protoc
    PATHS   ${VCPKG_TOOL_DIR}/protobuf
    # NO_DEFAULT_PATH 
)
message(STATUS "protoc: ${proto_compiler_path}")

# grpc plugin: c++
find_program(grpc_cpp_plugin_path
    NAMES   grpc_cpp_plugin.exe grpc_cpp_plugin
    PATHS   ${VCPKG_TOOL_DIR}/grpc
    # NO_DEFAULT_PATH 
)
message(STATUS "grpc_cpp_plugin: ${grpc_cpp_plugin_path}")

add_custom_command(
    OUTPUT  service.pb.h service.pb.cc
    COMMENT "code generation: c++"
    COMMAND ${proto_compiler_path} --version
    COMMAND ${proto_compiler_path} service.proto
                --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${proto_compiler_path} service.proto
                --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
                --plugin="protoc-gen-grpc=${grpc_cpp_plugin_path}"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
```

다른 하나는 Build/Link 직전에 어떤 작업을 수행해야 하는 경우 입니다.

https://cmake.org/cmake/help/latest/command/add_custom_command.html#build-events

#### [execute_process](https://cmake.org/cmake/help/latest/command/execute_process.html)

명령을 실행한다는 점에서, `add_custom_target`과 유사하지만, 차이점은 실행하는 시간이 다르다는 것입니다.
`add_custom_target`이 빌드 시간에, `execute_process`는 Configure 시간에 실행됩니다.

```cmake
find_package(Git REQUIRED)

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE COMMIT_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ENCODING UTF-8
)
message(STATUS "Current commit: ${COMMIT_ID}")
# ...

target_compile_definitions(main
PRIVATE
    BUILD_COMMIT_ID="${COMMIT_ID}"
)
```

이제까지의 내용을 바탕으로, CMake 프로젝트는 Configure / Generate / Build 시간을 가지며, 각각 어느때에 사용되는지 이해해야 한다는 것을 알 수 있습니다.

### 알려진 변수들, 패턴, 표현식

#### [Build variables](https://cmake.org/cmake/help/latest/guide/user-interaction/index.html#setting-build-variables)

[CMake 사용자 상호작용 가이드](https://cmake.org/cmake/help/latest/guide/user-interaction)에서 소개하는 변수들을 살펴봅니다.

```bash
mkdir -p build && pushd build
    cmake .. \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_INSTALL_PREFIX=../install/debug \
        -DCMAKE_TOOLCHAIN_FILE=/path/to/toolcahin.cmake \
        -DBUILD_SHARED_LIBS=true
popd
```

여기서 [`CMAKE_TOOLCHAIN_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html)이 처음 언급되는데, 이 파일에 대한 설명은 [cmake-toolchains.7.html 메뉴얼](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html)에서 확인할 수 있습니다.


#### [if/elseif/else](https://cmake.org/cmake/help/latest/command/if.html)

이제까지 살펴본 조건들 이외에도 Target/Variable/Cache/File의 존재 유무, 대소 비교를 지원합니다.
앞으로 틈틈이 보게 될 예정이니, 문서를 읽어보는 정도로 충분할 것 같습니다.

* [`if((condition) AND (condition OR (condition)))`](https://cmake.org/cmake/help/latest/command/if.html#logic-operators)
* [`if(TARGET target-name)`](https://cmake.org/cmake/help/latest/command/if.html#existence-checks)
* [`if(DEFINED <name>|CACHE{<name>}|ENV{<name>})`](https://cmake.org/cmake/help/latest/command/if.html#existence-checks)
* [`if(EXISTS path-to-file-or-directory)`](https://cmake.org/cmake/help/latest/command/if.html#file-operations)
* [`if(<variable|string> LESS <variable|string>)`](https://cmake.org/cmake/help/latest/command/if.html#comparisons)


#### [install](https://cmake.org/cmake/help/latest/command/install.html)

Q. 왜 프로젝트가 [설치](https://dic.daum.net/word/view.do?wordid=kkw000141569&supid=kku000177298)를 지원해야 할까요?

```cmake
install(FILES   LICENSE.txt
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}
)
```

가장 쉬운 설치 방법은 이렇습니다.

```cmake
install(TARGETS main
        RUNTIME  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
```

버전과 관련된 스크립트를 생성할때는 [`CMakePackageConfigHelpers`](https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html) 모듈을 사용합니다.

```cmake
include(CMakePackageConfigHelpers)
set(VERSION_FILE_PATH   ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config-version.cmake)
write_basic_package_version_file(${VERSION_FILE_PATH}
    VERSION             ${PROJECT_VERSION}
    COMPATIBILITY       SameMajorVersion
)
install(FILES           ${VERSION_FILE_PATH} 
        DESTINATION     ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}
)
```

설치된 파일들을 확인해봅시다.

Q. 어떤 파일들이 더 추가로 '설치'되어야 할까요?


### 복잡함 피하기

#### CMAKE_ 변수

대표적으로 CMAKE_CXX_STANDARD가 있는데, 이 변수의 사용사례를 가지고 생각해보겠습니다.

```cmake
# ...
```

#### [target_compile_features](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html)

이것은 CMake 고유성이 강합니다. 
[CMAKE_CXX_KNOWN_FEATURES](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES) 문서를 살펴보겠습니다.


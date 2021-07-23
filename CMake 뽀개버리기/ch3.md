# CMake 프로젝트의 Test, Import

### 참고자료

* CMake
    * [Using Dependencies Guide](https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html)
    * CMake Buildsystem: [Imported Targets](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)
    * [Importing and Exporting Guide](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html)
    * [Installing and Testing Guide](https://cmake.org/cmake/help/latest/guide/tutorial/Installing%20and%20Testing.html)
* Conan C/C++ Package Manger
    * [Getting Started](https://docs.conan.io/en/latest/getting_started.html)

## 스터디 노트

이번에는 작은 프로젝트를 하나 만들어서 시작해보겠습니다.

```cmake
cmake_minimum_required(VERSION 3.13)
project(sample LANGUAGES CXX)
```

### Testing

오늘날의 프로그램들은 필수적으로 설치와 테스트를 지원해야 합니다.

아마 많은 [Make](https://en.wikipedia.org/wiki/Make_(software)) 프로젝트들이 `make install`, `make test` 명령을 지원하는 것을 보셨을 것이라 생각합니다.
Make의 영향을 받은 CMake 또한 이에 대응하는 기능들을 지원하고 있습니다.
두 단계는 서로 상관이 없는 경우가 대부분이지만, 편의상 이번에는 둘을 결합해서 사용하는 형태로 다루도록 하겠습니다.

> 주의: 여기서 다루는 '설치'는 '패키징'과는 다른것입니다. 패키징에 대해서는 [6주차](./ch6.md)에 다루도록 하겠습니다.

테스트 옵션과 관련해서 관례가 정해져 있는 것은 아닙니다. 
많은 CMake 프로젝트들은 자신만의 옵션을 추가해서 사용하고 있으며... 옵션이 없는 경우도 많습니다. 
즉, 언제나 테스트 관련 내용을 사용하는 경우도 있다는 것이죠.

이 스터디에서는 [CTest](https://cmake.org/cmake/help/latest/module/CTest.html) 모듈의 정의를 따라, BUILD_TESTING 이라는 이름으로 옵션을 사용하겠습니다.

```cmake
option(BUILD_TESTING "Build test programs" ON)
# ...
if(NOT BUILD_TESTING)
    return()
endif()
```

> 여담으로, CTest 모듈은 테스트 결과를 HTTP request로 전송할 수 있도록 지원합니다.  
> 필자의 생각으로는, 이제는 CI 서비스에서 전체 과정의 결과를 갈무리할때는 파일을 사용하는 경우가 더 많은 것 같습니다.

코드의 커버리지 수집에 관심이 있고, GCC 를 사용하는 프로젝트라면 [CTestCoverageCollectGCOV](https://cmake.org/cmake/help/latest/module/CTestCoverageCollectGCOV.html) 모듈을 고려해보는 것도 좋겠습니다.

#### [enable_testing](https://cmake.org/cmake/help/latest/command/enable_testing.html)

먼저 Command 2개를 알아야 합니다. enable_testing과 add_test입니다.

```cmake
if(NOT BUILD_TESTING)
    return()
endif()
enable_testing()
```

이 Command를 사용하는 것으로, CTestTestfile.cmake 가 생성됩니다.
add_test를 추가하면서 내용이 복사되는 것을 확인할 수 있습니다.

#### [add_test](https://cmake.org/cmake/help/latest/command/add_test.html)

Test run 의 이름, 실행을 위해 사용할 CLI 명령, 실행할 폴더를 지정합니다.
Generator에 따라서는 IDE에서 `RUN_TESTS` target으로 관련된 내용을 확인할 수 있습니다.

```cmake
if(APPLE)
add_test(NAME feature_Apple COMMAND uname -a)
endif()
```

Target에서 실행 프로그램을 생성하는 경우, 이 프로그램을 사용하는 것도 가능합니다.

```
add_executable(test_suite)
# ...
add_test(NAME feature_ALL COMMAND test_suite
         WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR})
```

#### [CTest CLI](https://cmake.org/cmake/help/latest/guide/tutorial/Installing%20and%20Testing.html)

ctest 프로그램은 많은 옵션을 지원하지만 add_test로 추가된 내용을 실행시키는 것만이 목적이라면 옵션 몇개만 기억하고 있어도 충분히 사용할 수 있습니다.

테스트 프로그램과 샘플 프로그램이 분리되어 있다면 사용 방법을 보여주기 위해 add_test를 다양하게 작성해두는 것도 좋은 방법이겠습니다.

> 필자는 CMake를 오직 빌드/설치에만 사용하고, 패키징과 테스트 실행은 다른 툴에 의해서도 수행될 수 있어야 한다고 생각하기 때문에 이 기능을 상대적으로 적게 사용하는 편입니다.

```console
user@host$ ctest --help
Usage

  ctest [options]

Options
...
```

필자는 보통 2개 옵션을 사용해 호출합니다.

```bash
# Print logs when failed
ctest --output-on-failure --stop-on-failure
```

성공했을 때의 출력을 보고 싶을때는 verbose 혹은 extra verbose 옵션을 사용합니다.
CLI로 확인할 수 있는 내용 이외에도, 로그 파일은 Testing 폴더 아래에서 확인할 수 있습니다.

```
ctest --extra-verbose 
```

시간제한을 둘 수도 있습니다.

```
ctest --timeout 3600 # Time limit 1H
```

#### 실제로 사용해보기

이번에는 C++ 생태계의 여러 프로젝트 중 테스트 프레임워크 Catch2를 CLion에서 사용해보겠습니다.
또 맛보기로 Conan 패키지 매니저를 사용해 이 라이브러리를 Import 해볼 것입니다.

```conan
# https://docs.conan.io/en/latest/reference/conanfile_txt.html
[requires]
catch2/[>=2.11]

# https://docs.conan.io/en/latest/reference/generators.html#generators-reference
[generators]
cmake_find_package
```

```cmake
# conan install . -if build --build missing -s build_type=Debug
find_file(CONAN_SCRIPT 
    NAMES conanbuildinfo.txt
    PATHS ${CMAKE_BINARY_DIR}
          ${PROJECT_SOURCE_DIR}/build
)
if(CONAN_SCRIPT)
    get_filename_component(CONAN_SCRIPT_DIR ${CONAN_SCRIPT} DIRECTORY)
    list(APPEND CMAKE_MODULE_PATH ${CONAN_SCRIPT_DIR})
endif()
```

이 라이브러리는 Google.Test 또는 Boost Test와는 달리, header-only 로 파일들이 구성되어 있고, Macro를 정의함으로써 기능을 활성화하도록 하고 있는 특징이 있습니다.
빌드 관련 설정이 간소화 하기에 좋은 특징을 가지고 있지만, 파일이 굉장히 큽니다. (17000+ LoC)

또 많은 내용이 매크로로 작성되어 있으므로, PCH(Precompiled Header)를 사용하는 것을 권합니다.
CMake에서는 [target_precompile_headers](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html)를 사용해서 PCH 방법을 적용할 수 있습니다.

```cmake
# ...
enable_testing()
find_package(Catch2 REQUIRED)

add_executable(test_suite
    test_main.cpp
)

set_target_properties(test_suite
PROPERTIES
    CXX_STANDARD 17
)

target_link_libraries(test_suite
PRIVATE
    Catch2::Catch2 # ...
)
```

test_main.cpp 는 별 내용 없이 아래 코드 정도만 있으면 충분할 것 같습니다.

```c++
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

int main(int argc, char *argv[]) {
  Catch::Session s{};
  return s.run(argc, argv);
}

struct nameinfo_test_case {
  sockaddr_storage sa{};
  char hostname[NI_MAXHOST] {}

protected:
  nameinfo_test_case() {
    sa.ss_len = sizeof(sockaddr_in6);
    sa.ss_family = PF_INET6;
  }
};

TEST_CASE_METHOD(nameinfo_test_case, "hostname from IN6ADDR_LOOPBACK_INIT") {
  auto local = reinterpret_cast<sockaddr_in6 *>(&sa);
  local->sin6_addr = IN6ADDR_LOOPBACK_INIT;
  local->sin6_port = 0;
  if (auto ec = getnameinfo(reinterpret_cast<sockaddr *>(&sa), sa.ss_len, //
                            hostname, NI_MAXHOST, NULL, 0,                //
                            NI_NAMEREQD);
      ec != 0)
    FAIL(gai_strerror(ec));
  REQUIRE(strnlen(hostname, NI_MAXHOST));
}
```

### Import Target

CMake 2.x 버전에서는 프로젝트 **외부**에서 빌드에 필요한 파일들을 가져올 때 `include_directories`, `compile_options`, `link_libraries`를 사용해서 관리하였지만, CMake 3.x에서는 그렇지 않습니다.

CMake 3 에서는 대부분이 Target을 사용해 동작하며, 이를 통해 자연스럽게 오류의 원인을 추적하기 쉽고, 간결하게 작성할 수 있도록 돕고 있습니다.
**외부**의 파일과 설정들을 가져올때도 마찬가지로 Target을 만들어 처리하여야 합니다.

#### [find_library](https://cmake.org/cmake/help/latest/command/find_library.html)

먼저 라이브러리를 찾는 것부터 시작해보겠습니다.

```cmake
find_library(FMT_LIBPATH 
    NAMES fmtd fmt
    PATHS ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug
          ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}
    # NO_DEFAULT_PATH
    # NO_SYSTEM_ENVIRONMENT_PATH
)
if(FMT_LIBPATH)
    message(STATUS "Found ${FMT_LIBPATH}")
endif()
```

관련해서 알아두어야 할 옵션이 2가지 있습니다. `NO_DEFAULT_PATH`와 `NO_SYSTEM_ENVIRONMENT_PATH` 입니다.

* `NO_DEFAULT_PATH`: 오직 PATHS에 지정한 경로에서만 라이브러리를 찾도록 제한합니다.
* `NO_SYSTEM_ENVIRONMENT_PATH`: PATH 환경변수를 사용하지 않도록 제한합니다.

Apple 플랫폼에서는 framework를 찾을 때도 사용합니다.

```cmake
if(APPLE)
    find_library(CoreVideo_LIBPATH NAMES CoreVideo REQUIRED)
endif()

target_link_libraries(main
PRIVATE
    ${CoreVideo_LIBPATH} # -framework CoreVideo
)
```

#### [Import가 가능하도록 Property 설정하기](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#importing-libraries)

이미 빌드가 끝난 프로그램을 사용한다는 것을 CMake에게 알려주기 위해, `add_library`에 IMPORTED를 적어주면 됩니다.

```cmake
add_library(Catch2::Catch2 INTERFACE IMPORTED) # header only
```

```cmake
add_library(libGLESv2 SHARED IMPORTED GLOBAL)
```

.lib 라이브러리는 `IMPORTED_IMPLIB`에 사용합니다.
.a, .so, .dylib, .dll 라이브러리는 `IMPORTED_LOCATION`에 사용합니다.

필요에 따라 `find_library`로 파일들을 동적으로 찾아서 사용하거나, `get_filename_component`를 써서 절대 경로를 주는 것도 가능합니다.

> 두 command 모두 CMake Cache의 영향을 받을 수 있다는 특징이 있습니다.

```cmake
set_target_properties(libGLESv2
PROPERTIES
    IMPORTED_IMPLIB         "${QtANGLE_GLES_LIB_REL}"
    IMPORTED_IMPLIB_DEBUG   "${QtANGLE_GLES_LIB_DBG}"
    IMPORTED_LOCATION       "${QtANGLE_GLES_BIN_REL}"
    IMPORTED_LOCATION_DEBUG "${QtANGLE_GLES_BIN_DBG}"
)
```

#### Command들의 [INTERFACE](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets) 옵션

라이브러리 파일 이외에도 header, macro, compiler option 등을 함께 전달해야 하는 경우가 생깁니다.
이때 사용하는 것이 INTERFACE 옵션입니다.

```cmake
cmake_minimum_required(VERSION 3.11)
target_include_directories(libGLESv2
INTERFACE
    ${QtANGLE_INCLUDE_DIR}
)
target_compile_definitions(libGLESv2
INTERFACE
    ${QtANGLE_COMPILE_DEFINITIONS}
)
target_compile_options(libGLESv2
INTERFACE
    # ...
)
```

거의 사용할 일이 없지만, linker option을 전달할 수도 있습니다.

```cmake
cmake_minimum_required(VERSION 3.13)
target_link_options(libGLESv2
INTERFACE
    # ...
)
```

여러 라이브러리들을 묶어서 사용하고 싶을 수도 있습니다.

이때는 [INTERFACE_LINK_LIBRARIES](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html)를 설정합니다.

실제로 CMake에서 어떻게 사용하는지 한번 보면 좋을 것 같습니다.
[Exporting Targets]
(https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#exporting-targets)의 내용을 바탕으로, 

```cmake
cmake_minimum_required(VERSION 3.13)
project(sample2 LANGUAGES CXX)

include(GNUInstallDirs)

find_package(Threads REQUIRED)

add_library(abc INTERFACE)

set_target_properties(abc
PROPERTIES
    CXX_STANDARD 17
)

target_include_directories(abc
INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # include
)

target_link_libraries(abc
INTERFACE
    ${CMAKE_DL_LIBS} Threads::Threads
)

install(TARGETS abc
        EXPORT abc-targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
)
install(EXPORT abc-targets
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR} # share
)
```

```bash
cmake . -DCMAKE_INSTALL_PREFIX=$(pwd)/install
cmake --build . --config Debug --target install
```

이 내용을 바탕으로 설치된 abc-targets.cmake 를 읽어보면서 앞의 내용을 다시 짚어보겠습니다.

### Review

드디어, CMake 스크립트를 작성하기 위한 기본적인 내용들을 전부 다뤄본 것 같습니다.
실제로 **남이 작성한** 스크립트를 읽을 수 있게 되었는지 한번 볼까요?

#### Conan의 Imported Target

좀 전에 Catch2 라이브러리를 Conan 을 사용해서 설치했는데, 어떤 내용이 들어있을까요?

```conan
[requires]
catch2/[>=2.11]

[generators]
cmake_find_package
```

```
conan install . -if build
```

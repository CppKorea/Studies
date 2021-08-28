# Cross Compile 프로젝트의 빌드 설계

### 참고자료

* [Andreas Reischuck "Cross Compiling with CMake"](https://www.youtube.com/watch?v=rgWwrzZLVR8)

굉장히 배울 점이 많은 영상입니다. 다소 지루할 수 있겠지만 
정주행 해두시면 CMake Toolchain을 사용해 Cross Compile을 할때 어떻게 접근해야 하는지 이해할 수 있을 것입니다.

## 스터디 노트

이제서야 Cross-platform Make 다운 주제로 돌아온 것 같습니다.
먼저 CMake를 실행하기 편하도록 [CMake Presets](https://cmake.org/cmake/help/v3.20/manual/cmake-presets.7.html)를 설정하고 시작하겠습니다.

```cmake
cmake_minimum_required(VERSION 3.20)
project(sample LANGUAGES CXX)

find_package(ZLIB 1.2 REQUIRED)

```

### CMake Presets

* [An Introduction to CMakePresets.json](https://www.youtube.com/watch?v=NFbnm1t6Mc4)
* https://cmake.org/cmake/help/latest/guide/user-interaction/index.html#presets
* https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html

최신 버전에서는 CMake 사용을 좀 더 간단히 해주는 Presets 기능이 추가되었습니다.

Visual Studio Code 플러그인 중 Microsoft의 [CMake Tools](https://github.com/microsoft/vscode-cmake-tools)가 있습니다.
이 플러그인은 CMake Preset 사용법을 [설명하는 문서](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-presets.md)가 있는데, 그대로 따라가보죠...

```json
{
    "version": 3,
    "cmakeMinimumRequired": {
        "major": 3,
        "minor": 20,
        "patch": 1
    },
    "configurePresets": [
        {
            "name": "vcpkg-x64-osx-debug",
            "displayName": "vcpkg(x64-osx) debug",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/build-x64-osx",
            "cacheVariables": {
                "BUILD_TESTING": "ON",
                "BUILD_SHARED_LIBS": "ON",
                "CMAKE_BUILD_TYPE": {
                    "type": "STRING",
                    "value": "Debug"
                },
                "CMAKE_TOOLCHAIN_FILE": {
                    "type": "FILEPATH",
                    "value": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
                },
                "VCPKG_TARGET_TRIPLET": "x64-osx"
            },
            "environment": {
                "CI": "true"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "vcpkg-x64-osx-debug",
            "configurePreset": "vcpkg-x64-osx-debug"
        }
    ],
    "testPresets": [
        {
            "name": "vcpkg-x64-osx-debug",
            "configurePreset": "vcpkg-x64-osx-debug",
            "output": {
                "outputOnFailure": true
            },
            "execution": {
                "noTestsAction": "error",
                "stopOnFailure": false
            }
        }
    ]
}
```

`cacheVariables`에 CMake의 변수들이 작성된 것을 확인할 수 있습니다.
이번 기회에 [CMake의 변수들이 어떤 종류로 나뉘는지](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html) 알아두는 것도 필요할 것 같습니다.

특히 [Variables that Describe the System](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#variables-that-describe-the-system), [Variables that Change Behavior](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#variables-that-change-behavior) 부분을 주의 깊게 읽어두면 toolchain의 분석, 개조에 도움이 됩니다.

### CMake Toolchain for Cross Compiling

* https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling

간혹 독자적인 toolchain.cmake 파일을 작성하는 경우가 있습니다. 이런 Standalone 방법을 취하기 보다는, 가급적 생태계에 공개되어 있고, Build service들을 통해 검증하고 있는 프로젝트들의 파일들을 사용하는 것을 권합니다.

* GitHub: https://github.com/search?l=CMake&q=toolchain.cmake&type=Repositories
* GitLab: https://gitlab.com/search?group_id=&project_id=&repository_ref=&scope=issues&search=toolchain+cmake&snippets=false
* GitLab CMake 저장소: https://gitlab.kitware.com/cmake/cmake/-/issues

### Android

* CMake
    * [Cross Compiling for Android](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-android)
* Android Studio Guide
    * [Install and configure the NDK and CMake](https://developer.android.com/studio/projects/install-ndk)
    * [AGP(Android Gradle Plugin) - Release Notes](https://developer.android.com/studio/releases/gradle-plugin)
* NDK Guides
    * [CMake](https://developer.android.com/ndk/guides/cmake)
    * [ABI](https://developer.android.com/ndk/guides/abis)
    * [Other Build Systems](https://developer.android.com/ndk/guides/other_build_systems)
* https://github.com/android/ndk Issue 1407
* Android Google Source
    * [Build System Maintainers Guide](https://android.googlesource.com/platform/ndk/+/master/docs/BuildSystemMaintainers.md)


NDK 버전에 따라서 설치 구조가 좀 다를텐데, 이 스터디에서는 [22.1.7171670](https://github.com/android/ndk/issues/1407)이후 버전을 기준으로 설명하겠습니다. 이 버전에는 clang 11이 내장되어 있습니다.

NDK 버전을 선택할때는 [AGP API 버전](https://developer.android.com/reference/tools/gradle-api)을 먼저 결정하고, 이후에 [해당 버전에 맞는 NDK 버전](https://developer.android.com/studio/projects/install-ndk#default-ndk-per-agp)을 선택하여야 합니다.
별다른 기준을 두고 싶지 않다면 https://github.com/android/ndk-samples 저장소를 모니터링 하는 것도 방법이 될 수 있습니다.

#### 툴체인을 사용한 빌드

CMakeLists.txt, CMakePresets.json 에 각각 내용을 추가할 것입니다.

```cmake
message(STATUS "cmake:")
message(STATUS "  - version:   ${CMAKE_VERSION}")
message(STATUS "  - toolchain: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "  - find_root_path: ${CMAKE_FIND_ROOT_PATH}") 
message(STATUS "compiler:")
message(STATUS "  - id: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  - version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  - path: ${CMAKE_CXX_COMPILER}")
message(STATUS "android:")
message(STATUS "  - platform:  ${ANDROID_PLATFORM}")
message(STATUS "  - arch_name: ${ANDROID_ARCH_NAME}")
message(STATUS "  - abi: ${ANDROID_ABI}") # arm64-v8a 
message(STATUS "  - ndk: ${ANDROID_NDK}") # Path/to/NDK
message(STATUS "  - stl: ${ANDROID_STL}") # c++_shared
```

`configurePresets`, `buildPresets`에 각각 아래와 같이 추가해줍니다.
아래 내용에서 환경변수 `ANDROID_NDK_HOME`를 사용하도록 하였습니다. AGP 에서 사용하던 변수의 이름을 그대로 가져온 것으로, 다른 이름을 사용해도 무방합니다.

```json
{
    "name": "x64-android",
    "displayName": "x64-android",
    "generator": "Ninja",
    "binaryDir": "${sourceDir}/build-x64-android",
    "cacheVariables": {
        "CMAKE_TOOLCHAIN_FILE": {
            "type": "FILEPATH",
            "value": "$env{ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake"
        },
        "ANDROID_ABI": "x86_64",
        "ANDROID_PLATFORM_LEVEL": "24",
        "ANDROID_STL": "c++_shared"
    }
}
```

```json
{
    "name": "x64-android",
    "configurePreset": "x64-android"
}
```

#### android.toolchain.cmake 리뷰

* https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html

이 툴체인에서는 `ANDROID_`로 시작하는 변수들을 설정해줄 수 있습니다. 각각 어떤 값들이 사용되는지 알아두는 것이 좋습니다.

```cmake
# Standard cross-compiling stuff.
set(ANDROID TRUE)
set(CMAKE_SYSTEM_NAME Android)
```

위와 같은 내용은 `CMAKE_SYSTEM_` 변수들을 변경하고 있다는 '지표(指標)'라고 생각할 수 있습니다.

* `CMAKE_SYSTEM_PROCESSOR`
* `CMAKE_SYSROOT`
* `CMAKE_SYSTEM_LIBRARY_PATH`
* `CMAKE_LIBRARY_ARCHITECTURE`

CMake script(.cmake)를 작성해야 하는 입장에서 중요한 변수들은 아래와 같습니다.

* `CMAKE_FIND_ROOT_PATH`

Compiler/Linker 툴의 이름, 옵션도 확인할 수 있습니다.

* `CMAKE_CXX_COMPILER`
* `CMAKE_CXX_FLAGS`
* `CMAKE_SHARED_LINKER_FLAGS`
* `CMAKE_AR`
* `CMAKE_RANLIB`
* `CMAKE_STRIP`

### iOS

* https://github.com/leetal/ios-cmake

`configurePresets`, `buildPresets`에 각각 아래와 같이 추가해줍니다.

```json
{
    "name": "arm64-ios",
    "displayName": "arm64-ios",
    "generator": "Xcode",
    "binaryDir": "${sourceDir}/build-arm64-ios",
    "cacheVariables": {
        "BUILD_SHARED_LIBS": "ON",
        "CMAKE_TOOLCHAIN_FILE": {
            "type": "FILEPATH",
            "value": "${sourceDir}/ios-cmake/ios.toolchain.cmake"
        },
        "PLATFORM": "OS64",
        "DEPLOYMENT_TARGET": "11.0",
        "ENABLE_BITCODE": "false",
        "ENABLE_ARC": "true",
        "ENABLE_VISIBILITY": "false",
        "ARCHS": "arm64 x86_64"
    }
}
```

```json
{
    "name": "arm64-ios",
    "configurePreset": "arm64-ios"
}
```

#### Framework

.framework 파일을 생성할 때는 [`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html)와 관련 속성값들을 설정해줘야 합니다.

```cmake
set_target_properties(sample
PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION A
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.0
    MACOSX_FRAMEWORK_IDENTIFIER "dev.luncliff"
    # XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
)

install(TARGETS sample
        EXPORT  sample-config
        FRAMEWORK   DESTINATION ${CMAKE_INSTALL_PREFIX}
)
```

#### ios.toolchain.cmake 리뷰

> 이 툴체인은 Google에서 시작되어...

Device 뿐만 아니라 Simulator 관련 옵션도 지원하고 있으며, 4.x로 버전업 하면서 Mac 빌드 설정들이 추가되었습니다.
꽤 많은 변수들을 설정해줘야 하지만 위처럼 CMake Presets로 관리하거나 Configure/Generate를 수행하는 절차를 CI 서비스들의 YAML로 정리할 수도 있기에 아주 큰 부담은 아니라고 할 수 있겠습니다.

```cmake
# Standard settings.
set(CMAKE_SYSTEM_VERSION ${SDK_VERSION} CACHE INTERNAL "")
set(UNIX TRUE CACHE BOOL "")
set(APPLE TRUE CACHE BOOL "")
if(PLATFORM STREQUAL "MAC" OR PLATFORM STREQUAL "MAC_ARM64")
  set(IOS FALSE CACHE BOOL "")
  set(MACOS TRUE CACHE BOOL "")
elseif(PLATFORM STREQUAL "MAC_CATALYST" OR PLATFORM STREQUAL "MAC_CATALYST_ARM64")
  set(IOS TRUE CACHE BOOL "")
  set(MACOS TRUE CACHE BOOL "")
else()
  set(IOS TRUE CACHE BOOL "")
endif()
```

Apple 플랫폼 빌드와 관련해서 알아두면 좋을 변수들은 이정도 될 것 같습니다.

* [`CMAKE_MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html)
    * [`install(TARGETS targets... BUNDLE DESTINATION ...)`](https://cmake.org/cmake/help/latest/command/install.html#installing-targets)
* [`CMAKE_OSX_ARCHITECTURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_ARCHITECTURES.html)
* [`CMAKE_FIND_FRAMEWORK`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html)

Xcode 프로젝트 파일에서 사용할 옵션들은 [`CMAKE_XCODE_ATTRIBUTE_`로 시작하며, 전부 대문자를 사용합니다](https://cmake.org/cmake/help/latest/variable/CMAKE_XCODE_ATTRIBUTE_an-attribute.html).
Target마다 property로 지정하는 경우, [`XCODE_ATTRIBUTE_`로 시작합니다](https://cmake.org/cmake/help/latest/prop_tgt/XCODE_ATTRIBUTE_an-attribute.html). 

* `CMAKE_XCODE_ATTRIBUTE_ARCHS`
* `CMAKE_XCODE_ATTRIBUTE_SUPPORTED_PLATFORMS`
* `CMAKE_XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET`
* `CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET`
* `CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED`
* `CMAKE_XCODE_ATTRIBUTE_BITCODE_GENERATION_MODE`
* `CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE`
* `CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC`

실제로 각 필드가 어떻게 Xcode "Build Settings"에 영향을 주는지 살펴보겠습니다.

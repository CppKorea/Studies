# CMakeLists.txt 읽고쓰기

### 참고자료

* CMake
    * [Step 1: A Basic Starting Point](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html#step-1-a-basic-starting-point)
    * [User Interaction Guide](https://cmake.org/cmake/help/latest/guide/user-interaction/index.html)
* [CLion: Quick CMake tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)
* Meeting C++ 2019 [Oh No! More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y9kSr5enrSk)
* Meeting C++ 2018 [More Modern CMake - Deniz Bahadir](https://www.youtube.com/watch?v=y7ndUhdQuU8)

## 스터디 노트

### Build Target

#### [add_library](https://cmake.org/cmake/help/latest/command/add_library.html)

```cmake
# ...
```

#### [add_executable](https://cmake.org/cmake/help/latest/command/add_executable.html)

```cmake
# ...
```

### Custom Target

#### [add_custom_target](https://cmake.org/cmake/help/latest/command/add_custom_target.html)

```cmake
# ...
```

### Command

#### [add_custom_command](https://cmake.org/cmake/help/latest/command/add_custom_command.html)

```cmake
# ...
```

#### [execute_process](https://cmake.org/cmake/help/latest/command/execute_process.html)

```cmake
# ...
```

### 알려진 변수들, 패턴, 표현식

#### [Build variables](https://cmake.org/cmake/help/latest/guide/user-interaction/index.html#setting-build-variables)

```cmake
# ...
```

#### [if/elseif/else](https://cmake.org/cmake/help/latest/command/if.html)

[`if((condition) AND (condition OR (condition)))`](https://cmake.org/cmake/help/latest/command/if.html#logic-operators)

```cmake
# ...
```

[`if(TARGET target-name)`](https://cmake.org/cmake/help/latest/command/if.html#existence-checks)

```cmake
# ...
```

[`if(DEFINED <name>|CACHE{<name>}|ENV{<name>})`](https://cmake.org/cmake/help/latest/command/if.html#existence-checks)

```cmake
# ...
```

[`if(EXISTS path-to-file-or-directory)`](https://cmake.org/cmake/help/latest/command/if.html#file-operations)

```cmake
# ...
```

[`if(<variable|string> LESS <variable|string>)`](https://cmake.org/cmake/help/latest/command/if.html#comparisons)

```cmake
# ...
```

#### [install](https://cmake.org/cmake/help/latest/command/install.html)

Q. 왜 프로젝트가 설치를 지원해야 하는걸까?


#ifndef HEADERS_CUSTOM_H__
#define HEADERS_CUSTOM_H__

#include "headers_std.h"

//Windows 종속적인 구현을 사용합니다.
//입출력은 OS 종속적인 경우가 많으므로 굳이 이 코드를 모든 OS에서 처리할 수 있게 하려다가
//내용이 산으로 갈 수 있기 때문입니다.
#include <Windows.h>

#include "Utility/Study_Object.h"

#include "Utility/Study_IO.h"

#include "Utility/Study_Status.h"

#include "Utility/Study_Localize.h"

#include "Function/Study_Schedule.h"

#include "Utility/program_utill.h"

#endif
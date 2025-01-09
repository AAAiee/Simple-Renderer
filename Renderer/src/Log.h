#pragma once
#include <GL/glew.h>

#define ASSERT(x) if(!(x)) {__debugbreak();}
#define GLLOGCALL(x) ClearError();\
    x;\
    ASSERT(PullError(#x,__LINE__,__FILE__))


void ClearError();
bool PullError(const char* func_name, const int& line_number, const char* file);

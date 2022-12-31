#pragma once

#include <cstdio>

#define LOGLINE() printf("[%s:%d]\n", __FILE__, __LINE__)

#define LOG(X) printf("[%s:%d] %s\n", __FILE__, __LINE__, (X))

#define LOGI(X) printf("[%s:%d] %d\n", __FILE__, __LINE__, (X))
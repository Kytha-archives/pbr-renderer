#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include "Timestep.h"

#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#define BIT(x) (1 << x)
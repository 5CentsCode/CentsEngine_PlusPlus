#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>

#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else

#endif

#include <stdint.h>
#include <glm/glm.hpp>

#define UNUSED_PARAM(T) T

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using Color = glm::vec4;
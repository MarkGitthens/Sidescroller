include(src/core/CMakeLists.txt)
include(src/physics/CMakeLists.txt)
include(src/entities/CMakeLists.txt)
include(src/util/CMakeLists.txt)
include(src/util/tiled/CMakeLists.txt)
include(src/core/events/CMakeLists.txt)

set(VULTURE2D_HEADERS
	${VULTURE2D_CORE_HEADERS}
	${VULTURE2D_EVENTS_HEADERS}
	${VULTURE2D_PHYSICS_HEADERS}
	${VULTURE2D_ENTITIES_HEADERS}
	${VULTURE2D_UTIL_HEADERS}
	${VULTURE2D_TILED_HEADERS})

set(VULTURE2D_SRC src/main.cpp
	${VULTURE2D_CORE_SRC}
	${VULTURE2D_EVENTS_SRC}
	${VULTURE2D_PHYSICS_SRC}
	${VULTURE2D_ENTITIES_SRC}
	${VULTURE2D_UTIL_SRC}
	${VULTURE2D_TILED_SRC})

list(APPEND VULTURE2D_SRC ${VULTURE2D_HEADERS})

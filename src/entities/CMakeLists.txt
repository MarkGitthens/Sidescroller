file(GLOB VULTURE2D_ENTITIES_HEADERS "src/entities/*.h")
file(GLOB VULTURE2D_ENTITIES_SRC "src/entities/*.cpp")

set(VULTURE2D_ENTITIES_HEADERS 
    src/entities/Box.h
    src/entities/Camera.h
    src/entities/Player.h
    src/entities/Projectile.h
    src/entities/ResetBox.h
    src/entities/TiledMap.h)

set(VULTURE2D_ENTITIES_SRC 
    src/entities/Box.cpp
    src/entities/Camera.cpp
    src/entities/Player.cpp
    src/entities/Projectile.cpp
    src/entities/ResetBox.cpp)

set(COMPONENT_SRCDIRS
    "src/core"
    "src/core/ipc"
    "src/core/logging"
    "src/core/timer"
    "src/core/util"
)

set(COMPONENT_ADD_INCLUDEDIRS
    "include"
)

set(COMPONENT_REQUIRES
    nvs_flash pthread mbedtls fmt 
)

register_component()

if (IDF_VER STRGREATER_EQUAL "v4.0")
    target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-expansion-to-defined)
endif()

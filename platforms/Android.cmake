add_library(RetroEngine SHARED ${RETRO_FILES})
set(DEP_PATH android)
set(RETRO_SDL_VERSION 2)
set(RETRO_OUTPUT_NAME "RetroEngine")
set(COMPILE_OGG TRUE)
set(COMPILE_VORBIS TRUE)
set(COMPILE_THEORA TRUE)
set(OGG_FLAGS -ffast-math -fsigned-char -O2 -fPIC -DPIC -DBYTE_ORDER=LITTLE_ENDIAN -D_ARM_ASSEM_ -w)
set(VORBIS_FLAGS -ffast-math -fsigned-char -O2 -fPIC -DPIC -DBYTE_ORDER=LITTLE_ENDIAN -D_ARM_ASSEM_ -w)
set(THEORA_FLAGS -ffast-math -fsigned-char -O2 -fPIC -DPIC -DBYTE_ORDER=LITTLE_ENDIAN -D_ARM_ASSEM_ -w)
set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/../dependencies/android/SDL)
add_subdirectory(${SDL2_DIR} SDL2)
target_link_libraries(RetroEngine
    android
    EGL
    GLESv2
    log
    z
    jnigraphics
    OpenSLES
    SDL2
)
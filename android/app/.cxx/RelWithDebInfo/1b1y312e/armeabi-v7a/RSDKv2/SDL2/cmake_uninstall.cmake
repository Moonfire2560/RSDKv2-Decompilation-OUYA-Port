if (NOT EXISTS "C:/Github/RSDKv2-Decompilation/android/app/.cxx/RelWithDebInfo/1b1y312e/armeabi-v7a/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"C:/Github/RSDKv2-Decompilation/android/app/.cxx/RelWithDebInfo/1b1y312e/armeabi-v7a/install_manifest.txt\"")
endif(NOT EXISTS "C:/Github/RSDKv2-Decompilation/android/app/.cxx/RelWithDebInfo/1b1y312e/armeabi-v7a/install_manifest.txt")

file(READ "C:/Github/RSDKv2-Decompilation/android/app/.cxx/RelWithDebInfo/1b1y312e/armeabi-v7a/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND C:/Users/austi/AppData/Local/Android/Sdk/cmake/3.22.1/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)


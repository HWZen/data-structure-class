cmake_minimum_required(VERSION 3.18...3.28)
project(cpp-fast-test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
include_directories(.)

# Enable MFC (2 = use shared MFC DLL)
#set(CMAKE_MFC_FLAG 2)

add_compile_options(/utf-8 /Zc:__cplusplus)


add_definitions(-DUNICODE -D_UNICODE)


add_compile_options(/W4 /WX)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.9/5.12.9/msvc2017_64")
message("cmake prefix path: ${CMAKE_PREFIX_PATH}")
find_package(Qt5 COMPONENTS Core Gui Widgets Svg REQUIRED)
#find_package(pugixml CONFIG REQUIRED)

#
set(CMAKE_AUTOMOC ON)


if(WIN32)
    # 生成包含兼容性声明的完整清单文件
    set(ADMIN_MANIFEST_CONTENT
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
            "<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">\n"
            "  <compatibility xmlns=\"urn:schemas-microsoft-com:compatibility.v1\">\n"
            "    <application>\n"
            "      <supportedOS Id=\"{8e0f7a12-bfb3-4fe8-b9a5-48fd0a9d0fb2}\"/>\n"  # Win10
            "    </application>\n"
            "  </compatibility>\n"
            "  <trustInfo xmlns=\"urn:schemas-microsoft-com:asm.v3\">\n"
            "    <security>\n"
            "      <requestedPrivileges>\n"
            "        <requestedExecutionLevel level=\"requireAdministrator\" uiAccess=\"false\"/>\n"
            "      </requestedPrivileges>\n"
            "    </security>\n"
            "  </trustInfo>\n"
            "</assembly>"
    )
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/admin.manifest" "${ADMIN_MANIFEST_CONTENT}")

    # 生成RC文件（注意使用相对路径）
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/admin.rc" "1 RT_MANIFEST \"admin.manifest\"\n")

        set(EMBEDDED_DLL_PATH "${CMAKE_SOURCE_DIR}/CrystalDiskInfo9_4_4.exe")
        if(NOT EXISTS "${EMBEDDED_DLL_PATH}")
                message(FATAL_ERROR "Missing embedded: ${EMBEDDED_DLL_PATH}")
        endif()

        set(EMBEDDED_DLL_PATH2 "${CMAKE_SOURCE_DIR}/LjTool_Disk_Test.dll")
        if(NOT EXISTS "${EMBEDDED_DLL_PATH2}")
                message(FATAL_ERROR "Missing embedded: ${EMBEDDED_DLL_PATH2}")
        endif()


        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/embedded.rc"
                        "101 RCDATA \"${EMBEDDED_DLL_PATH}\"\n"
                        "102 RCDATA \"${EMBEDDED_DLL_PATH2}\"\n"
        )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /utf-8")
    add_definitions(-DUNICODE -D_UNICODE)
endif()



add_executable(run
        temp.cpp
#        ${CMAKE_CURRENT_BINARY_DIR}/admin.rc
#        ${CMAKE_CURRENT_BINARY_DIR}/admin.manifest
)

target_link_directories(run PUBLIC .)
#target_link_libraries(run PUBLIC comctl32 kernel32 user32 gdi32 advapi32)
#set_property(TARGET run PROPERTY WIN32_EXECUTABLE ON)
#target_link_options(run PUBLIC /MANIFEST:NO /MANIFESTUAC:NO)


# target_link_libraries(run PUBLIC pugixml::pugixml)




# 如果编译器target是32位
if(CMAKE_SIZEOF_VOID_P EQUAL 4)

set(absl_DIR ${CMAKE_CURRENT_LIST_DIR}/ThirdLib/abseil/x86/lib/cmake/absl)
set(re2_DIR ${CMAKE_CURRENT_LIST_DIR}/ThirdLib/re2/x86/lib/cmake/re2)
find_package(re2 REQUIRED)
add_library(LjTool_TestDiskBenchmarkExtern SHARED
        DiskExt.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/embedded.rc
)


add_executable(LjTool_TestDiskBenchmarkExternExe
        DiskExt.cpp
       ${CMAKE_CURRENT_BINARY_DIR}/embedded.rc
)
target_compile_definitions(LjTool_TestDiskBenchmarkExternExe PRIVATE ON_EXE)


target_link_libraries(LjTool_TestDiskBenchmarkExtern PUBLIC re2::re2)
target_link_libraries(LjTool_TestDiskBenchmarkExternExe PUBLIC re2::re2)
endif()


#find_package(tomlplusplus CONFIG REQUIRED)
#add_executable(device_detector device_detector.cpp)
#target_link_libraries(device_detector PUBLIC tomlplusplus::tomlplusplus)
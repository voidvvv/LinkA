cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)
project(LinkA VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CHARSET "UTF-8")
#关闭所有警告（有效）
add_compile_options(-w)

include(CTest)
enable_testing()

#链接库的目录,可用相对路径
link_directories(C:/myWareHouse/dev/cpp/vscode_lib)
#配置头文件目录
include_directories(C:/myWareHouse/dev/cpp/include ./include)

# 定义文件
file(GLOB SOURCES1 "src/**/*.cpp")
file(GLOB SOURCES2 "src/*.cpp")
# 添加链接文件
add_executable(LinkA  main.cpp glad.c head.cpp  ${SOURCES1} ${SOURCES2})

# 添加编译参数，下面两个参数分别制定了文件编码格式以及控制台输出编码格式，这样打印中文不会报错
# target_compile_options(LinkA PRIVATE -finput-charset=utf-8)
# target_compile_options(LinkA PRIVATE -fexec-charset=gbk)



# 添加静态依赖库
target_link_libraries(${PROJECT_NAME} 
libglfw3.a 
libfreetyped.a 
libspdlogd.a 
libalut.dll.a 
OpenAL32.lib

liblibnyquist_d.a
libvorbisfile.a 
libvorbis.a
libogg.a
libvorbisenc.a
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

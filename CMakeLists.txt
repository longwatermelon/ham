cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_STANDARD 99)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(ham-rewrite)

add_executable(ham-rewrite
	src/main.c
	src/lexer.c
	src/node.c
	src/parser.c
	src/token.c
	src/utils.c
	src/visitor.c
	include/lexer.h
	include/node.h
	include/parser.h
	include/token.h
	include/utils.h
	include/visitor.h
)

set_property(TARGET ham-rewrite PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

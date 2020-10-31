cmake_minimum_required(VERSION 3.12)
project(HashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashTable main.cpp List.cpp List.h Container.h GroupContainer.h ListAbstract.h Table.h Table.cpp TableAbstract.h Mem.h MemoryManager.h Test.cpp Test.h)
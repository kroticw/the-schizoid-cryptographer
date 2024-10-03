cmake_minimum_required(VERSION 3.30)
project(the_schizoid_cryptographer)

set(CMAKE_CXX_STANDARD 23)
include_directories(include)
add_executable(the_schizoid_cryptographer main.cpp
        src/encrypter/encrypter.cpp
        include/encrypter.h
        src/decrypt/decrypter.cpp
        include/decryptor.h
        include/random.h)


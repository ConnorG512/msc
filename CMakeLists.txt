cmake_minimum_required(VERSION 3.28)
project(MSclae CXX)

set(EXECUTABLE_NAME msc)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
  src/main.cpp
  src/search.cpp
)

add_executable(${EXECUTABLE_NAME} 
  ${SOURCE_FILES}
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  # Libraries:
)

if(WIN32)
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  stdc++exp
)
endif()

target_include_directories(${EXECUTABLE_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/external/cli11"
)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)

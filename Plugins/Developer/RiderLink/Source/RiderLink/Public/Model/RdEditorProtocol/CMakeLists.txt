cmake_minimum_required(VERSION 3.7)
add_library(RdEditorRoot STATIC RdEditorModel/RdEditorModel.Generated.cpp
RdEditorModel/RdEditorModel.Generated.h
RdEditorRoot/RdEditorRoot.Generated.cpp
RdEditorRoot/RdEditorRoot.Generated.h
instantiations.h
instantiations.cpp)

target_include_directories(RdEditorRoot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} RdEditorModel
RdEditorRoot)
target_link_libraries(RdEditorRoot PUBLIC rd_framework_cpp)

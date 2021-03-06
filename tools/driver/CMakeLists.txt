add_swift_host_tool(swift
  api_notes.cpp
  driver.cpp
  autolink_extract_main.cpp
  modulewrap_main.cpp
  swift_format_main.cpp
  LINK_LIBRARIES
    swiftDriver
    swiftFrontendTool
    swiftWALASupport
  LLVM_COMPONENT_DEPENDS
    DebugInfoCodeView
  SWIFT_COMPONENT compiler
)

# Check for the underlying platform
set(LIBJVM_PATH "")
set(LIBCAST_PATH "")

if(APPLE) # for MacOS X
  set(LIBJVM_PATH "$ENV{JAVA_HOME}/jre/lib/server/")
  set(LIBCAST_PATH "$ENV{WALA_HOME}/com.ibm.wala.cast/target/classes/libcast.jnilib")
else() # for Ubuntu
  set(LIBJVM_PATH "$ENV{JAVA_HOME}/jre/lib/amd64/server/")
  set(LIBCAST_PATH "$ENV{WALA_HOME}/com.ibm.wala.cast/target/classes/libcast.so")
endif()

set_property(TARGET swift APPEND_STRING PROPERTY
  LINK_FLAGS " ${LIBCAST_PATH} -L${LIBJVM_PATH} -ljvm -rpath ${LIBJVM_PATH}")

if(HAVE_UNICODE_LIBEDIT)
  target_link_libraries(swift edit)
endif()

swift_create_post_build_symlink(swift
  SOURCE "swift${CMAKE_EXECUTABLE_SUFFIX}"
  DESTINATION "swiftc${CMAKE_EXECUTABLE_SUFFIX}"
  WORKING_DIRECTORY "${SWIFT_RUNTIME_OUTPUT_INTDIR}")

swift_create_post_build_symlink(swift
  SOURCE "swift${CMAKE_EXECUTABLE_SUFFIX}"
  DESTINATION "swift-format${CMAKE_EXECUTABLE_SUFFIX}"
  WORKING_DIRECTORY "${SWIFT_RUNTIME_OUTPUT_INTDIR}")

swift_create_post_build_symlink(swift
  SOURCE "swift${CMAKE_EXECUTABLE_SUFFIX}"
  DESTINATION "swift-autolink-extract${CMAKE_EXECUTABLE_SUFFIX}"
  WORKING_DIRECTORY "${SWIFT_RUNTIME_OUTPUT_INTDIR}")

add_swift_tool_symlink(swiftc swift compiler)
add_swift_tool_symlink(swift-autolink-extract swift autolink-driver)
add_swift_tool_symlink(swift-format swift editor-integration)

# If building as part of clang, make sure the headers are installed.
if(NOT SWIFT_BUILT_STANDALONE)
  add_dependencies(swift clang-headers)
endif()

swift_install_in_component(compiler
    FILES "${SWIFT_RUNTIME_OUTPUT_INTDIR}/swiftc"
    DESTINATION "bin")
swift_install_in_component(autolink-driver
    FILES "${SWIFT_RUNTIME_OUTPUT_INTDIR}/swift-autolink-extract"
    DESTINATION "bin")
swift_install_in_component(editor-integration
    FILES "${SWIFT_RUNTIME_OUTPUT_INTDIR}/swift-format"
    DESTINATION "bin")

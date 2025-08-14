if(NOT CMAKE_TOOLCHAIN_FILE)
  if(${OS_TYPE} STREQUAL "WINDOWS")
    include(config/os_settings/windows.cmake)
  elseif(${OS_TYPE} STREQUAL "LINUX")
    include(config/os_settings/linux.cmake)
  endif()
endif()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
  message("Building for ARM64 architecture")
  # Add any ARM64 specific settings here
endif()
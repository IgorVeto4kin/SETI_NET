# Добавляем флаги компилятора в зависимости от типа сборки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
      "-g"  # Включаем отладочную информацию
      "-O0" # Отключаем оптимизацию
    )
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(
      "/DEBUG"  # Включаем отладочную информацию
      "/Od"     # Отключаем оптимизацию
    )
  endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
      "-O3"       # Включаем максимальную оптимизацию
      "-DNDEBUG"  # Отключаем отладочные утверждения
    )
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(
      "/O2"       # Включаем оптимизацию
      "/DNDEBUG"  # Отключаем отладочные утверждения
    )
  endif()
endif()

# Общие флаги, которые будут добавлены в любом случае
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    "-Wall"
    "-Wextra"
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(
    "/W3"
  )
endif()

# Санитайзеры
if(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message("Sanitizers are enabled (Debug build only)")
    add_compile_options(
      "-fsanitize=address"
      "-fsanitize=undefined"
    )
    add_link_options(
      "-fsanitize=address"
      "-fsanitize=undefined"
    )
  else()
    message(WARNING "Sanitizers are not supported for this compiler.")
  endif()
endif()

# Покрытие кода
if(ENABLE_CODE_COVERAGE OR ENABLE_APP_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("Code coverage enabled for GNU compiler")
    add_compile_options("-fprofile-arcs" "-ftest-coverage")
    add_link_options("-fprofile-arcs" "-ftest-coverage")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Code coverage enabled for Clang compiler")
    add_compile_options("-fprofile-instr-generate" "-fcoverage-mapping")
    add_link_options("-fprofile-instr-generate" "-fcoverage-mapping")
  else()
    message(WARNING "Code coverage is not supported for this compiler")
  endif()
endif()

# Профилирование
if(ENABLE_PROFILING)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("Profiling enabled for GNU compiler")
    add_compile_options("-pg")
    add_link_options("-pg")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Profiling enabled for Clang compiler")
    add_compile_options("-g")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("Profiling enabled for MSVC compiler (using Visual Studio Profiler)")
    # Visual Studio Profiler требует настройки в IDE
  else()
    message(WARNING "Profiling is not supported for this compiler")
  endif()
endif()
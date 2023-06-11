# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif/frameworks/esp-idf-v4.4.4/components/bootloader/subproject"
  "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader"
  "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader-prefix"
  "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader-prefix/tmp"
  "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader-prefix/src/bootloader-stamp"
  "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader-prefix/src"
  "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()

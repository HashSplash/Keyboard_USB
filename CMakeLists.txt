# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(010keyboard_USB)

include(${ZEPHYR_BASE}/samples/subsys/usb/common/common.cmake)
# target_sources(app PRIVATE src/main.c)
# target_sources(app PRIVATE src/kb_misc.c)
# target_sources(app PRIVATE src/kb_misc.h)
# target_include_directories(app PRIVATE include)
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/kb_misc.c)
target_include_directories(app PRIVATE include)
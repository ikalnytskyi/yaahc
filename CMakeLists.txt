#
# Copyright 2012 Igor Kalnitsky <igor@kalnitsky.org>
#
# This file is part of YaAHC.
#
# YaAHC is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# YaAHC is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with YaAHC.  If not, see <http://www.gnu.org/licenses/>.
#

project (yaahc)
cmake_minimum_required (VERSION 2.8)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   available options
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
option (BUILD_TESTS "Build all tests." OFF)
option (BUILD_SAMPLES "Build all samples." OFF)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  compiler settings
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set (CMAKE_COMPILER_IS_CLANG True)
endif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
  set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fvisibility=hidden -std=c++0x")
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_INIT} -g")
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_INIT} -O2")
endif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  project settings
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# set global variable with header path
set (YAAHC_INCLUDE ${yaahc_SOURCE_DIR}/include)

# build libyaahc
add_subdirectory (src/)

# build tests
if (BUILD_TESTS)
    enable_testing ()
    add_subdirectory (test/)
endif (BUILD_TESTS)

# build utils
if (BUILD_SAMPLES)
    add_subdirectory (samples/)
endif (BUILD_SAMPLES)

#
# Copyright 2012 Igor Kalnitsky <igor@kalnitsky.org>
#
# This file is part of yaahc.
#
# yaahc is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# yaahc is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with yaahc.  If not, see <http://www.gnu.org/licenses/>.
#

project (tests)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   boost test framework configuration
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_definitions (-DBOOST_TEST_DYN_LINK)
add_definitions (-DBOOST_TEST_MAIN)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   project settings
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
include_directories(${YAAHC_INCLUDE})

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   test suites
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set (TEST_SUITES
        encoding.cpp
        decoding.cpp
        encdec.cpp
)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   build tests
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
foreach (test_suite ${TEST_SUITES})
    # extract test name (it will be an executable name)
    string (REPLACE ".cpp" "" test_name ${test_suite})
    set (test_name test-${test_name})

    # build test suite
    add_executable (${test_name} ${test_suite})
    target_link_libraries (${test_name}
        ${CMAKE_PROJECT_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )

    # make it available in the ctest
    add_test (${test_name} ${test_name})
endforeach (test_suite)

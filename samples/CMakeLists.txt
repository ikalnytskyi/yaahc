#
# Copyright 2012 Igor Kalnitsky <igor@kalnitsky.org>
#
# This file is part of yaahc.
#
# yaahc is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# yaahc is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with yaahc.  If not, see <http://www.gnu.org/licenses/>.
#

project (samples)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   build samples
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include_directories(${YAAHC_INCLUDE})

set (SOURCES
        compress.cpp
        uncompress.cpp
)


foreach (source ${SOURCES})
    # extract sample name (it will be an executable name)
    string (REPLACE ".cpp" "" sample ${source})

    # build sample
    add_executable (${sample} ${source})
    target_link_libraries (${sample} ${CMAKE_PROJECT_NAME})
endforeach (source)

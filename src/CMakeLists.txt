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

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   build library
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include_directories(${YAAHC_INCLUDE})

set (SOURCES
        tree.cpp
        fgk/tree.cpp
)

add_library (${PROJECT_NAME} SHARED ${SOURCES})

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   install library
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# install headers
install (DIRECTORY "${YAAHC_INCLUDE}/ahc"
    DESTINATION     include
)

# install library
install (TARGETS ${PROJECT_NAME}
    LIBRARY         DESTINATION     lib
)

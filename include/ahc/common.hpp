/*
 * Copyright 2012 Igor Kalnitsky <igor@kalnitsky.org>
 *
 * This file is part of YaAHC.
 *
 * YaAHC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * YaAHC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with YaAHC.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef YAAHC_COMMON_HPP_
#define YAAHC_COMMON_HPP_

#include <cstdint>


namespace ahc
{
/*!
 * A byte type declaration.
 */
typedef std::uint_fast8_t byte_t;

/*!
 * A bit type declaration. Yep, I know it's not a really bit.
 * This type was introduced special for better code readability.
 */
typedef std::uint_fast8_t bit_t;

} // namespace ahc

//! Define an exporting macros
#define DLL_PUBLIC __attribute__ ((visibility ("default")))

#endif // YAAHC_COMMON_HPP_

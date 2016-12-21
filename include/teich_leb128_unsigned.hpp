/*
    This file is part of teich.

    teich is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    teich is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with teich.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <vector>

#include <bitter_read.hpp>
#include <bitter_variable_unsigned_integer.hpp>

///
/// INTERFACE
///

namespace teich {
    namespace leb128 {
        //!
        //! \brief  Decodes unsigned LEB128 data into a bitter::VariableUnsignedInteger
        //!
        //! \tparam  T  the type the source pointer points to,
        //!             should be inferred from the parameter,
        //!             do not set this explicitly
        //!
        //! \param[in]  source  where to read from
        //!
        //! \returns  a bitter::VariableUnsignedInteger
        //!           containing the decoded value
        //!
        //! \par Example
        //! \code
        //!     constexpr uint8_t buffer[] = { 0b11100101, 0b10001110, 0b00100110 };
        //!     decodeUnsigned(buffer); // returns 624485
        //! \endcode
        //!
        template <typename T>
        inline bitter::VariableUnsignedInteger decodeUnsigned(const T* const source);

        //!
        //! \brief  Decodes unsigned LEB128 data into a bitter::VariableUnsignedInteger
        //!
        //! \param[in]  source  the value to encode in unsigned LEB128
        //!
        //! \returns  a collection of bytes containing the encoded data
        //!
        //! \par Example
        //! \code
        //!     // given a bitter::VariableUnsignedInteger called x
        //!     x = 624485
        //!     encodeUnsigned(value); // returns { 0b11100101, 0b10001110, 0b00100110 };
        //! \endcode
        //!
        inline std::vector<uint8_t> encodeUnsigned(bitter::VariableUnsignedInteger source);
    }
}

///
/// IMPLEMENTATION
///

template <typename T>
inline bitter::VariableUnsignedInteger teich::leb128::decodeUnsigned(const T* const source) {
    std::vector<uint8_t> buffer;
    const auto* castSource = reinterpret_cast<const char*>(source);

    for(;;) {
        auto currentByte = *castSource;
        buffer.push_back(currentByte);

        if(bitter::getBit(&currentByte, 7) == bitter::Bit::Zero) {
            // this was the last byte
            break;
        }

        castSource += 1;
    }

    bitter::VariableUnsignedInteger result(static_cast<size_t>(std::ceil(buffer.size() * 7.0) / 8.0f));
    result = 0;

    for(size_t i = buffer.size(); i > 0; --i) {
        const auto bufferIndex = i - 1;

        result <<= 7;
        result += buffer[bufferIndex] & 0x7F;
    }

    return result;
}

inline std::vector<uint8_t> teich::leb128::encodeUnsigned(bitter::VariableUnsignedInteger source) {
    if(source == 0) {
        return { 0 };
    }

    std::vector<uint8_t> result;

    for(;;) {
        // TODO:
        // add feature to libbitter to allow for faster extraction of individual bytes?
        // it might speed this up; check
        // TODO:
        // allow bitwise operations with primitive integer types in libbitter?
        result.push_back(source.toPrimitive<uint8_t>() & 0x7F);
        source >>= 7;

        if(source == 0) {
            break;
        } else {
            bitter::setBit(&result.back(), 7, bitter::Bit::One);
        }
    }

    return result;
}


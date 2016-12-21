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

#include <catch.hpp>

#include <teich_leb128_unsigned.hpp>

#include <sstream>

namespace teich {
    namespace test {
        SCENARIO("unsigned LEB128 data can be decoded correctly") {
            GIVEN("a buffer containing unsigned LEB128 data") {
                WHEN("decodeUnsigned is called upon it") {
                    THEN("the correct data is decoded") {
                        {
                            constexpr uint8_t buffer[] = { 0b00000000 };
                            REQUIRE(leb128::decodeUnsigned(buffer) == 0);
                        }

                        {
                            constexpr uint8_t buffer[] = { 0b00000001 };
                            REQUIRE(leb128::decodeUnsigned(buffer) == 1);
                        }

                        {
                            constexpr uint8_t buffer[] = { 0b01000011 };
                            REQUIRE(leb128::decodeUnsigned(buffer) == 67);
                        }

                        {
                            constexpr uint8_t buffer[] = { 0b10000000, 0b00000001 };
                            REQUIRE(leb128::decodeUnsigned(buffer) == 128);
                        }

                        {
                            constexpr uint8_t buffer[] = { 0b10000000, 0b10000001, 0b00000011 };
                            REQUIRE(leb128::decodeUnsigned(buffer) == 49280);
                        }

                        {
                            constexpr uint8_t buffer[] = { 0b11100101, 0b10001110, 0b00100110 };
                            REQUIRE(leb128::decodeUnsigned(buffer) == 624485);
                        }
                    }
                }
            }
        }
    }
}


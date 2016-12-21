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
#include <vector>

namespace teich {
    namespace test {
        SCENARIO("unsigned LEB128 data can be encoded correctly") {
            GIVEN("a supported numeric value") {
                WHEN("encodeUnsigned is called upon it") {
                    THEN("the correct data is encoded") {
                        {
                            bitter::VariableUnsignedInteger value(2);
                            value = 0;
                            REQUIRE(leb128::encodeUnsigned(value) == (std::vector<uint8_t> { 0b00000000 }));
                        }

                        {
                            bitter::VariableUnsignedInteger value(1);
                            value = 1;
                            REQUIRE(leb128::encodeUnsigned(value) == (std::vector<uint8_t> { 0b00000001 }));
                        }

                        {
                            bitter::VariableUnsignedInteger value(3);
                            value = 67;
                            REQUIRE(leb128::encodeUnsigned(value) == (std::vector<uint8_t> { 0b01000011 }));
                        }

                        {
                            bitter::VariableUnsignedInteger value(4);
                            value = 128;
                            REQUIRE(leb128::encodeUnsigned(value) == (std::vector<uint8_t> { 0b10000000, 0b00000001 }));
                        }

                        {
                            bitter::VariableUnsignedInteger value(2);
                            value = 49280;
                            REQUIRE(leb128::encodeUnsigned(value) == (std::vector<uint8_t> { 0b10000000, 0b10000001, 0b00000011 }));
                        }

                        {
                            bitter::VariableUnsignedInteger value(5);
                            value = 624485;
                            REQUIRE(leb128::encodeUnsigned(value) == (std::vector<uint8_t> { 0b11100101, 0b10001110, 0b00100110 }));
                        }
                    }
                }
            }
        }
    }
}


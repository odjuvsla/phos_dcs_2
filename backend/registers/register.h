/*
    Library for controlling and configuring the electronics for
    the PHOS detector at the ALICE Experiment

    Copyright (C) 2011  Oystein Djuvsland <oystein.djuvsland@gmail.com>,
                        Henrik Qvigstad <henrik.qvigstad@cern.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef REGISTER_H
#define REGISTER_H
#include <sys/types.h>
#include <bitset>
#include <stdint.h>
#include <iostream>

/*
 * This class serves as a base for specific registers.
 * It defines the common instance interface members and typesl.
 */
class Register
{
  public:
    virtual ~Register() {;}

    // Register namespace types
    /** The Register Access */
    enum Access { /** Read */       R=4,
		  /** Write */      W=2,
		  /** Read/Write */ RW=6  };
    enum Type { ALTRO, BC, RCU, TRU};
    typedef int16_t Address;
    /** Value of Register,
     *
     * may represent value to be written, or value read from Register */
    typedef int32_t Value;

    // Register Interface:
    virtual Register::Access GetAccess() const = 0;
    virtual Register::Address GetAddress() const = 0;
    virtual Register::Type GetType() const = 0;
    virtual Register::Value GetValue() const = 0;
    virtual void SetValue(Register::Value value) = 0;


    operator Register::Value() { return GetValue(); }

    // Convenience Functions
    template<size_t from, size_t to, size_t N>
    static unsigned long ReadValue(const std::bitset<N>& bits);

    template<size_t from, size_t N, size_t M>
    static unsigned long InsertValue(std::bitset<N>& bits, const std::bitset<M>& inserts);
};


template<size_t from, size_t to, size_t N>
unsigned long Register::ReadValue(const std::bitset<N>& bits)
{
  // strips the [to:from] from @param bits and returns
  // IMPORTANT: defined behavior requires: bits-in-long >= N > to > from !

  // shift bits to left and strip down to size:
  const std::bitset<to-from+1> newbits ( (bits >> from).to_ulong() );
  return newbits.to_ulong();
}

template<size_t from, size_t N, size_t M>
unsigned long Register::InsertValue(std::bitset<N>& bits, const std::bitset<M>& inserts)
{
  // inserts @param inserts into @param bits, at @param from
  // IMPORTANT: defined behavior requires: 32 >= N > from,  N => from+M,.

  const std::bitset<N> ones(0xFFFFFFFF);
  const std::bitset<N> wipeset( (ones << from+M)  |  ( ones >> (N-from))); // 0 at insert, 1 elsewere
  const std::bitset<N> insertset( std::bitset<N>(inserts.to_ulong()) << from); // inserts at insert, 0 elsewere
  bits = ( (bits & wipeset) | insertset); // wipe insert, and insert inserts at insert
  return bits.to_ulong();
}


#endif // REGISTER_H

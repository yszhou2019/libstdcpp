// Copyright (C) 2012-2022 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// libstdc++/55320

// { dg-do run { target c++11 } }

#include <functional>
#include <testsuite_hooks.h>

struct X
{
  X() { ++count; }
  X(const X&) { throw 1; }
  ~X() { --count; }
  void operator()() { }
  static int count;
};

int X::count = 0;

int main()
{
  try
  {
    std::function<void()> f = X();
  }
  catch (int)
  {
    VERIFY( X::count == 0 );
  }
}

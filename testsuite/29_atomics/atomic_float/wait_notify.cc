// { dg-options "-std=gnu++2a" }
// { dg-do run { target c++2a } }
// { dg-require-gthreads "" }
// { dg-additional-options "-pthread" { target pthread } }
// { dg-add-options libatomic }

// Copyright (C) 2020-2022 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.


#include <atomic>
#include <thread>

#include <testsuite_hooks.h>

template<typename Tp>
  void
  check()
  {
    std::atomic<Tp> a{ 1.0 };
    VERIFY( a.load() != 0.0 );
    a.wait( 0.0 );
    std::thread t([&]
      {
        a.store(0.0);
        a.notify_one();
      });
    a.wait(1.0);
    t.join();
  }

int
main ()
{
  check<float>();
  check<double>();
  return 0;
}

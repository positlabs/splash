/*
 * Copyright (C) 2015 Emmanuel Durand
 *
 * This file is part of Splash.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Splash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Splash.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * @spinlock.h
 * Spinlock, when mutexes have too much overhead
 */

#ifndef SPLASH_SPINLOCK_H
#define SPLASH_SPINLOCK_H

#include <atomic>

namespace Splash
{

/*************/
class Spinlock
{
  public:
    void lock()
    {
        while (_lock.test_and_set(std::memory_order_acquire))
        {
        }
    }

    void unlock() { _lock.clear(std::memory_order_release); }

    bool try_lock() { return !_lock.test_and_set(std::memory_order_acquire); }

  private:
    std::atomic_flag _lock = ATOMIC_FLAG_INIT;
};

} // end of namespace

#endif // SPLASH_SPINLOCK_H

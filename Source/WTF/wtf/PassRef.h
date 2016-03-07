/*
 *  Copyright (C) 2013-2014 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#ifndef WTF_PassRef_h
#define WTF_PassRef_h

#include "Assertions.h"
#include <cstddef>
#include <utility>

namespace WTF {

template<typename T> class PassRef;
template<typename T> class PassRefPtr;
template<typename T> class Ref;
template<typename T> class RefPtr;

template<typename T> PassRef<T> adoptRef(T&);

inline void adopted(const void*) { }

template<typename T> class PassRef {
public:
    PassRef(T&);
    PassRef(PassRef&&);
    template<typename U> PassRef(const Ref<U>&);
    template<typename U> PassRef(PassRef<U>);

    const T& get() const;
    T& get();

    const T* ptr() const;
    T* ptr();

    T& leakRef() WARN_UNUSED_RETURN;

    ~PassRef();

private:
    friend PassRef adoptRef<T>(T&);

    template<typename U> friend class PassRef;
    template<typename U> friend class PassRefPtr;
    template<typename U> friend class Ref;
    template<typename U> friend class RefPtr;

    enum AdoptTag { Adopt };
    PassRef(T&, AdoptTag);

    T* m_ptr;
    bool m_gaveUpReference;
};

template<typename T> inline PassRef<T>::PassRef(T& reference)
    : m_ptr(&reference)
{
    m_ptr->ref();
}

template<typename T> inline PassRef<T>::PassRef(PassRef&& other)
    : m_ptr(&other.leakRef())
{
}

template<typename T> template<typename U> inline PassRef<T>::PassRef(PassRef<U> other)
    : m_ptr(&other.leakRef())
{
}

template<typename T> template<typename U> inline PassRef<T>::PassRef(const Ref<U>& other)
    : m_ptr(static_cast<T*>(const_cast<U*>(other.ptr())))
{
    ASSERT(m_ptr);
    m_ptr->ref();
}

template<typename T> PassRef<T>::~PassRef()
{
    if (m_ptr)
        m_ptr->deref();
}

template<typename T> inline const T& PassRef<T>::get() const
{
    ASSERT(m_ptr);
    return *m_ptr;
}

template<typename T> inline T& PassRef<T>::get()
{
    ASSERT(m_ptr);
    return *m_ptr;
}

template<typename T> const T* PassRef<T>::ptr() const
{
    ASSERT(m_ptr);
    return m_ptr;
}

template<typename T> T* PassRef<T>::ptr()
{
    ASSERT(m_ptr);
    return m_ptr;
}

template<typename T> inline T& PassRef<T>::leakRef()
{
    ASSERT(m_ptr);
    T* leakedPtr = m_ptr;
    m_ptr = nullptr;
    return *leakedPtr;
}

template<typename T> inline PassRef<T>::PassRef(T& reference, AdoptTag)
    : m_ptr(&reference)
{
}

template<typename T> inline PassRef<T> adoptRef(T& reference)
{
    adopted(&reference);
    return PassRef<T>(reference, PassRef<T>::Adopt);
}

template<typename T, typename... Args> inline PassRef<T> createRefCounted(Args&&... args)
{
    return adoptRef(*new T(std::forward<Args>(args)...));
}

} // namespace WTF

using WTF::PassRef;
using WTF::adoptRef;
using WTF::createRefCounted;

#endif // WTF_PassRef_h

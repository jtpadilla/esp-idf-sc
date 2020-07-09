#pragma once

#include <memory>
#include <type_traits>

namespace smooth::core::util
{
    /// \brief The purpose of this template function is to allow forcing instantiation of classes to be held
    /// only by a std::shared_ptr, by making T's constructor protected. This us useful when you want
    /// to use std::shared_from_this and prevent an instance being directly created with new() which
    /// would result usage of in std::shared_from_this in an exception.
    template<typename T, typename... Args>
    auto create_protected_shared(Args&& ... args)
    {
        class CreationWrapper
            : public T
        {
            public:
                explicit CreationWrapper(Args&& ... args)
                        : T(std::forward<Args>(args)...)
                {}
        };

        return std::make_shared<CreationWrapper>(std::forward<Args>(args)...);
    }

    /// \brief The purpose of this template function is to allow forcing instantiation of classes to be held
    /// only by a std::unique_ptr, by making T's constructor protected. As there's no std::unique_from_this,
    /// this method has limited usage compared to create_protected_shared.
    template<typename T, typename... Args>
    auto create_protected_unique(Args&& ... args)
    {
        class CreationWrapper
            : public T
        {
            public:
                explicit CreationWrapper(Args&& ... args)
                        : T(std::forward<Args>(args)...)
                {}
        };

        return std::make_unique<CreationWrapper>(std::forward<Args>(args)...);
    }
}

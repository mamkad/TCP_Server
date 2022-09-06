#pragma once

// вспомогательный класс для запрета присваивания
class NonAssignable
{
public:
    NonAssignable& operator=(const NonAssignable &) = delete;
    virtual ~NonAssignable() = default;
};
 
 
/// вспомогательный класс для запрета копирования
class NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable &) = delete;
    virtual ~NonCopyable() = default;
};
 
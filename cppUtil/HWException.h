#pragma once
#include "cppUtil/tools.h"
#include <exception>
#include <format>
#include <string_view>


class HWException : public std::exception
{
public:
    explicit HWException(std::wstring_view msg) : std::exception( BT8 msg.data())
    {

    }
};

#define THROW_HW_EXCEPTION(Format, ...)                                                                                \
{                                                                                                                  \
constexpr auto file_path{ std::wstring_view{ __FILEW__ } };                                                    \
constexpr auto file_name{ file_path.substr(file_path.find_last_of('\\') + 1) };                                \
throw HWException{std::format(L"{}@{}: " Format, file_name, __LINE__, ##__VA_ARGS__) };                       \
}

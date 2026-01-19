//
// Created by HWZ on 2023/4/23.
//

#ifndef ZHUAN_HARDWARE_LIB_INC_TOOLS_H_
#define ZHUAN_HARDWARE_LIB_INC_TOOLS_H_

#include <string>
#include <string_view>
#include <type_traits>
#include <format>
#include <chrono>

#include <Windows.h>
#include <comutil.h>

#ifndef defer
template<typename F>
struct deferrer
{
    F f;
    bool cancelled{ false };
    ~deferrer()
    {
        if (!cancelled)
            f();
    }
    void cancel()
    {
        cancelled = true;
    }
};
#define DEFER_LINE(line) defer##line
#define DEFER_NAME(name) DEFER_LINE(name)
#define defer(code) auto DEFER_NAME(__LINE__) = deferrer{.f = (code)}

#define defer_cancel(line)  DEFER_NAME(line).cancel()
#endif // defer

#ifndef MV
struct MvThing{
    template <class Ty>
    std::remove_reference_t<Ty>&& operator*(Ty&& thing) const
    {
        return static_cast<std::remove_cvref_t<Ty>&&>(thing);
    }
};
// 'MV' is a macro that can be used to move an object, 'MV obj' is equivalent to 'std::move(obj)'
#define MV MvThing{} *
#endif // MV

inline std::wstring GetLastErrorString(DWORD errorCode = GetLastError())
{
    LPWSTR buffer{ nullptr };
    size_t size =
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);

    std::wstring errorDescription(buffer, size);
    LocalFree(buffer);

    return std::format(L"error code: {} message: {}", errorCode, errorDescription);
}


template<class CharT>
struct std::formatter<_bstr_t, CharT> : std::formatter<CharT*, CharT>
{
    template<class FormatContext>
    auto format(const _bstr_t &t, FormatContext& fc) const
    {
        return std::formatter<CharT*, CharT>::format((CharT*)t, fc);
    }
};

#ifndef BT
class BstrHelper{
public:
    _bstr_t operator*(const auto &str){
        return _bstr_t(str);
    }
};
#define BT BstrHelper{} *
#endif // BT

#ifndef BT8
class BstrHelper8{
public:
    /**
     * @brief bstr8_t is a helper class like _bstr_t, but it converts utf-8 narrow characters and utf-16 wide characters to and from each other
     */
    class bstr8_t{

    public:
        bstr8_t() = delete;
        bstr8_t(const bstr8_t& other) = default;
        bstr8_t(bstr8_t&& other) noexcept = default;
        bstr8_t(std::string_view str);
        bstr8_t(std::wstring_view wstr);
        ~bstr8_t() = default;
        bstr8_t& operator=(const bstr8_t& other) = default;
        bstr8_t& operator=(bstr8_t&& other) = default;
        bstr8_t& operator=(std::string_view str);
        bstr8_t& operator=(std::wstring_view wstr);
        operator char*();
        operator const char *()const;
        operator wchar_t*();
        operator const wchar_t*()const;
        char *u8data();
        const char *u8data()const;
        wchar_t *u16data();
        const wchar_t *u16data()const;
    private:
        std::string utf8str;
        std::wstring utf16str;

    };

    bstr8_t operator*(const auto &str){
        return bstr8_t(str);
    }
};

template<class CharT>
struct std::formatter<BstrHelper8::bstr8_t, CharT> : std::formatter<const CharT*, CharT>
{
    template<class FormatContext>
    auto format(const BstrHelper8::bstr8_t &t, FormatContext& fc) const
    {
        return std::formatter<const CharT*, CharT>::format((const CharT*)t, fc);
    }
};

/**
 * @brief BT8 is a helper for converting string to bstr8_t
 * @note Usage: BT8 "obj can be converted to std::string_view or std::wstring_view"
 */
#define BT8 BstrHelper8{} *


inline BstrHelper8::bstr8_t::bstr8_t(std::string_view str)
{
    operator=(str);
}

inline BstrHelper8::bstr8_t::bstr8_t(std::wstring_view wstr)
{
    operator=(wstr);
}

inline BstrHelper8::bstr8_t& BstrHelper8::bstr8_t::operator=(std::string_view str)
{
    utf8str = str;
    auto len = MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), nullptr, 0);
    if (len == 0){
        utf8str.clear();
        utf16str.clear();
        return *this;
    }
    utf16str.resize(len);
    auto res = MultiByteToWideChar(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), utf16str.data(), len);
    if (res == 0){
        utf8str.clear();
        utf16str.clear();
        return *this;
    }

    return *this;
}

inline BstrHelper8::bstr8_t& BstrHelper8::bstr8_t::operator=(std::wstring_view wstr)
{
    utf16str = wstr;
    auto len = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
    if (len == 0){
        utf8str.clear();
        utf16str.clear();
        return *this;
    }
    utf8str.resize(len);
    auto res = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), utf8str.data(), len, nullptr, nullptr);
    if (res == 0){
        utf8str.clear();
        utf16str.clear();
        return *this;
    }
    return *this;
}

inline BstrHelper8::bstr8_t::operator char*()
{
    return utf8str.data();
}

inline BstrHelper8::bstr8_t::operator const char*() const
{
    return utf8str.c_str();
}

inline BstrHelper8::bstr8_t::operator wchar_t*()
{
    return utf16str.data();
}

inline BstrHelper8::bstr8_t::operator const wchar_t*() const
{
    return utf16str.c_str();
}

inline char* BstrHelper8::bstr8_t::u8data()
{
    return utf8str.data();
}

inline wchar_t* BstrHelper8::bstr8_t::u16data()
{
    return utf16str.data();
}

inline const char* BstrHelper8::bstr8_t::u8data() const
{
    return utf8str.data();
}

inline const wchar_t* BstrHelper8::bstr8_t::u16data() const
{
    return utf16str.data();
}



#endif // BT8


/**
 * @brief A timer class for measuring elapsed time
 * 
 * This class provides functionality to measure elapsed time using high resolution clock.
 * All time measurements are in milliseconds.
 */
class ElapsedTimer{
public:
    /**
     * @brief Construct a new Elapsed Timer object
     * 
     * Initializes the timer with current time as start point
     */
    ElapsedTimer() : start_time(std::chrono::high_resolution_clock::now()) {};

    /**
     * @brief Reset the timer to current time
     */
    void start() { start_time = std::chrono::high_resolution_clock::now(); };

    /**
     * @brief Get elapsed time and restart the timer
     * 
     * @return uint64_t Elapsed time in milliseconds
     */
    uint64_t restart()
    {
        auto ret = elapsed();
        start();
        return ret;
    };

    /**
     * @brief Get elapsed time since last start/restart
     * 
     * @return uint64_t Elapsed time in milliseconds
     */
    uint64_t elapsed() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
    };

private:
    std::chrono::high_resolution_clock::time_point start_time; ///< Time point when timer was started
};

#endif //ZHUAN_HARDWARE_LIB_INC_TOOLS_H_

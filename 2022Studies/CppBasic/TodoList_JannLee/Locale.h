#pragma once
#ifndef PRACTICAL_CPP_LOCALE_H
#define PRACTICAL_CPP_LOCALE_H


#include <locale>
#include <string>


namespace practicalCpp
{
    class Locale
    {
    public:
        Locale();
        virtual ~Locale();

        Locale(const Locale&) = delete;
        Locale& operator=(const Locale&) = delete;

        static std::wstring AnsiToUnicode(const std::string& ansi);
        static std::string UnicodeToUtf8(const std::wstring& unicode);
        static std::string AnsiToUtf8(const std::string& ansi);

    private:
        std::locale beforeGlobalLocale_;
        std::locale beforeCoutLocale_;
        std::uint32_t beforeOutputCodePage_;
    };
}

#endif // PRACTICAL_CPP_LOCALE_H
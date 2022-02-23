#include "Locale.h"
#include <windows.h>
#include <boost/locale.hpp>
#include <fmt/format.h>

namespace practicalCpp
{
    using boost::locale::translate;
    using fmt::format;

    Locale::Locale()
    {
        boost::locale::generator generator;

        generator.add_messages_path(".");
        generator.add_messages_domain("locale");

        // 일본어 테스트용
        // beforeGlobalLocale_ = std::locale::global(generator("ja_JP.UTF-8"));
        beforeGlobalLocale_ = std::locale::global(generator(""));
        beforeCoutLocale_ = std::cout.imbue(std::locale());

        // UTF-8 문자열 출력을 위해 출력 코드 페이지를 UTF-8로 지정합니다.
        beforeOutputCodePage_ = ::GetConsoleOutputCP();
        ::SetConsoleOutputCP(CP_UTF8);
    }
     
    Locale::~Locale()
    {
        ::SetConsoleOutputCP(beforeOutputCodePage_);
        std::cout.imbue(beforeCoutLocale_);
        std::locale::global(beforeGlobalLocale_);
    }

    std::wstring Locale::AnsiToUnicode(const std::string& ansi)
    {
        std::wstring unicode;

        if (!ansi.empty())
        {
            const auto& src = ansi.c_str();
            const auto& length = static_cast<int>(ansi.length());
            if (auto unicodeLength = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, src, length, nullptr, 0);
                unicodeLength > 0)
            {
                auto buffer = std::make_unique<wchar_t[]>(static_cast<size_t>(unicodeLength) + 1);
                if (::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, src, length, buffer.get(), unicodeLength) <= 0)
                {
                    throw std::logic_error(format(translate("MultiByteToWideChar Error with {}").str(), ::GetLastError()));
                }
                unicode = buffer.get();
            }
            else
            {
                throw std::logic_error(format(translate("MultiByteToWideChar Error with {}").str(), ::GetLastError()));
            }
        }

        return unicode;
    }

    std::string Locale::UnicodeToUtf8(const std::wstring& unicode)
    {
        std::string utf8;

        if (!unicode.empty())
        {
            const auto& src = unicode.c_str();
            const auto& length = static_cast<int>(unicode.length());
            if (auto utf8Length = ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, src, length, nullptr, 0, nullptr, nullptr);
                utf8Length > 0)
            {
                auto buffer = std::make_unique<char[]>(static_cast<size_t>(utf8Length) + 1);
                if (::WideCharToMultiByte(CP_UTF8, 0, src, length, buffer.get(), utf8Length, nullptr, nullptr) <= 0)\
                {
                    throw std::logic_error(format(translate("WideCharToMultiByte Error with {}").str(), ::GetLastError()));
                }
                utf8 = buffer.get();
            }
            else
            {
                throw std::logic_error(format(translate("WideCharToMultiByte Error with {}").str(), ::GetLastError()));
            }
        }

        return utf8;
    }

    std::string Locale::AnsiToUtf8(const std::string& ansi)
    {
        return UnicodeToUtf8(AnsiToUnicode(ansi));
    }
}

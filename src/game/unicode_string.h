#pragma once

#include <wchar.h>

class AsciiString;

class UnicodeString {
public:
    UnicodeString();
    UnicodeString(wchar_t c);
    UnicodeString(const wchar_t *str);
    UnicodeString(const wchar_t *str, int len);
    UnicodeString(const UnicodeString &that);
    UnicodeString(const UnicodeString &that, int start, int len);
    ~UnicodeString();
    UnicodeString &operator=(const UnicodeString &that);
    UnicodeString &operator=(wchar_t c);
    UnicodeString &operator=(const wchar_t *str);
    UnicodeString &operator+=(const UnicodeString &that);
    UnicodeString &operator+=(wchar_t c);
    UnicodeString &operator+=(const wchar_t *str);
    void __cdecl format(UnicodeString fmt, ...);
    void translate(const AsciiString &that);

private:
    wchar_t *m_text;
};

#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2017 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace some string methods, including
//	conversions to or from strings.
//----------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <vector>

class StringHelper {
public:
    static std::vector<std::wstring> split(const std::wstring &source, wchar_t delimiter) {
        std::vector<std::wstring> output;
        std::wistringstream ss(source);
        std::wstring nextItem;

        while (std::getline(ss, nextItem, delimiter)) {
            output.push_back(nextItem);
        }

        return output;
    }

    template<typename T>
    static std::wstring toString(const T &subject) {
        std::wostringstream ss;
        ss << subject;
        return ss.str();
    }

    template<typename T>
    static T fromString(const std::wstring &subject) {
        std::wistringstream ss(subject);
        T target;
        ss >> target;
        return target;
    }
};

/**********************************************************************
OJTool: Get problem and submit code for OJ just from your CLI!
Copyright (C) 2024  langningchen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
**********************************************************************/

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std::literals::string_literals;
#define TRIGGER_ERROR(ErrorDetail)                               \
    throw Exception("an error! \n"s +                            \
                    "\n" +                                       \
                    std::string(ErrorDetail) + "\n" +            \
                    "File: " + __FILE__ + "\n" +                 \
                    "Line: " + std::to_string(__LINE__) + "\n" + \
                    "Function: " + __func__ + "\n" +             \
                    "Errno: " + std::to_string(errno))
#define TRIGGER_ERROR_WITH_CODE(ErrorDetail, ErrorCode)               \
    throw Exception("an error! " + std::to_string(ErrorCode) + "\n" + \
                    "\n" +                                            \
                    std::string(ErrorDetail) + "\n" +                 \
                    "File: " + __FILE__ + "\n" +                      \
                    "Line: " + std::to_string(__LINE__) + "\n" +      \
                    "Function: " + __func__ + "\n" +                  \
                    "Errno: " + std::to_string(errno))
#define TRIGGER_ERROR_WITH_CODE_AND_MESSAGE(ErrorDetail, ErrorCode, ErrorMessage)           \
    throw Exception("an error! " + std::to_string(ErrorCode) + ": " + ErrorMessage + "\n" + \
                    "\n" +                                                                  \
                    std::string(ErrorDetail) + "\n" +                                       \
                    "File: " + __FILE__ + "\n" +                                            \
                    "Line: " + std::to_string(__LINE__) + "\n" +                            \
                    "Function: " + __func__ + "\n" +                                        \
                    "Errno: " + std::to_string(errno))

#define CLN_TRY \
    try {       \
        try {
#define CLN_CATCH                                                            \
    }                                                                        \
    catch (const configor::configor_exception &ExceptionData) {              \
        TRIGGER_ERROR("a JSON error: "s + ExceptionData.what());             \
    }                                                                        \
    catch (const std::logic_error &ExceptionData) {                          \
        TRIGGER_ERROR("a standard logic error: "s + ExceptionData.what());   \
    }                                                                        \
    catch (const std::runtime_error &ExceptionData) {                        \
        TRIGGER_ERROR("a standard runtime error: "s + ExceptionData.what()); \
    }                                                                        \
    catch (const std::exception &ExceptionData) {                            \
        TRIGGER_ERROR("a standard error: "s + ExceptionData.what());         \
    }                                                                        \
    }                                                                        \
    catch (const Exception &ExceptionData) {                                 \
        std::cerr << ExceptionData.what() << std::endl;                      \
        exit(1);                                                             \
    }

std::string
GetStackTrace();

class Exception {
  private:
    std::string Content = "";

  public:
    Exception();
    Exception(const std::string &message);
    std::string what() const;
    ~Exception();
};

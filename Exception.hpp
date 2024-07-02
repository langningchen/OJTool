#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std::literals::string_literals;
#define TRIGGER_ERROR(ErrorDetail)                                  \
    throw CLNException("an error! \n"s +                            \
                       "\n" +                                       \
                       std::string(ErrorDetail) + "\n" +            \
                       "File: " + __FILE__ + "\n" +                 \
                       "Line: " + std::to_string(__LINE__) + "\n" + \
                       "Function: " + __func__ + "\n" +             \
                       "Errno: " + std::to_string(errno))
#define TRIGGER_ERROR_WITH_CODE(ErrorDetail, ErrorCode)                  \
    throw CLNException("an error! " + std::to_string(ErrorCode) + "\n" + \
                       "\n" +                                            \
                       std::string(ErrorDetail) + "\n" +                 \
                       "File: " + __FILE__ + "\n" +                      \
                       "Line: " + std::to_string(__LINE__) + "\n" +      \
                       "Function: " + __func__ + "\n" +                  \
                       "Errno: " + std::to_string(errno))
#define TRIGGER_ERROR_WITH_CODE_AND_MESSAGE(ErrorDetail, ErrorCode, ErrorMessage)              \
    throw CLNException("an error! " + std::to_string(ErrorCode) + ": " + ErrorMessage + "\n" + \
                       "\n" +                                                                  \
                       std::string(ErrorDetail) + "\n" +                                       \
                       "File: " + __FILE__ + "\n" +                                            \
                       "Line: " + std::to_string(__LINE__) + "\n" +                            \
                       "Function: " + __func__ + "\n" +                                        \
                       "Errno: " + std::to_string(errno))

#define CLN_TRY \
    try {       \
        try {
#define CLN_CATCH                                                        \
    }                                                                    \
    catch (const configor::configor_exception &Exception) {              \
        TRIGGER_ERROR("a JSON error: "s + Exception.what());             \
    }                                                                    \
    catch (const std::logic_error &Exception) {                          \
        TRIGGER_ERROR("a standard logic error: "s + Exception.what());   \
    }                                                                    \
    catch (const std::runtime_error &Exception) {                        \
        TRIGGER_ERROR("a standard runtime error: "s + Exception.what()); \
    }                                                                    \
    catch (const std::exception &Exception) {                            \
        TRIGGER_ERROR("a standard error: "s + Exception.what());         \
    }                                                                    \
    }                                                                    \
    catch (const CLNException &Exception) {                              \
        std::cerr << Exception.what() << std::endl;                      \
        exit(1);                                                         \
    }

std::string
GetStackTrace();

class CLNException {
  private:
    std::string Content = "";

  public:
    CLNException();
    CLNException(const std::string &message);
    std::string what() const;
    ~CLNException();
};

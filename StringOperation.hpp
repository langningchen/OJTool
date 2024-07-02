#pragma once

#include <Exception.hpp>
#include <assert.h>
#include <fstream>
#include <string.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#define VAR_DUMP(e) std::cout << #e << "=" << e << std::endl
#define SPILT_LINE std::cout << std::endl                                     \
                             << "------------------------------" << std::endl \
                             << std::endl
#define REPORT_POSITION                                   \
    std::cout << "Report current position: " << std::endl \
              << "File: " << __FILE__ << std::endl        \
              << "Line: " << __LINE__ << std::endl        \
              << "Function: " << __func__ << std::endl;
void GetCurrentDir();
std::string StringReplaceAll(std::string Data, std::string Before, std::string After);
std::string StringReplaceAllNoLoop(std::string Data, std::string Before, std::string After);
std::string GetStringBetween(std::string Data, std::string Start, std::string End);
std::vector<std::string> SpiltString(std::string Input, std::string Separator);
bool IfFileExist(std::string FileName);
std::string GetDataFromFileToString(std::string FileName = "/tmp/Body.tmp");
void SetDataFromStringToFile(std::string FileName, std::string Data);
std::string FixString(std::string Data);
#ifndef _WIN32
std::string GetUserHomeFolder();
#endif

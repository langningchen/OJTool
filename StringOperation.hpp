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
std::string GetCurrentDir();
std::string StringReplaceAll(std::string Data, std::string Before, std::string After);
std::string StringReplaceAllNoLoop(std::string Data, std::string Before, std::string After);
std::string GetStringBetween(std::string Data, std::string Start, std::string End);
std::vector<std::string> SpiltString(std::string Input, std::string Separator);
bool IfFileExist(std::string FileName);
std::string GetDataFromFileToString(std::string FileName = "/OJTool/Body.tmp");
void SetDataFromStringToFile(std::string FileName, std::string Data);
std::string FixString(std::string Data);
std::string GetUserHomeFolder();
std::string GetRealpath(std::string Input);
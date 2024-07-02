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

#include <Curl.hpp>
#include <MD5.hpp>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <tidy/tidy.h>
#include <tidy/tidybuffio.h>

class TOOL {
  public:
    std::string Username;
    std::string Password;
    std::string OJ;
    std::string Operation;
    std::string ProblemID;

    void Execute();

    static std::string GetSourceCodePath(std::string Filename);
    static std::string GetCPHFileName(std::string Filename);
    static std::string TidyHTMLDocument(std::string Input);
};

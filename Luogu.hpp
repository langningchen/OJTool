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
#include <OJ.hpp>
#include <map>
#include <string>

class LUOGU : public OJ {
  private:
    std::map<int, std::string> LanguageName, LanguageMarkdownName;
    std::map<int, std::pair<std::string, std::string>> DifficultyName, TagName, RecordName;
    std::map<std::string, std::string> TypeName, ColorList;
    std::string GetCSRF();

  public:
    LUOGU();
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
    void ClockIn();
    void GetAnswerOrTips(std::string ProblemID);
};

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
#include <string>
#include <tinyxml/tinyxml.h>

class CODEFORCES : public OJ {
  private:
    const std::string ftaa = "rv5q0yv00p85nhpyi7";
    const std::string bfaa = "f1b3f18c715565b589b7823cda7448ce";
    std::string GetCSRF();
    std::string OutputPre(TiXmlElement *Input);
    std::string Output(TiXmlElement *Input, bool InLatex = false);
    std::string ToNormalName(std::string Input);

  public:
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
};

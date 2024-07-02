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

    static std::string GetCPHFileName(std::string Path, std::string FileName);
    static std::string TidyHTMLDocument(std::string Input);
};

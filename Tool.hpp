#pragma once
#include "Curl.hpp"
#include "MD5.hpp"
#include "tidy/tidy.h"
#include "tidy/tidybuffio.h"
#include <iostream>
#include <map>
#include <regex>
#include <string>
using namespace std;

class TOOL {
  public:
    string Username;
    string Password;
    string OJ;
    string Operation;
    string ProblemID;

    void Execute();

    static void Speak(string Name);
    static string GetCPHFileName(string Path, string FileName);
    static string TidyHTMLDocument(string Input);
};

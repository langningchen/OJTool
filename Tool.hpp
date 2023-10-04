#pragma once

#include <string>
#include <iostream>
#include <regex>
#include <map>
#include "Curl.hpp"
#include "MD5.hpp"
#include "tidy/tidy.h"
#include "tidy/tidybuffio.h"
using namespace std;

class TOOL
{
public:
    string Username;
    string Password;
    string OJ;
    string Operation;
    string ProblemID;

    void Execute();

    static void Speak(string Name);
#ifndef _WIN32
    static string GetCPHFileName(string Path, string FileName);
#endif
    static string TidyHTMLDocument(string Input);
};

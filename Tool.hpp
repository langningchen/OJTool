#ifndef TOOL_HPP
#define TOOL_HPP

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
    string QuestionID;

    void Execute();

    static void Speak(string Name);
    static string GetCPHFileName(string Path, string FileName);
    static string TidyHTMLDocument(string Input);
};

#endif

#pragma once

#include <string>
#include <map>
#include "OJ.hpp"
using namespace std;

class LUOGU : public OJ
{
private:
    map<int, string> LanguageName, LanguageMarkdownName;
    map<int, pair<string, string>> DifficultyName, TagName, RecordName;
    map<string, string> TypeName, ColorList;
    string GetCSRF();

public:
    LUOGU();
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
    void ClockIn();
    void GetAnswerOrTips(string ProblemID);
};

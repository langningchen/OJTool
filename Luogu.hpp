#ifndef LUOGU_HPP
#define LUOGU_HPP

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
    void GetQuestionDetail(string QuestionID);
    void SubmitCode(string QuestionID);
    void ClockIn();
    void GetAnswerOrTips(string QuestionID);
};

#endif

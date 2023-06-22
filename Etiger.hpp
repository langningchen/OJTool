#ifndef ETIGER_HPP
#define ETIGER_HPP

#include <string>
#include <map>
#include "OJ.hpp"
using namespace std;

class ETIGER : public OJ
{
private:
    string Token = "";
    map<int, pair<string, string>> DifficultyName;

public:
    ETIGER();
    void Login(string Username, string Password);
    void GetQuestionDetail(string QuestionID);
    void SubmitCode(string QuestionID);
    void ClockIn();
    void GetAnswerOrTips(string QuestionID);
};

#endif

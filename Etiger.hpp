#pragma once
#include "OJ.hpp"
#include <map>
#include <string>
using namespace std;

class ETIGER : public OJ {
  private:
    string Token = "";
    map<int, pair<string, string>> DifficultyName;

  public:
    ETIGER();
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
    void ClockIn();
    void GetAnswerOrTips(string ProblemID);
};

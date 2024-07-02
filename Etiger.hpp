#pragma once
#include <OJ.hpp>
#include <map>
#include <string>

class ETIGER : public OJ {
  private:
    std::string Token = "";
    std::map<int, std::pair<std::string, std::string>> DifficultyName;

  public:
    ETIGER();
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
    void ClockIn();
    void GetAnswerOrTips(std::string ProblemID);
};

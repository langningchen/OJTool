#pragma once
#include <string>

class OJ {
  public:
    virtual void Login(std::string Username, std::string Password) = 0;
    virtual void GetProblemDetail(std::string ProblemID) = 0;
    virtual void SubmitCode(std::string ProblemID) = 0;
};

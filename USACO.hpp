#pragma once
#include <OJ.hpp>
#include <string>

class USACO : public OJ {
  private:
    std::string Username;
    std::string Token;

  public:
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
};

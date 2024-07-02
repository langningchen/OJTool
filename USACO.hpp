#pragma once
#include "OJ.hpp"
#include <string>
using namespace std;

class USACO : public OJ {
  private:
    string Username;
    string Token;

  public:
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
};

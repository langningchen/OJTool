#pragma once
#include "OJ.hpp"
#include <string>
using namespace std;

class ATCODER : public OJ {
  public:
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
};

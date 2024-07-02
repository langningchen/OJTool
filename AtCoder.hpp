#pragma once
#include <OJ.hpp>
#include <string>

class ATCODER : public OJ {
  public:
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
};

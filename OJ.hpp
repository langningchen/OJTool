#ifndef OJ_HPP
#define OJ_HPP

#include <string>
using namespace std;

class OJ {
  public:
    virtual void Login(string Username, string Password) = 0;
    virtual void GetProblemDetail(string ProblemID) = 0;
    virtual void SubmitCode(string ProblemID) = 0;
};

#endif

#ifndef ATCODER_HPP
#define ATCODER_HPP

#include <string>
#include "OJ.hpp"
using namespace std;

class ATCODER : public OJ
{
public:
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
};

#endif

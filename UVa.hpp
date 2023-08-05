#ifndef UVA_HPP
#define UVA_HPP

#include <string>
#include "OJ.hpp"
using namespace std;

class UVA : public OJ
{
public:
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
};

#endif

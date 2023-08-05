#ifndef USACO_HPP
#define USACO_HPP

#include <string>
#include "OJ.hpp"
using namespace std;

class USACO : public OJ
{
private:
    string Username;
    string Token;

public:
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
};

#endif

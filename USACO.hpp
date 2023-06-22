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
    void GetQuestionDetail(string QuestionID);
    void SubmitCode(string QuestionID);
};

#endif

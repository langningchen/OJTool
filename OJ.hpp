#ifndef OJ_HPP
#define OJ_HPP

#include <string>
using namespace std;

class OJ
{
public:
    virtual void Login(string Username, string Password) = 0;
    virtual void GetQuestionDetail(string QuestionID) = 0;
    virtual void SubmitCode(string QuestionID) = 0;
};

#endif

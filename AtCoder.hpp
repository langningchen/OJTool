#ifndef ATCODER_HPP
#define ATCODER_HPP

#include <string>
#include "OJ.hpp"
using namespace std;

class ATCODER : public OJ
{
public:
    void Login(string Username, string Password);
    void GetQuestionDetail(string QuestionID);
    void SubmitCode(string QuestionID);
};

#endif

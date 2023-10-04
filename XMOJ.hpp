#pragma once

#include <string>
#include "OJ.hpp"
using namespace std;

class XMOJ : public OJ
{
private:
    string ResultName[17];
    string GetCSRF();
    string HTMLToText(string Data);
    void _GetProblemDetail(string ProblemID, string ProblemHandle);

public:
    XMOJ();
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
    void GetContestProblemsDetails(string ContestID);
};

#pragma once

#include <string>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "OJ.hpp"
using namespace std;

class CODEFORCES : public OJ
{
private:
    const string ftaa = "rv5q0yv00p85nhpyi7";
    const string bfaa = "f1b3f18c715565b589b7823cda7448ce";
    string GetCSRF();
    string OutputPre(TiXmlElement *Input);
    string Output(TiXmlElement *Input, bool InLatex = false);
    string ToNormalName(string Input);

public:
    void Login(string Username, string Password);
    void GetProblemDetail(string ProblemID);
    void SubmitCode(string ProblemID);
};

#pragma once
#include <OJ.hpp>
#include <string>
#include <tinyxml/tinyxml.h>

class CODEFORCES : public OJ {
  private:
    const std::string ftaa = "rv5q0yv00p85nhpyi7";
    const std::string bfaa = "f1b3f18c715565b589b7823cda7448ce";
    std::string GetCSRF();
    std::string OutputPre(TiXmlElement *Input);
    std::string Output(TiXmlElement *Input, bool InLatex = false);
    std::string ToNormalName(std::string Input);

  public:
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
};

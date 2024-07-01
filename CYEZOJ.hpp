#pragma once
#include <OJ.hpp>
#include <string>

class CYEZOJ : public OJ {
  private:
    std::string ResultName[17];
    std::string GetCSRF();
    std::string HTMLToText(std::string Data);
    void _GetProblemDetail(std::string ProblemID, std::string ProblemHandle);

  public:
    CYEZOJ();
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
    void GetContestProblemsDetails(std::string ContestID);
};

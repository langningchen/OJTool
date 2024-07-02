#pragma once
#include <OJ.hpp>
#include <map>
#include <string>

class LUOGU : public OJ {
  private:
    std::map<int, std::string> LanguageName, LanguageMarkdownName;
    std::map<int, std::pair<std::string, std::string>> DifficultyName, TagName, RecordName;
    std::map<std::string, std::string> TypeName, ColorList;
    std::string GetCSRF();

  public:
    LUOGU();
    void Login(std::string Username, std::string Password);
    void GetProblemDetail(std::string ProblemID);
    void SubmitCode(std::string ProblemID);
    void ClockIn();
    void GetAnswerOrTips(std::string ProblemID);
};

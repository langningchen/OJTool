#ifndef TOOL_HPP
#define TOOL_HPP
#include <string>
#include <iostream>
#include <regex>
#include <map>
#include "Curl.hpp"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "MD5.hpp"
#include "tidy/tidy.h"
#include "tidy/tidybuffio.h"
using namespace std;
extern string CurrentDir;
class TOOL
{
private:
    static void Speak(string Name);
    static string GetCPHFileName(string Path, string FileName);
    static string TidyHTMLDocument(string Input);
    class LUOGU
    {
    private:
        map<int, string> LanguageName, LanguageMarkdownName;
        map<int, pair<string, string>> DifficultyName, TagName, RecordName;
        map<string, string> TypeName, ColorList;
        string GetCSRF();

    public:
        LUOGU();
        void Login(string Username, string Password);
        void ClockIn();
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
        void GetAnswerOrTips(string QuestionID);
    };
    class ETIGER
    {
    private:
        string Token = "";
        map<int, pair<string, string>> DifficultyName;

    public:
        ETIGER();
        void Login(string Username, string Password);
        void ClockIn();
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
        void GetAnswerOrTips(string QuestionID);
    };
    class XMOJ
    {
    private:
        string ResultName[17];
        string GetCSRF();
        string HTMLToText(string Data);
        void _GetQuestionDetail(string QuestionID, string QuestionHandle);

    public:
        XMOJ();
        void Login(string Username, string Password);
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
        void GetContestQuestionsDetails(string ContestID);
    };
    class USACO
    {
    private:
        string Token;

    public:
        USACO();
        void Login(string Username, string Password);
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
    };
    class CODEFORCES
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
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
    };
    class UVA
    {
    public:
        void Login(string Username, string Password);
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
    };
    class ATCODER
    {
    public:
        void Login(string Username, string Password);
        void GetQuestionDetail(string QuestionID);
        void SubmitCode(string QuestionID);
    };

public:
    TOOL();
    TOOL(string FileName, string Operation);
    TOOL(string ServerName, string Username, string Password);
    ~TOOL();
};
#endif

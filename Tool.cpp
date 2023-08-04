#include "Tool.hpp"
#include "AtCoder.hpp"
#include "Codeforces.hpp"
#include "Etiger.hpp"
#include "Luogu.hpp"
#include "USACO.hpp"
#include "UVa.hpp"
#include "XMOJ.hpp"
void TOOL::Speak(string Name)
{
    system(("mocp -l \"" + GetUserHomeFolder() + "/OJTool/Audios/" + Name + ".mp3\"" +
            " > /dev/null 2>&1")
               .c_str());
}
string TOOL::GetCPHFileName(string Path, string FileName)
{
    // Create an object of the MD5 class to encode the file name
    MD5 MD5Encoder;
    // Return the file name in the CPH directory
    return "/home/langningc2009/CPH/." +
           FileName +
           ".cpp_" +
           // Encode the full path of the file
           MD5Encoder.encode(GetUserHomeFolder() + "/" + Path + "/" + FileName + ".cpp") +
           // Add the .prob extension to the file name
           ".prob";
}
void TOOL::Execute()
{
    // Choose the tool
    if (OJ == "Luogu")
    {
        LUOGU Luogu;
        Luogu.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            Luogu.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            Luogu.SubmitCode(QuestionID);
        else if (Operation == "GetAnswerOrTips")
            Luogu.GetAnswerOrTips(QuestionID);
        else if (Operation == "ClockIn")
            Luogu.ClockIn();
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else if (OJ == "Etiger")
    {
        ETIGER Etiger;
        Etiger.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            Etiger.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            Etiger.SubmitCode(QuestionID);
        else if (Operation == "GetAnswerOrTips")
            Etiger.GetAnswerOrTips(QuestionID);
        else if (Operation == "ClockIn")
            Etiger.ClockIn();
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else if (OJ == "XMOJ")
    {
        XMOJ _XMOJ;
        _XMOJ.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            _XMOJ.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            _XMOJ.SubmitCode(QuestionID);
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else if (OJ == "USACO")
    {
        USACO _USACO;
        _USACO.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            _USACO.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            _USACO.SubmitCode(QuestionID);
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else if (OJ == "UVa")
    {
        UVA UVa;
        UVa.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            UVa.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            UVa.SubmitCode(QuestionID);
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else if (OJ == "Codeforces")
    {
        CODEFORCES Codeforces;
        Codeforces.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            Codeforces.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            Codeforces.SubmitCode(QuestionID);
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else if (OJ == "AtCoder")
    {
        ATCODER AtCoder;
        AtCoder.Login(Username, Password);
        if (Operation == "GetQuestionDetail")
            AtCoder.GetQuestionDetail(QuestionID);
        else if (Operation == "SubmitCode")
            AtCoder.SubmitCode(QuestionID);
        else
            TRIGGER_ERROR("Arguments invalid");
    }
    else
        TRIGGER_ERROR("Arguments invalid");
}
string TOOL::TidyHTMLDocument(string Input)
{
    // Use Tidy to tidy the HTML document to XHTML
    TidyBuffer OutputBuffer = {0};
    TidyBuffer ErrorBuffer = {0};
    TidyDoc TidyDocument = tidyCreate();
    tidyOptSetBool(TidyDocument, TidyXhtmlOut, yes);
    tidySetErrorBuffer(TidyDocument, &ErrorBuffer);
    tidyParseString(TidyDocument, Input.c_str());
    tidyCleanAndRepair(TidyDocument);
    tidyRunDiagnostics(TidyDocument);
    tidyOptSetBool(TidyDocument, TidyForceOutput, yes);
    tidySaveBuffer(TidyDocument, &OutputBuffer);
    string Output = string(reinterpret_cast<const char *>(OutputBuffer.bp));
    tidyBufFree(&OutputBuffer);
    tidyBufFree(&ErrorBuffer);
    tidyRelease(TidyDocument);
    return Output;
}

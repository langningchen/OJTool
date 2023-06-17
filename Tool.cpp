#include "Tool.hpp"
extern string CurrentDir;
void TOOL::Speak(string Name)
{
    system(("mplayer \"" +
            CurrentDir + "Projects/OJTool/Audios/" + Name + ".mp3\"" +
            " > /dev/null 2>&1")
               .c_str());
}
string TOOL::GetCPHFileName(string Path, string FileName)
{
    // Create an object of the MD5 class to encode the file name
    MD5 MD5Encoder;
    // Return the file name in the CPH directory
    return "CPH/." +
           FileName +
           ".cpp_" +
           // Encode the full path of the file
           MD5Encoder.encode(CurrentDir +
                             Path +
                             "/" +
                             FileName +
                             ".cpp") +
           // Add the .prob extension to the file name
           ".prob";
}
TOOL::TOOL()
{
    string ContestID;
    cout << "Please input ContestID: ";
    cin >> ContestID;
    XMOJ _XMOJ;
    _XMOJ.Login(GetDataFromFileToString("Keys/XMOJUsername"), GetDataFromFileToString("Keys/XMOJPassword"));
    _XMOJ.GetContestQuestionsDetails(ContestID);
}
TOOL::TOOL(string FileName, string Operation)
{
    // Choose the tool
    if (FileName.find("Luogu") != string::npos)
    {
        LUOGU Luogu;
        Luogu.Login(GetDataFromFileToString("Keys/LuoguUsername"), GetDataFromFileToString("Keys/LuoguPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Luogu get question detail");
#endif
            Luogu.GetQuestionDetail(GetStringBetween(FileName, "Luogu/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Luogu submit code");
#endif
            Luogu.SubmitCode(GetStringBetween(FileName, "Luogu/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "GetAnswerOrTips")
        {
#ifdef TEST
            OutputSummary("##### Luogu get answer or tips");
#endif
            Luogu.GetAnswerOrTips(GetStringBetween(FileName, "Luogu/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("Etiger") != string::npos)
    {
        ETIGER Etiger;
        Etiger.Login(GetDataFromFileToString("Keys/EtigerUsername"), GetDataFromFileToString("Keys/EtigerPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Etiger get question detail");
#endif
            Etiger.GetQuestionDetail(GetStringBetween(FileName, "Etiger/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Etiger submit code");
#endif
            Etiger.SubmitCode(GetStringBetween(FileName, "Etiger/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "GetAnswerOrTips")
        {
#ifdef TEST
            OutputSummary("##### Etiger get answer or tips");
#endif
            Etiger.GetAnswerOrTips(GetStringBetween(FileName, "Etiger/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("XMOJ") != string::npos)
    {
        XMOJ _XMOJ;
        _XMOJ.Login(GetDataFromFileToString("Keys/XMOJUsername"), GetDataFromFileToString("Keys/XMOJPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### XMOJ get question detail");
#endif
            _XMOJ.GetQuestionDetail(GetStringBetween(FileName, "XMOJ/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### XMOJ submit code");
#endif
            _XMOJ.SubmitCode(GetStringBetween(FileName, "XMOJ/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("USACO") != string::npos)
    {
        USACO _USACO;
        _USACO.Login(GetDataFromFileToString("Keys/USACOUsername"), GetDataFromFileToString("Keys/USACOPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### USACO get question detail");
#endif
            _USACO.GetQuestionDetail(GetStringBetween(FileName, "USACO/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### USACO submit code");
#endif
            _USACO.SubmitCode(GetStringBetween(FileName, "USACO/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("UVa") != string::npos)
    {
        UVA UVa;
        UVa.Login(GetDataFromFileToString("Keys/UVaUsername"), GetDataFromFileToString("Keys/UVaPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### UVa get question detail");
#endif
            UVa.GetQuestionDetail(GetStringBetween(FileName, "UVa/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### UVa submit code");
#endif
            UVa.SubmitCode(GetStringBetween(FileName, "UVa/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("Codeforces") != string::npos)
    {
        CODEFORCES Codeforces;
        Codeforces.Login(GetDataFromFileToString("Keys/CodeforcesUsername"), GetDataFromFileToString("Keys/CodeforcesPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Codeforces get question detail");
#endif
            Codeforces.GetQuestionDetail(GetStringBetween(FileName, "Codeforces/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Codeforces submit code");
#endif
            Codeforces.SubmitCode(GetStringBetween(GetStringBetween(FileName, "Codeforces/", ".cpp"), "", "/"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else if (FileName.find("AtCoder") != string::npos)
    {
        ATCODER AtCoder;
        AtCoder.Login(GetDataFromFileToString("Keys/AtCoderUsername"), GetDataFromFileToString("Keys/AtCoderPassword"));
        if (Operation == "GetQuestionDetail")
        {
#ifdef TEST
            OutputSummary("##### Codeforces get question detail");
#endif
            AtCoder.GetQuestionDetail(GetStringBetween(FileName, "AtCoder/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else if (Operation == "SubmitCode")
        {
#ifdef TEST
            OutputSummary("##### Codeforces submit code");
#endif
            AtCoder.SubmitCode(GetStringBetween(FileName, "AtCoder/", ".cpp"));
#ifdef TEST
            OutputSummary("Success");
#endif
        }
        else
        {
            TRIGGER_ERROR("Arguments invalid");
        }
    }
    else
    {
        TRIGGER_ERROR("Arguments invalid");
    }
}
TOOL::TOOL(string ServerName, string Username, string Password)
{
    // Fix leading and trailing spaces and line breaks in the username and password
    Username = FixString(Username);
    Password = FixString(Password);
    if (ServerName == "Luogu")
    {
        LUOGU Luogu;
        Luogu.Login(Username, Password);
        Luogu.ClockIn();
    }
    else if (ServerName == "Etiger")
    {
        ETIGER Etiger;
        Etiger.Login(Username, Password);
        Etiger.ClockIn();
    }
    else
    {
        TRIGGER_ERROR("Arguments invalid");
    }
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
TOOL::~TOOL()
{
}

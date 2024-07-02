#include "Tool.hpp"
#include "AtCoder.hpp"
#include "Codeforces.hpp"
#include "Etiger.hpp"
#include "Luogu.hpp"
#include "USACO.hpp"
#include "UVa.hpp"
#include "XMOJ.hpp"
string TOOL::GetCPHFileName(string Path, string FileName) {
    // Create an object of the MD5 class to encode the file name
    MD5 MD5Encoder;
    // Return the file name in the CPH directory
    return "/CPH/." +
           FileName +
           ".cpp_" +
           // Encode the full path of the file
           MD5Encoder.encode(GetUserHomeFolder() + PathSeparator + Path + PathSeparator + FileName + ".cpp") +
           // Add the .prob extension to the file name
           ".prob";
}
void TOOL::Execute() {
    // Choose the tool
    if (OJ == "Luogu") {
        LUOGU Luogu;
        Luogu.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            Luogu.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            Luogu.SubmitCode(ProblemID);
        else if (Operation == "GetAnswerOrTips")
            Luogu.GetAnswerOrTips(ProblemID);
        else if (Operation == "ClockIn")
            Luogu.ClockIn();
        else
            TRIGGER_ERROR("Arguments invalid");
    } else if (OJ == "Etiger") {
        ETIGER Etiger;
        Etiger.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            Etiger.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            Etiger.SubmitCode(ProblemID);
        else if (Operation == "GetAnswerOrTips")
            Etiger.GetAnswerOrTips(ProblemID);
        else if (Operation == "ClockIn")
            Etiger.ClockIn();
        else
            TRIGGER_ERROR("Arguments invalid");
    } else if (OJ == "XMOJ") {
        XMOJ _XMOJ;
        _XMOJ.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            _XMOJ.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            _XMOJ.SubmitCode(ProblemID);
        else
            TRIGGER_ERROR("Arguments invalid");
    } else if (OJ == "USACO") {
        USACO _USACO;
        _USACO.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            _USACO.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            _USACO.SubmitCode(ProblemID);
        else
            TRIGGER_ERROR("Arguments invalid");
    } else if (OJ == "UVa") {
        UVA UVa;
        UVa.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            UVa.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            UVa.SubmitCode(ProblemID);
        else
            TRIGGER_ERROR("Arguments invalid");
    } else if (OJ == "Codeforces") {
        CODEFORCES Codeforces;
        Codeforces.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            Codeforces.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            Codeforces.SubmitCode(ProblemID);
        else
            TRIGGER_ERROR("Arguments invalid");
    } else if (OJ == "AtCoder") {
        ATCODER AtCoder;
        AtCoder.Login(Username, Password);
        if (Operation == "GetProblemDetail")
            AtCoder.GetProblemDetail(ProblemID);
        else if (Operation == "SubmitCode")
            AtCoder.SubmitCode(ProblemID);
        else
            TRIGGER_ERROR("Arguments invalid");
    } else
        TRIGGER_ERROR("Arguments invalid");
}
string TOOL::TidyHTMLDocument(string Input) {
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

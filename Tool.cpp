/**********************************************************************
OJTool: Get problem and submit code for OJ just from your CLI!
Copyright (C) 2024  langningchen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
**********************************************************************/

#include <AtCoder.hpp>
#include <Codeforces.hpp>
#include <Etiger.hpp>
#include <Luogu.hpp>
#include <Tool.hpp>
#include <USACO.hpp>
#include <UVa.hpp>
#include <XMOJ.hpp>
std::string TOOL::GetSourceCodePath(std::string Filename) {
    return GetRealpath(GetCurrentDir() + "/../" + Filename + ".cpp");
}
std::string TOOL::GetCPHFileName(std::string Filename) {
    // Create an object of the MD5 class to encode the file name
    MD5 MD5Encoder;
    // Return the file name in the CPH directory
    return "/OJTool/." +
           Filename +
           ".cpp_" +
           // Encode the full path of the file
           MD5Encoder.encode(GetSourceCodePath(Filename)) +
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
std::string TOOL::TidyHTMLDocument(std::string Input) {
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
    std::string Output = std::string(reinterpret_cast<const char *>(OutputBuffer.bp));
    tidyBufFree(&OutputBuffer);
    tidyBufFree(&ErrorBuffer);
    tidyRelease(TidyDocument);
    return Output;
}

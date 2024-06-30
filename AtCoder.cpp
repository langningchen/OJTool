#include "AtCoder.hpp"
#include "Curl.hpp"
#include "Tool.hpp"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <iostream>
using namespace std;

void ATCODER::Login(string Username, string Password) {
    cout << "Checking logged... " << flush;
    int HTTPResponseCode = 0;
    GetDataToFile("https://atcoder.jp/settings",
                  "",
                  "",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode != 302) {
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;

    cout << "Getting CSRF token... " << flush;
    GetDataToFile("https://atcoder.jp/login");
    string CSRFToken = GetStringBetween(GetDataFromFileToString(),
                                        "var csrfToken = \"",
                                        "\"");
    if (CSRFToken == "")
        TRIGGER_ERROR("Get CSRF token failed");
    cout << "Succeed" << endl;

    cout << "Logging in... " << flush;
    GetDataToFile("https://atcoder.jp/login",
                  "",
                  "",
                  true,
                  "username=" + URLEncode(Username) + "&password=" + URLEncode(Password) + "&csrf_token=" + URLEncode(CSRFToken),
                  NULL,
                  NULL,
                  FORM);
    if (FindLocation().find("login") != string::npos)
        TRIGGER_ERROR("Login failed");
    cout << "Succeed" << endl;
}
void ATCODER::GetProblemDetail(string ProblemID) {
    if (!IfFileExist("/tmp/AtCoder-" + ProblemID + ".md")) {
        cout << "Getting problem detail... " << flush;
        string ContestName = SpiltString(ProblemID, "_")[0];
        GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + ProblemID);
        cout << "Succeed" << endl;

        cout << "Parsing problem detail... " << flush;
        TiXmlDocument ProblemXmlDocument;
        ProblemXmlDocument.Parse(TOOL::TidyHTMLDocument(GetDataFromFileToString()).c_str());
        if (ProblemXmlDocument.Error())
            TRIGGER_ERROR("Parse problem detail error: "s + ProblemXmlDocument.ErrorDesc());
        cout << "Succeed" << endl;

        TiXmlHandle ProblemXmlHandle = TiXmlHandle(&ProblemXmlDocument)
                                           .FirstChild("html")
                                           .FirstChild("body")
                                           .Child("div", 2)
                                           .FirstChild("div")
                                           .FirstChild("div")
                                           .Child("div", 1);
        string ProblemDetail = "# " + ContestName + " " + ProblemXmlHandle.FirstChild("span").FirstChild().ToText()->Value() + "\n" +
                               "\n";
        string TimeAndMemoryLimit = FixString(ProblemXmlHandle.FirstChild("p").FirstChild().ToText()->Value()) + "__END__";
        ProblemDetail += "## Other information\n"s +
                         "\n" +
                         "|Item|Value|\n" +
                         "|:---:|:---:|\n" +
                         "|Time limit|$" + GetStringBetween(TimeAndMemoryLimit, "Time Limit: ", " / ") + "$|\n" +
                         "|Memory limit|$" + GetStringBetween(TimeAndMemoryLimit, "Memory Limit: ", "__END__") + "$|\n";
        SetDataFromStringToFile("/tmp/AtCoder-" + ProblemID + ".md", ProblemDetail);
    }

    // Open the problem detail file
    if (system(string("code-insiders /tmp/AtCoder-" + ProblemID + ".md").c_str()))
        cout << "Open file \"/tmp/AtCoder-" << ProblemID << ".md\" failed, please open it manually" << endl;
}
void ATCODER::SubmitCode(string ProblemID) {
    // Get the code
    string Code = GetDataFromFileToString("AtCoder/" + ProblemID + ".cpp");
    string ContestName = SpiltString(ProblemID, "_")[0];

    // Get the token
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + ProblemID);
    string CSRFToken = GetStringBetween(GetDataFromFileToString(),
                                        "var csrfToken = \"",
                                        "\"");
    cout << "Succeed" << endl;

    cout << "Submitting... " << flush;
    int HTTPResponseCode = 0;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submit",
                  "",
                  "",
                  true,
                  "data.TaskScreenName=" + ProblemID + "&data.LanguageId=4003&sourceCode=" + URLEncode(Code) + "&csrf_token=" + URLEncode(CSRFToken),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode != 302) {
        TRIGGER_ERROR_WITH_CODE("Submit failed",
                                HTTPResponseCode);
    }
    cout << "Succeed" << endl;

    cout << "Getting submission ID... " << flush;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submissions/me");
    string SubmissionID = GetStringBetween(GetDataFromFileToString(),
                                           "data-id=\"",
                                           "\"");
    if (SubmissionID == "")
        TRIGGER_ERROR("Get submission ID failed");
    cout << "Succeed" << endl;

    cout << "Judging... " << flush;
    while (1) {
        GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID + "/status/json");
        json JSONData = json::parse(GetDataFromFileToString());
        cout << "\rJudging... " << GetStringBetween(JSONData["Html"].as_string(), ">", "<") << flush;
        if (JSONData["Interval"].is_null()) {
            cout << "\rJudging... Succeed"
                 << " " << JSONData["Status"].as_string() << endl;
            system(("www-browser https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID).c_str());
            break;
        }
        usleep(500000);
    }
}

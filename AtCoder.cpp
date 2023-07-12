#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "Curl.hpp"
#include "Tool.hpp"
#include "AtCoder.hpp"
using namespace std;

void ATCODER::Login(string Username, string Password)
{
    cout << "Checking logged... " << flush;
    int HTTPResponseCode = 0;
    GetDataToFile("https://atcoder.jp/settings",
                  "",
                  "",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode != 302)
    {
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
void ATCODER::GetQuestionDetail(string QuestionID)
{
    if (!IfFileExist("/tmp/AtCoder-" + QuestionID + ".md"))
    {
        cout << "Getting question detail... " << flush;
        string ContestName = SpiltString(QuestionID, "_")[0];
        GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + QuestionID);
        cout << "Succeed" << endl;

        cout << "Parsing question detail... " << flush;
        TiXmlDocument QuestionXmlDocument;
        QuestionXmlDocument.Parse(TOOL::TidyHTMLDocument(GetDataFromFileToString()).c_str());
        if (QuestionXmlDocument.Error())
            TRIGGER_ERROR("Parse question detail error: "s + QuestionXmlDocument.ErrorDesc());
        cout << "Succeed" << endl;

        TiXmlHandle QuestionXmlHandle = TiXmlHandle(&QuestionXmlDocument)
                                            .FirstChild("html")
                                            .FirstChild("body")
                                            .Child("div", 2)
                                            .FirstChild("div")
                                            .FirstChild("div")
                                            .Child("div", 1);
        string QuestionDetail = "# " + ContestName + " " + QuestionXmlHandle.FirstChild("span").FirstChild().ToText()->Value() + "\n" +
                                "\n";
        string TimeAndMemoryLimit = FixString(QuestionXmlHandle.FirstChild("p").FirstChild().ToText()->Value()) + "__END__";
        QuestionDetail += "## Other information\n"s +
                          "\n" +
                          "|Item|Value|\n" +
                          "|:---:|:---:|\n" +
                          "|Time limit|$" + GetStringBetween(TimeAndMemoryLimit, "Time Limit: ", " / ") + "$|\n" +
                          "|Memory limit|$" + GetStringBetween(TimeAndMemoryLimit, "Memory Limit: ", "__END__") + "$|\n";
        SetDataFromStringToFile("/tmp/AtCoder-" + QuestionID + ".md", QuestionDetail);
    }

    // Open the question detail file
    if (system(string("code-insiders /tmp/AtCoder-" + QuestionID + ".md").c_str()))
        cout << "Open file \"/tmp/AtCoder-" << QuestionID << ".md\" failed, please open it manually" << endl;
    TOOL::Speak("Get question detail succeed");
}
void ATCODER::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString("AtCoder/" + QuestionID + ".cpp");
    string ContestName = SpiltString(QuestionID, "_")[0];

    // Get the token
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + QuestionID);
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
                  "data.TaskScreenName=" + QuestionID + "&data.LanguageId=4003&sourceCode=" + URLEncode(Code) + "&csrf_token=" + URLEncode(CSRFToken),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode != 302)
    {
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
    while (1)
    {
        GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID + "/status/json");
        json JSONData = json::parse(GetDataFromFileToString());
        cout << "\rJudging... " << GetStringBetween(JSONData["Html"].as_string(), ">", "<") << flush;
        if (JSONData["Status"].as_string() == "AC")
        {
            cout << "\rJudging... Succeed" << endl
                 << "Congratulations! You have passed this question!" << endl;
            TOOL::Speak("Congratulations! You have passed this question!");
            break;
        }
        else if (JSONData["Interval"].is_null())
        {
            cout << "\rJudging... Succeed"
                 << " " << JSONData["Status"].as_string() << endl;
            system(("www-browser https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID).c_str());
            TOOL::Speak("You did not pass this question");
            break;
        }
        usleep(500000);
    }
}

#include "Tool.hpp"
void TOOL::ATCODER::Login(string Username, string Password)
{
    cout << "Checking logged... " << flush;
    int HTTPResponseCode = 0;
    GetDataToFile("https://atcoder.jp/settings",
                  "Header.tmp",
                  "Body.tmp",
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
    {
        TRIGGER_ERROR("Get CSRF token failed");
    }
    cout << "Succeed" << endl;

    cout << "Logging in... " << flush;
    GetDataToFile("https://atcoder.jp/login",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  "username=" + URLEncode(Username) + "&password=" + URLEncode(Password) + "&csrf_token=" + URLEncode(CSRFToken),
                  NULL,
                  NULL,
                  FORM);
    if (FindLocation().find("login") != string::npos)
    {
        TRIGGER_ERROR("Login failed");
    }
    cout << "Succeed" << endl;
}
void TOOL::ATCODER::GetQuestionDetail(string QuestionID)
{
    cout << "Getting question detail... " << flush;
    string ContestName = SpiltString(QuestionID, "_")[0];
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + QuestionID);
    cout << "Succeed" << endl;

    cout << "Parsing question detail... " << flush;
    TiXmlDocument QuestionXmlDocument;
    QuestionXmlDocument.Parse(TidyHTMLDocument(GetDataFromFileToString()).c_str());
    if (QuestionXmlDocument.Error())
    {
        TRIGGER_ERROR("Parse question detail error: "s + QuestionXmlDocument.ErrorDesc());
    }
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
    SetDataFromStringToFile("AtCoder/" + QuestionID + ".md", QuestionDetail);

#ifndef TEST
    // Open the question detail file
    if (system(string("code " + CurrentDir + "AtCoder/" + QuestionID + ".md").c_str()))
        cout << "Open file \"AtCoder/" << QuestionID << ".md\" failed, please open it manually" << endl;
    Speak("Get question detail succeed");
#endif
}
void TOOL::ATCODER::SubmitCode(string QuestionID)
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
                  "Header.tmp",
                  "Body.tmp",
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
    string SubmissionID = GetStringBetween(GetDataFromFileToString("Body.tmp"),
                                           "data-id=\"",
                                           "\"");
    if (SubmissionID == "")
    {
        TRIGGER_ERROR("Get submission ID failed");
    }
    cout << "Succeed" << endl;

    cout << "Judging... " << flush;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID);
    std::string HTMLData = GetDataFromFileToString();
    HTMLData = StringReplaceAll(HTMLData, "\r", " ");
    HTMLData = StringReplaceAll(HTMLData, "\n", " ");
    HTMLData = StringReplaceAll(HTMLData, "\t", " ");
    HTMLData = StringReplaceAll(HTMLData, "< ", "<");
    HTMLData = StringReplaceAll(HTMLData, " <", "<");
    HTMLData = StringReplaceAll(HTMLData, " >", ">");
    HTMLData = StringReplaceAll(HTMLData, "> ", ">");
    HTMLData = StringReplaceAll(HTMLData, "= ", "=");
    HTMLData = StringReplaceAll(HTMLData, " =", "=");
    HTMLData = StringReplaceAll(HTMLData, "  ", " ");
    SetDataFromStringToFile("Temp.txt", HTMLData);
}

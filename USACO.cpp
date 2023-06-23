#include "Tool.hpp"
#include "USACO.hpp"
void USACO::Login(string Username, string Password)
{
    // Login to USACO
    cout << "Logging in... " << flush;
    GetDataToFile("https://train.usaco.org/usacogate",
                  "",
                  "",
                  true,
                  "NAME=" + URLEncode(Username) +
                      "&PASSWORD=" + URLEncode(Password) +
                      "&SUBMIT=ENTER",
                  NULL,
                  NULL,
                  "application/x-www-form-urlencoded");
    Token = GetStringBetween(GetDataFromFileToString(), "a=", "\"");
    if (Token == "")
    TRIGGER_ERROR("Login failed");
    cout << "Succeed" << endl;
    this->Username = Username;
}
void USACO::GetQuestionDetail(string QuestionID)
{
    // Get the question detail
    cout << "Getting question detail... " << flush;
    GetDataToFile("https://train.usaco.org/usacoprob2?a=XKG7SarkKso&S=" + QuestionID);
    SetDataFromStringToFile(
        "/tmp/USACO-" + QuestionID + ".md",
        GetStringBetween(
            GetDataFromFileToString(),
            "<img src=\"/usaco/cow1.jpg\" width=\"742\" height=\"118\">",
            "<div style='width:6.25in;background-color:#FFFFCC;border:1px solid black;'>"));
    cout << "Succeed" << endl;

    // Open the question detail file
    if (system(string("code-insiders /tmp/USACO-" + QuestionID + ".md").c_str()))
        cout << "Open file \"/tmp/USACO-" << QuestionID << ".md\" failed, please open it manually" << endl;
    TOOL::Speak("Get question detail succeed");
}
void USACO::SubmitCode(string QuestionID)
{
    string Code = GetDataFromFileToString("USACO/" + QuestionID + ".cpp");
    Code = "/*\n"s +
           "ID: " + Username + "\n" +
           "TASK: " + QuestionID + "\n" +
           "LANG: C++14\n" +
           "*/\n" +
           Code;
    Code = FixString(Code);
    Code += "\n";
    string MultiPartData = "--" + MULTIPART_BOUNDARY + "\n" +
                           "Content-Disposition: form-data; name=\"filename\"; filename=\"" + QuestionID + ".cpp\"\n" +
                           "Content-Type: application/octet-stream\n" +
                           "\n" +
                           Code + "\n" +
                           "--" + MULTIPART_BOUNDARY + "\n" +
                           "Content-Disposition: form-data; name=\"a\"\n" +
                           "\n" +
                           Token + "\n" +
                           "--" + MULTIPART_BOUNDARY + "--\n";
    SetDataFromStringToFile("MultiPartData.tmp", MultiPartData);

    // Submit code
    cout << "Submitting code... " << flush;
    GetDataToFile("https://train.usaco.org/upload3",
                  "",
                  "",
                  true,
                  MultiPartData,
                  NULL,
                  NULL,
                  MULTIPART);
    cout << "Succeed" << endl;

    SetDataFromStringToFile("/tmp/" + QuestionID + ".log",
                            EraseHTMLElement(
                                GetStringBetween(
                                    GetDataFromFileToString(),
                                    "<div style=background-color:white;padding:5px;>",
                                    "</div>")));
    system(("code-insiders /tmp/" + QuestionID + ".log").c_str());
}

#include "Tool.hpp"
void TOOL::UVA::Login(string Username, string Password)
{
    // Check if already logged in
    cout << "Checking login... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler");
    if (GetDataFromFileToString().find("You need to login.") == string::npos)
    {
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;

    // Get the login page data
    GetDataToFile("https://onlinejudge.org/index.php");
    string LoginPageHTML = GetDataFromFileToString();
    int HTTPResponseCode = 0;
    string cbsecuritym3 = GetStringBetween(LoginPageHTML,
                                           "<input type=\"hidden\" name=\"cbsecuritym3\" value=\"",
                                           "\" />");

    // Login
    cout << "Logging in... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler&task=login",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string("username=" + URLEncode(Username) +
                         "&passwd=" + URLEncode(Password) +
                         "&op2=login" +
                         "&lang=english" +
                         "&force_session=1" +
                         "&return=" +
                         URLEncode(
                             GetStringBetween(LoginPageHTML.c_str(),
                                              "<input type=\"hidden\" name=\"return\" value=\"",
                                              "\" />")) +
                         "&message=0" +
                         "&loginfrom=loginmodule" +
                         "&cbsecuritym3=" + cbsecuritym3 +
                         "&" +
                         GetStringBetween(LoginPageHTML.c_str(),
                                          cbsecuritym3 + "\" />\n<input type=\"hidden\" name=\"",
                                          "\" value=\"1\" />") +
                         "=1" +
                         "&remember=yes" +
                         "&Submit=Login"),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
    {
        TRIGGER_ERROR("Login failed");
    }
    cout << "Succeed" << endl;
}
void TOOL::UVA::GetQuestionDetail(string QuestionID)
{
    // Get the question detail
    string FixedQuestionID = QuestionID;
    while (FixedQuestionID[0] == '0')
        FixedQuestionID.erase(0, 1);

    // Save the pdf file
    cout << "Getting question detail... " << flush;
    GetDataToFile("https://onlinejudge.org/external/" +
                      FixedQuestionID.substr(0, FixedQuestionID.size() - 2) +
                      "/p" + FixedQuestionID + ".pdf",
                  "Header.tmp",
                  "UVa/" + QuestionID + ".pdf",
                  false,
                  "",
                  NULL,
                  NULL,
                  "application/json",
                  "",
                  true);
    cout << "Succeed" << endl;

#ifndef TEST
    // Open the pdf file
    if (system(string("code " + CurrentDir + "UVa/" + QuestionID + ".pdf").c_str()))
        cout << "Open file \"" + CurrentDir + "UVa/" << QuestionID << ".md\" failed, please open it manually" << endl;
    Speak("Get question detail succeed");
#endif
}
void TOOL::UVA::SubmitCode(string QuestionID)
{
    // Get the submit page data
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=submit_problem");
    cout << "Succeed" << endl;
    string FixedQuestionID = QuestionID;
    while (FixedQuestionID[0] == '0')
        FixedQuestionID.erase(0, 1);

    // Get the code
    string Code = GetDataFromFileToString("UVa/" + QuestionID + ".cpp");

    // Create the header list
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
    HeaderList = curl_slist_append(HeaderList, "Accept-Encoding: gzip, deflate, br");
    HeaderList = curl_slist_append(HeaderList, "Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://onlinejudge.org");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Dest: document");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Mode: navigate");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-Site: same-origin");
    HeaderList = curl_slist_append(HeaderList, "Sec-Fetch-User: ?1");
    HeaderList = curl_slist_append(HeaderList, "Upgrade-Insecure-Requests: 1");
    HeaderList = curl_slist_append(HeaderList, "Connection: keep-alive");
    HeaderList = curl_slist_append(HeaderList, "Host: onlinejudge.org");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=submit_problem");
    int HTTPResponseCode = 0;

    // Create the multipart data
    string SubmitPostBody = "--" + MULTIPART_BOUNDARY + "\n" +
                            "Content-Disposition: form-data; name=\"problemid\"\n" +
                            "\n" +
                            "\n" +
                            "--" + MULTIPART_BOUNDARY + "\n" +
                            "Content-Disposition: form-data; name=\"category\"\n" +
                            "\n" +
                            "\n" +
                            "--" + MULTIPART_BOUNDARY + "\n" +
                            "Content-Disposition: form-data; name=\"localid\"\n" +
                            "\n" +
                            FixedQuestionID + "\n" +
                            "--" + MULTIPART_BOUNDARY + "\n" +
                            "Content-Disposition: form-data; name=\"language\"\n" +
                            "\n" +
                            "5\n" +
                            "--" + MULTIPART_BOUNDARY + "\n" +
                            "Content-Disposition: form-data; name=\"code\"\n" +
                            "\n" +
                            Code + "\n" +
                            "\n" +
                            "--" + MULTIPART_BOUNDARY + "\nContent-Disposition: form-data; name=\"codeupl\"; filename=\"\"\n" +
                            "Content-Type: application/octet-stream\n" +
                            "\n" +
                            "\n" +
                            "--" + MULTIPART_BOUNDARY + "--\n";

    // Submit the code
    cout << "Submitting... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=save_submission",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  SubmitPostBody,
                  HeaderList,
                  &HTTPResponseCode,
                  MULTIPART);
    if (HTTPResponseCode == 200)
    {
        TRIGGER_ERROR("Submit failed");
    }

    // Get the submission id
    string SubmissionID = FindLocation();
    SubmissionID = SubmissionID.substr(SubmissionID.find_last_of('+') + 1);
    if (atoi(SubmissionID.c_str()) == 0)
    {
        TRIGGER_ERROR("Get submission id failed");
    }
    cout << "Succeed" << endl;

    // Get the submission result
    cout << "Judging... " << flush;
    while (1)
    {
        // Get the submission list
        GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9");
        string Data = GetDataFromFileToString();
        Data = StringReplaceAll(Data, "\t", "");
        Data = StringReplaceAll(Data, "\r", "");
        Data = StringReplaceAll(Data, "\n", "");
        Data = StringReplaceAll(Data, "< ", "<");
        Data = StringReplaceAll(Data, " <", "<");
        Data = StringReplaceAll(Data, "> ", ">");
        Data = StringReplaceAll(Data, " >", ">");
        SetDataFromStringToFile("Data.tmp", Data);

        // Find the submission
        smatch Match;
        if (regex_search(Data.cbegin(), Data.cend(), Match, regex("<tr class=\"sectiontableentry[0-9]\"><td>" + SubmissionID + "</td><td align=\"right\"><a href=\"index\\.php\\?option=com_onlinejudge&amp;Itemid=8&amp;page=show_problem&amp;problem=[0-9]*\">[0-9]*</a></td><td><a href=\"index\\.php\\?option=com_onlinejudge&amp;Itemid=8&amp;page=show_problem&amp;problem=[0-9]*\">[^<]*</a></td><td>([^<]*)</td><td>C\\+\\+11</td><td>([0-9\\.]*)</td><!--<td></td>--><td>[^<]*</td></tr>")))
        {
            // Get the result
            string Verdict = Match[1];
            if (Verdict == "In judge queue")
                usleep(500000);
            else
            {
                cout << "Succeed" << endl
                     << "Verdict: " << Verdict << endl
                     << "Run Time: " << Match[2] << "s" << endl;
                break;
            }
        }
        else
        {
            TRIGGER_ERROR("Can not find the judge result with submission id " + SubmissionID);
        }
    }
}

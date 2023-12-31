#include "Tool.hpp"
#include "UVa.hpp"
void UVA::Login(string Username, string Password)
{
    // Check if already logged in
    cout << "Checking login... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler");
    if (GetDataFromFileToString().find("You need to login.") == string::npos)
    {
        TOOL::Speak("Already logged in");
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
                  "",
                  "",
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
        TRIGGER_ERROR("Login failed");
    TOOL::Speak("Login succeeds");
    cout << "Succeed" << endl;
}
void UVA::GetProblemDetail(string ProblemID)
{
    if (!IfFileExist(TempFolder + "UVa-" + ProblemID + ".pdf"))
    {
        // Get the problem detail
        string FixedProblemID = ProblemID;
        while (FixedProblemID[0] == '0')
            FixedProblemID.erase(0, 1);

        // Save the pdf file
        cout << "Getting problem detail... " << flush;
        GetDataToFile("https://onlinejudge.org/external/" +
                          FixedProblemID.substr(0, FixedProblemID.size() - 2) +
                          "/p" + FixedProblemID + ".pdf",
                      "",
                      TempFolder + "UVa-" + ProblemID + ".pdf",
                      false,
                      "",
                      NULL,
                      NULL,
                      "application/json",
                      "",
                      true);
        cout << "Succeed" << endl;
    }

    // Open the pdf file
    if (system(string("code-insiders /tmp/UVa-" + ProblemID + ".pdf").c_str()))
        cout << "Open file \"/tmp/UVa-" << ProblemID << ".md\" failed, please open it manually" << endl;
    TOOL::Speak("Get problem detail succeed");
}
void UVA::SubmitCode(string ProblemID)
{
    // Get the submit page data
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=submit_problem");
    cout << "Succeed" << endl;
    string FixedProblemID = ProblemID;
    while (FixedProblemID[0] == '0')
        FixedProblemID.erase(0, 1);

    // Get the code
    string Code = GetDataFromFileToString("UVa/" + ProblemID + ".cpp");

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
                            FixedProblemID + "\n" +
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
                  "",
                  "",
                  true,
                  SubmitPostBody,
                  HeaderList,
                  &HTTPResponseCode,
                  MULTIPART);
    if (HTTPResponseCode == 200)
        TRIGGER_ERROR("Submit failed");

    // Get the submission ID
    string SubmissionID = FindLocation();
    SubmissionID = SubmissionID.substr(SubmissionID.find_last_of('+') + 1);
    if (atoi(SubmissionID.c_str()) == 0)
        TRIGGER_ERROR("Get submission ID failed");
    cout << "Succeed" << endl;
    TOOL::Speak("Submit succeed");

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
        SetDataFromStringToFile(TempFolder + "Data.tmp", Data);

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
            TRIGGER_ERROR("Can not find the judge result with submission ID " + SubmissionID);
    }
}

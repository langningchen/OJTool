#include <Tool.hpp>
#include <UVa.hpp>
void UVA::Login(std::string Username, std::string Password) {
    // Check if already logged in
    std::cout << "Checking login... " << std::flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler");
    if (GetDataFromFileToString().find("You need to login.") == std::string::npos) {
        std::cout << "Already logged in" << std::endl;
        return;
    }
    std::cout << "Not logged in" << std::endl;

    // Get the login page data
    GetDataToFile("https://onlinejudge.org/index.php");
    std::string LoginPageHTML = GetDataFromFileToString();
    int HTTPResponseCode = 0;
    std::string cbsecuritym3 = GetStringBetween(LoginPageHTML,
                                                "<input type=\"hidden\" name=\"cbsecuritym3\" value=\"",
                                                "\" />");

    // Login
    std::cout << "Logging in... " << std::flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_comprofiler&task=login",
                  "",
                  "",
                  true,
                  std::string("username=" + URLEncode(Username) +
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
    std::cout << "Succeed" << std::endl;
}
void UVA::GetProblemDetail(std::string ProblemID) {
    if (!IfFileExist("/tmp/UVa-" + ProblemID + ".pdf")) {
        // Get the problem detail
        std::string FixedProblemID = ProblemID;
        while (FixedProblemID[0] == '0')
            FixedProblemID.erase(0, 1);

        // Save the pdf file
        std::cout << "Getting problem detail... " << std::flush;
        GetDataToFile("https://onlinejudge.org/external/" +
                          FixedProblemID.substr(0, FixedProblemID.size() - 2) +
                          "/p" + FixedProblemID + ".pdf",
                      "",
                      "/tmp/UVa-" + ProblemID + ".pdf",
                      false,
                      "",
                      NULL,
                      NULL,
                      "application/json",
                      "",
                      true);
        std::cout << "Succeed" << std::endl;
    }

    // Open the pdf file
    if (system(std::string("code-insiders /tmp/UVa-" + ProblemID + ".pdf").c_str()))
        std::cout << "Open file \"/tmp/UVa-" << ProblemID << ".md\" failed, please open it manually" << std::endl;
}
void UVA::SubmitCode(std::string ProblemID) {
    // Get the submit page data
    std::cout << "Getting submit page data... " << std::flush;
    GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=submit_problem");
    std::cout << "Succeed" << std::endl;
    std::string FixedProblemID = ProblemID;
    while (FixedProblemID[0] == '0')
        FixedProblemID.erase(0, 1);

    // Get the code
    std::string Code = GetDataFromFileToString("UVa/" + ProblemID + ".cpp");

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
    std::string SubmitPostBody = "--" + MULTIPART_BOUNDARY + "\n" +
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
    std::cout << "Submitting... " << std::flush;
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
    std::string SubmissionID = FindLocation();
    SubmissionID = SubmissionID.substr(SubmissionID.find_last_of('+') + 1);
    if (atoi(SubmissionID.c_str()) == 0)
        TRIGGER_ERROR("Get submission ID failed");
    std::cout << "Succeed" << std::endl;

    // Get the submission result
    std::cout << "Judging... " << std::flush;
    while (1) {
        // Get the submission list
        GetDataToFile("https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9");
        std::string Data = GetDataFromFileToString();
        Data = StringReplaceAll(Data, "\t", "");
        Data = StringReplaceAll(Data, "\r", "");
        Data = StringReplaceAll(Data, "\n", "");
        Data = StringReplaceAll(Data, "< ", "<");
        Data = StringReplaceAll(Data, " <", "<");
        Data = StringReplaceAll(Data, "> ", ">");
        Data = StringReplaceAll(Data, " >", ">");
        SetDataFromStringToFile("/tmp/Data.tmp", Data);

        // Find the submission
        std::smatch Match;
        if (std::regex_search(Data.cbegin(), Data.cend(), Match, std::regex("<tr class=\"sectiontableentry[0-9]\"><td>" + SubmissionID + "</td><td align=\"right\"><a href=\"index\\.php\\?option=com_onlinejudge&amp;Itemid=8&amp;page=show_problem&amp;problem=[0-9]*\">[0-9]*</a></td><td><a href=\"index\\.php\\?option=com_onlinejudge&amp;Itemid=8&amp;page=show_problem&amp;problem=[0-9]*\">[^<]*</a></td><td>([^<]*)</td><td>C\\+\\+11</td><td>([0-9\\.]*)</td><!--<td></td>--><td>[^<]*</td></tr>"))) {
            // Get the result
            std::string Verdict = Match[1];
            if (Verdict == "In judge queue")
                usleep(500000);
            else {
                std::cout << "Succeed" << std::endl
                          << "Verdict: " << Verdict << std::endl
                          << "Run Time: " << Match[2] << "s" << std::endl;
                break;
            }
        } else
            TRIGGER_ERROR("Can not find the judge result with submission ID " + SubmissionID);
    }
}

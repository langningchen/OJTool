#include <AtCoder.hpp>
#include <Curl.hpp>
#include <Tool.hpp>
#include <iostream>
#include <tinyxml/tinyxml.h>

void ATCODER::Login(std::string Username, std::string Password) {
    std::cout << "Checking logged... " << std::flush;
    int HTTPResponseCode = 0;
    GetDataToFile("https://atcoder.jp/settings",
                  "",
                  "",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode != 302) {
        std::cout << "Already logged in" << std::endl;
        return;
    }
    std::cout << "Not logged in" << std::endl;

    std::cout << "Getting CSRF token... " << std::flush;
    GetDataToFile("https://atcoder.jp/login");
    std::string CSRFToken = GetStringBetween(GetDataFromFileToString(),
                                             "var csrfToken = \"",
                                             "\"");
    if (CSRFToken == "")
        TRIGGER_ERROR("Get CSRF token failed");
    std::cout << "Succeed" << std::endl;

    std::cout << "Logging in... " << std::flush;
    GetDataToFile("https://atcoder.jp/login",
                  "",
                  "",
                  true,
                  "username=" + URLEncode(Username) + "&password=" + URLEncode(Password) + "&csrf_token=" + URLEncode(CSRFToken),
                  NULL,
                  NULL,
                  FORM);
    if (FindLocation().find("login") != std::string::npos)
        TRIGGER_ERROR("Login failed");
    std::cout << "Succeed" << std::endl;
}
void ATCODER::GetProblemDetail(std::string ProblemID) {
    if (!IfFileExist("/tmp/AtCoder-" + ProblemID + ".md")) {
        std::cout << "Getting problem detail... " << std::flush;
        std::string ContestName = SpiltString(ProblemID, "_")[0];
        GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + ProblemID);
        std::cout << "Succeed" << std::endl;

        std::cout << "Parsing problem detail... " << std::flush;
        TiXmlDocument ProblemXmlDocument;
        ProblemXmlDocument.Parse(TOOL::TidyHTMLDocument(GetDataFromFileToString()).c_str());
        if (ProblemXmlDocument.Error())
            TRIGGER_ERROR("Parse problem detail error: "s + ProblemXmlDocument.ErrorDesc());
        std::cout << "Succeed" << std::endl;

        TiXmlHandle ProblemXmlHandle = TiXmlHandle(&ProblemXmlDocument)
                                           .FirstChild("html")
                                           .FirstChild("body")
                                           .Child("div", 2)
                                           .FirstChild("div")
                                           .FirstChild("div")
                                           .Child("div", 1);
        std::string ProblemDetail = "# " + ContestName + " " + ProblemXmlHandle.FirstChild("span").FirstChild().ToText()->Value() + "\n" +
                                    "\n";
        std::string TimeAndMemoryLimit = FixString(ProblemXmlHandle.FirstChild("p").FirstChild().ToText()->Value()) + "__END__";
        ProblemDetail += "## Other information\n"s +
                         "\n" +
                         "|Item|Value|\n" +
                         "|:---:|:---:|\n" +
                         "|Time limit|$" + GetStringBetween(TimeAndMemoryLimit, "Time Limit: ", " / ") + "$|\n" +
                         "|Memory limit|$" + GetStringBetween(TimeAndMemoryLimit, "Memory Limit: ", "__END__") + "$|\n";
        SetDataFromStringToFile("/tmp/AtCoder-" + ProblemID + ".md", ProblemDetail);
    }

    // Open the problem detail file
    if (system(std::string("code-insiders /tmp/AtCoder-" + ProblemID + ".md").c_str()))
        std::cout << "Open file \"/tmp/AtCoder-" << ProblemID << ".md\" failed, please open it manually" << std::endl;
}
void ATCODER::SubmitCode(std::string ProblemID) {
    // Get the code
    std::string Code = GetDataFromFileToString("../" + ProblemID + ".cpp");
    std::string ContestName = SpiltString(ProblemID, "_")[0];

    // Get the token
    std::cout << "Getting submit page data... " << std::flush;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/tasks/" + ProblemID);
    std::string CSRFToken = GetStringBetween(GetDataFromFileToString(),
                                             "var csrfToken = \"",
                                             "\"");
    std::cout << "Succeed" << std::endl;

    std::cout << "Submitting... " << std::flush;
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
    std::cout << "Succeed" << std::endl;

    std::cout << "Getting submission ID... " << std::flush;
    GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submissions/me");
    std::string SubmissionID = GetStringBetween(GetDataFromFileToString(),
                                                "data-id=\"",
                                                "\"");
    if (SubmissionID == "")
        TRIGGER_ERROR("Get submission ID failed");
    std::cout << "Succeed" << std::endl;

    std::cout << "Judging... " << std::flush;
    while (1) {
        GetDataToFile("https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID + "/status/json");
        json JSONData = json::parse(GetDataFromFileToString());
        std::cout << "\rJudging... " << GetStringBetween(JSONData["Html"].as_string(), ">", "<") << std::flush;
        if (JSONData["Interval"].is_null()) {
            std::cout << "\rJudging... Succeed"
                      << " " << JSONData["Status"].as_string() << std::endl;
            system(("www-browser https://atcoder.jp/contests/" + ContestName + "/submissions/" + SubmissionID).c_str());
            break;
        }
        usleep(500000);
    }
}

#include <Tool.hpp>
#include <XMOJ.hpp>
XMOJ::XMOJ() {
    ResultName[0] = "Waiting";
    ResultName[1] = "Waiting for rejudge";
    ResultName[2] = "Compiling";
    ResultName[3] = "Judging";
    ResultName[4] = "AC";
    ResultName[5] = "PE";
    ResultName[6] = "WA";
    ResultName[7] = "TE";
    ResultName[8] = "ME";
    ResultName[9] = "OLE";
    ResultName[10] = "RE";
    ResultName[11] = "CE";
    ResultName[12] = "Compiled";
    ResultName[13] = "Judged";
    ResultName[14] = "Waiting";
    ResultName[15] = "Ignored";
    ResultName[16] = "";
}
std::string XMOJ::GetCSRF() {
    // Get csrf token
    GetDataToFile("http://www.xmoj.tech/csrf.php");
    std::string Token = GetStringBetween(GetDataFromFileToString(), "value=\"", "\"");
    if (Token == "")
        TRIGGER_ERROR("Can not find csrf token");
    return Token;
}
std::string XMOJ::HTMLToText(std::string Data) {
    Data = EraseHTMLElement(Data);
    Data = HTMLDecode(Data);
    Data = StringReplaceAll(Data, "\t", "");
    Data = StringReplaceAll(Data, "\r", "");
    Data = StringReplaceAll(Data, "\n\n", "");
    Data = FixString(Data);
    return Data;
}
void XMOJ::Login(std::string Username, std::string Password) {
    // Check if the user is already logged in
    std::cout << "Checking login... " << std::flush;
    GetDataToFile("http://www.xmoj.tech/mail.php");
    if (GetDataFromFileToString().find("请登录后继续操作") == std::string::npos) {
        std::cout << "Already logged in" << std::endl;
        return;
    }
    std::cout << "Not logged in" << std::endl;
    MD5 MD5Encoder;
    std::cout << "Logging in... " << std::flush;
    GetDataToFile("http://www.xmoj.tech/login.php",
                  "",
                  "",
                  true,
                  "user_id=" + Username +
                      "&password=" + MD5Encoder.encode(Password) +
                      "&submit=" +
                      "&csrf=" + GetCSRF(),
                  NULL,
                  NULL,
                  "application/x-www-form-urlencoded");
    std::string HTMLData = GetDataFromFileToString();
    if (HTMLData.find("history.go(-2);") == std::string::npos)
        TRIGGER_ERROR("Login failed: " + GetStringBetween(HTMLData, "alert('", "');"));
    std::cout << "Success" << std::endl;
}
void XMOJ::GetProblemDetail(std::string ProblemID) {
    _GetProblemDetail(ProblemID, "id=" + ProblemID);
}
void XMOJ::_GetProblemDetail(std::string ProblemID, std::string ProblemHandle) {
    if (!IfFileExist("/tmp/XMOJ-" + ProblemID + ".md")) {
        // Gets the problem detail page
        std::cout << "Getting problem detail page... " << std::flush;
        GetDataToFile("http://www.xmoj.tech/problem.php?" + ProblemHandle);
        std::string HTMLData = GetDataFromFileToString();
        std::string Title = GetStringBetween(HTMLData, "<h2>", "</h2>");
        if (Title == "")
            TRIGGER_ERROR("Get problem detail failed: " + GetStringBetween(HTMLData, "<h2>", "</h2>"));
        std::cout << "Succeed" << std::endl;
        std::string InputMethod = GetStringBetween(HTMLData, "<span class=green>输入文件: </span>", "&nbsp;");
        std::string OutputMethod = GetStringBetween(HTMLData, "<span class=green>输出文件: </span>", "&nbsp;");
        std::string TimeLimit = GetStringBetween(HTMLData, "<span class=green>时间限制: </span>", "&nbsp;");
        std::string MemoryLimit = GetStringBetween(HTMLData, "<span class=green>内存限制: </span>", "<br>");
        std::string SubmitCount = GetStringBetween(HTMLData, "<span class=green>提交: </span>", "&nbsp;");
        std::string PassCount = GetStringBetween(HTMLData, "<span class=green>解决: </span>", "<br>");
        std::string Description = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row'><div class='cnt-row-head title'>题目描述</div><div class='cnt-row-body'><div class=content>", "</div></div></div>"));
        std::string Range = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row-head title'>数据范围</div><div class='cnt-row-body'><div class=content>", "</div></div>"));
        std::string InputFormat = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row'><div class='cnt-row-head title'>输入</div><div class='cnt-row-body'><div class=content>", "</div></div></div>"));
        std::string OutputFormat = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row'><div class='cnt-row-head title'>输出</div><div class='cnt-row-body'><div class=content>", "</div></div></div>"));
        std::vector<std::pair<std::pair<std::string, std::string>, std::string>> Samples;
        while (1) {
            std::string InputSample = GetStringBetween(HTMLData, "<div class='in-out-item' style='margin-right:.5em;'><span class='title'>样例输入 #" + std::to_string(Samples.size() + 1) + "</span><a class='copy-btn'>复制</a><pre class=content style='overflow:auto;'><span class=sampledata>", "</span></pre></div>");
            if (InputSample == "")
                break;
            std::string OutputSample = GetStringBetween(HTMLData, "<div class='in-out-item' style='margin-left:.5em;'><span class='title'>样例输出 #" + std::to_string(Samples.size() + 1) + "</span><a class='copy-btn'>复制</a><pre class=content style='overflow:auto;'><span class=sampledata>", "</span></pre></div>");
            std::string SampleDescription = GetStringBetween(HTMLData, "<div style='margin:.5em 0;'><div class='title' style='margin:.8em 0;'>样例说明 #" + std::to_string(Samples.size() + 1) + "</div><div class=content>", "</div></div></div>");
            Samples.push_back({{InputSample, OutputSample}, SampleDescription});
        }

        // Save data for CPH
        MD5 MD5Encoder;
        json CPHData;
        CPHData["name"] = Title;
        CPHData["group"] = "XMOJ - test";
        CPHData["url"] = "http://www.xmoj.tech/problem.php?" + ProblemHandle;
        CPHData["interactive"] = false;
        CPHData["memoryLimit"] = atoi(MemoryLimit.substr(0, MemoryLimit.size() - 2).c_str()) * 1024 * 1024;
        CPHData["timeLimit"] = atoi(GetStringBetween(TimeLimit, "", " ").c_str()) * 1000;
        for (size_t i = 0; i < Samples.size(); i++) {
            json Temp;
            Temp["id"] = i;
            Temp["input"] = HTMLDecode(FixString(Samples[i].first.first));
            Temp["output"] = HTMLDecode(FixString(Samples[i].first.second));
            CPHData["tests"].push_back(json(Temp));
        }
        CPHData["local"] = false;
        CPHData["srcPath"] = "/home/langningchen/XMOJ/" + ProblemID + ".cpp";
        CPHData["testType"] = "single";
        CPHData["input"]["type"] = "stdin";
        CPHData["output"]["type"] = "stdout";
        CPHData["languages"]["java"]["mainClass"] = "Main";
        CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
        CPHData["batch"]["id"] = MD5Encoder.encode(ProblemID);
        CPHData["batch"]["size"] = 1;
        SetDataFromStringToFile(TOOL::GetCPHFileName("XMOJ", ProblemID), CPHData.dump());

        // Save data for markdown
        std::string OutputContent = "# " + Title + "\n";
        OutputContent += "## Description\n"s +
                         "\n" +
                         FixString(Description) + "\n" +
                         "\n" +
                         "## Input format\n" +
                         "\n" +
                         FixString(InputFormat) + "\n" +
                         "\n" +
                         "## Output format\n" +
                         "\n" +
                         FixString(OutputFormat) + "\n" +
                         "\n";
        if (Range != "")
            OutputContent += "## Range\n"s +
                             "\n" +
                             FixString(Range) + "\n" +
                             "\n";
        OutputContent += "## Samples\n"s +
                         "\n";
        int Counter = 0;
        for (auto i : Samples) {
            Counter++;
            OutputContent += std::string("Input #" + std::to_string(Counter) + "\n") +
                             "```\n" +
                             FixString(i.first.first) + "\n" +
                             "```\n" +
                             "Output #" + std::to_string(Counter) + "\n" +
                             "```\n" +
                             FixString(i.first.second) + "\n" +
                             "```\n";
            if (i.second != "")
                OutputContent += "Description #" + std::to_string(Counter) + "\n" +
                                 FixString(i.second) + "\n";
            OutputContent += "\n";
        }
        OutputContent += "\n"s +
                         "## Other information\n" +
                         "\n";
        OutputContent += "|Item|Value|\n"s +
                         "|:---:|:---:|\n" +
                         "|Input method|`" + InputMethod + "`|\n" +
                         "|Output method|`" + OutputMethod + "`|\n" +
                         "|Time limit|$" + TimeLimit + "$|\n" +
                         "|Memory limit|$" + MemoryLimit + "$|\n" +
                         "|Submit count|$" + SubmitCount + "$|\n" +
                         "|Pass count|$" + PassCount + "$|\n" +
                         "|Pass rate|$" + std::to_string(atoi(PassCount.c_str()) * 100.0 / atoi(SubmitCount.c_str())) + "\\%$|\n" +
                         "\n";
        SetDataFromStringToFile("/tmp/XMOJ-" + ProblemID + ".md", OutputContent);
    }

    // Open the problem detail file
    if (system(std::string("code-insiders /tmp/XMOJ-" + ProblemID + ".md").c_str()))
        std::cout << "Open file \"/tmp/XMOJ-" << ProblemID << ".md\" failed, please open it manually" << std::endl;
}
void XMOJ::SubmitCode(std::string ProblemID) {
    std::string Code = GetDataFromFileToString("XMOJ/" + ProblemID + ".cpp");
    Code = StringReplaceAll(Code, "// freopen", "freopen");
    std::cout << "Getting submit page data... " << std::flush;
    GetDataToFile("http://www.xmoj.tech/submitpage.php?id=" + ProblemID);
    std::cout << "Succeed" << std::endl;
    std::string SubmitPageData = GetDataFromFileToString();
    int HTTPResponseCode = 0;

    // Submit
    std::cout << "Submitting... " << std::flush;
    GetDataToFile("http://www.xmoj.tech/submit.php",
                  "",
                  "",
                  true,
                  "id=" + ProblemID +
                      "&language=1" +
                      "&source=" + URLEncode(Code) +
                      "&enable_O2=on" +
                      "&input_text=" + URLEncode(GetStringBetween(SubmitPageData, "<textarea style=\"width:30%\" cols=40 rows=5 id=\"input_text\" name=\"input_text\" >", "</textarea>")) +
                      "&out=" + URLEncode(GetStringBetween(SubmitPageData, "<textarea style=\"width:30%\" cols=10 rows=5 id=\"out\" name=\"out\" >", "</textarea>")) +
                      "&csrf=" + GetCSRF(),
                  NULL,
                  &HTTPResponseCode,
                  "application/x-www-form-urlencoded");
    if (HTTPResponseCode != 302)
        TRIGGER_ERROR("Submit failed");
    std::cout << "Succeed" << std::endl;

    std::cout << "Getting submission ID... " << std::flush;
    GetDataToFile("http://www.xmoj.tech/" + FindLocation());
    std::string SubmissionID = GetStringBetween(GetDataFromFileToString(), "<tbody>\r\n<tr class=\"oddrow\"><td></td><td>", "</td>");
    if (SubmissionID == "")
        TRIGGER_ERROR("Can not find submission ID");
    std::cout << "Succeed" << std::endl;

    // Get the record info and wait for the result
    std::cout << "Judging... " << std::flush;
    int JudgeResult = 0;
    do {
        GetDataToFile("http://www.xmoj.tech/status-ajax.php?solution_id=" + SubmissionID);
        JudgeResult = atoi(GetStringBetween(GetDataFromFileToString(), "", ",").c_str());
        usleep(500000);
    } while (JudgeResult < 4 || JudgeResult > 11);
    std::cout << "Succeed" << std::endl;
    if (JudgeResult == 4)
        SetDataFromStringToFile("XMOJ/" + ProblemID + ".cpp", Code + "\n");
    // Check whether there is a compile error
    if (JudgeResult == 11) {
        GetDataToFile("http://www.xmoj.tech/ceinfo.php?sid=" + SubmissionID);
        std::cout << "Compile error: " << std::endl
                  << HTMLDecode(GetStringBetween(GetDataFromFileToString(), "<pre class=\"brush:c;\" id='errtxt' >", "</pre>")) << std::endl;
    } else {
        GetDataToFile("http://www.xmoj.tech/reinfo.php?sid=" + SubmissionID);
        json Result = json::parse(GetStringBetween(GetDataFromFileToString(), "var json = ", "\n"));
        int ResultCounter[17] = {0};
        if (Result["st"].as_integer() == 0) {
            std::map<std::string, std::pair<int, std::string>> Index;
            int Counter = 0;
            for (auto i : Result["tasks"]) {
                Index[((atoi(i["i"].as_string().c_str()) != 0 ||
                        i["i"].as_string() == "0") &&
                               i["i"].as_string().length() == 1
                           ? "0"
                           : "") +
                      i["i"].as_string()] = {Counter, i["i"].as_string()};
                Counter++;
            }
            for (auto i : Index) {
                std::cout << "#" << i.second.second << " "
                          << Result["tasks"][i.second.first]["sc"].as_integer() << "pts "
                          << ResultName[Result["tasks"][i.second.first]["s"].as_integer()] << " "
                          << Result["tasks"][i.second.first]["t"].as_integer() << "ms "
                          << Result["tasks"][i.second.first]["m"].as_integer() << "B" << std::endl;
                ResultCounter[Result["tasks"][i.second.first]["s"].as_integer()]++;
            }
        } else {
            for (auto i : Result["tasks"]) {
                std::cout << "#" << i["i"].as_integer() << " " << i["s"].as_integer() << "pts" << std::endl;
                int Counter = 0;
                for (auto j : i["t"]) {
                    Counter++;
                    std::cout << "    #" << Counter << " "
                              << j["sc"].as_integer() << "pts "
                              << ResultName[j["s"].as_integer()] << " "
                              << j["t"].as_integer() << "ms "
                              << j["m"].as_integer() << "B" << std::endl;
                    ResultCounter[j["s"].as_integer()]++;
                }
            }
        }
    }
}
void XMOJ::GetContestProblemsDetails(std::string ContestID) {
    GetDataToFile("http://www.xmoj.tech/contest.php?cid=" + ContestID);
    std::string ContestPageData = GetDataFromFileToString();
    int ProblemCount = 0;
    while (1) {
        std::string ProblemID = GetStringBetween(ContestPageData, "\t&nbsp;", " &nbsp;");
        if (ProblemID == "")
            break;
        _GetProblemDetail(ProblemID, "cid=" + ContestID + "&pid=" + std::to_string(ProblemCount));
        ContestPageData = ContestPageData.substr(ContestPageData.find("\t&nbsp;") + 1);
        ProblemCount++;
        std::cout << "Problem " << ProblemID << " has been downloaded" << std::endl;
    }
}

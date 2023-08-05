#include "Tool.hpp"
#include "Etiger.hpp"
ETIGER::ETIGER()
{
    DifficultyName[1] = make_pair("入门难度", "#979797");
    DifficultyName[2] = make_pair("普及-", "#79d479");
    DifficultyName[3] = make_pair("普及/提高-", "#4191ff");
    DifficultyName[4] = make_pair("普及+/提高", "yellowgreen");
    DifficultyName[5] = make_pair("提高+/省选-", "plum");
    DifficultyName[6] = make_pair("省选+/NOI", "goldenrod");
    DifficultyName[7] = make_pair("NOI+/CTSC/IOI", "orange");
    DifficultyName[8] = make_pair("传说", "red");
}
void ETIGER::Login(string Username, string Password)
{
    // Create login request
    json LoginRequest;
    LoginRequest["name"] = Username;
    LoginRequest["password"] = Password;

    // Add headers
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");

    // Send login request
    cout << "Logging in... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/user/login",
                  "",
                  "",
                  true,
                  LoginRequest.dump(),
                  HeaderList);

    // Parse login response
    json LoginInfo = json::parse(GetDataFromFileToString());

    // Check login response
    if (LoginInfo["code"] != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Login failed",
                                            LoginInfo["code"].as_integer(),
                                            LoginInfo["msg"].as_string());
    }
    TOOL::Speak("Login succeeds");
    cout << "Succeed" << endl;

    // Save token
    Token = LoginInfo["data"]["ticket"].as_string();
}
void ETIGER::ClockIn()
{
    // Add headers
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Send clock in request
    cout << "Clocking in... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/sign/dailySign",
                  "",
                  "",
                  false,
                  "",
                  HeaderList);

    // Parse clock in response
    json ClockInInfo = json::parse(GetDataFromFileToString());
    if (ClockInInfo["code"] != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Clock in failed",
                                            ClockInInfo["code"].as_integer(),
                                            ClockInInfo["msg"].as_string());
        return;
    }
    cout << "Succeed" << endl;
}
void ETIGER::GetProblemDetail(string ProblemID)
{
    if (!IfFileExist("/tmp/Etiger-" + ProblemID + ".md"))
    {
        // Add headers
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
        HeaderList = curl_slist_append(HeaderList, "lang: zh");
        HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
        HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

        // Send request
        cout << "Getting problem detail... " << flush;
        GetDataToFile("https://www.etiger.vip/thrall-web/question/getById?id=" + ProblemID,
                      "",
                      "",
                      false,
                      "",
                      HeaderList);

        // Parse response
        json ProblemInfo = json::parse(GetDataFromFileToString());
        if (ProblemInfo["code"] != 200)
        {
            TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get problem detail failed",
                                                ProblemInfo["code"].as_integer(),
                                                ProblemInfo["msg"].as_string());
        }
        cout << "Succeed" << endl;

        // Save data for CPH
        json CPHData;
        CPHData["name"] = ProblemInfo["data"]["title"].as_string();
        CPHData["group"] = "Etiger - test";
        CPHData["url"] = "https://etiger.vip";
        CPHData["interactive"] = false;
        CPHData["memoryLimit"] = ProblemInfo["data"]["memLimit"].as_integer();
        CPHData["timeLimit"] = ProblemInfo["data"]["timeLimit"].as_integer() * 1000;
        string InputSample = ProblemInfo["data"]["inputSample"].as_string();
        string OutputSample = ProblemInfo["data"]["outputSample"].as_string();
        vector<string> InputSamples = SpiltString(InputSample, ";");
        vector<string> OutputSamples = SpiltString(OutputSample, ";");
        for (size_t i = 0; i < InputSamples.size(); i++)
        {
            string Input = FixString(InputSamples[i]);
            string Output = FixString(OutputSamples[i]);
            // If input or output is empty, skip this test case
            if (Input == "" || Input == "无" || Output == "" || Output == "无")
                continue;
            CPHData["tests"][i]["input"] = Input;
            CPHData["tests"][i]["output"] = Output;
            CPHData["tests"][i]["id"] = i;
        }
        CPHData["local"] = false;
        CPHData["srcPath"] = "/home/langningc2009/Etiger/" + ProblemID + ".cpp";
        CPHData["testType"] = "single";
        CPHData["input"]["type"] = "stdin";
        CPHData["output"]["type"] = "stdout";
        CPHData["languages"]["java"]["mainClass"] = "Main";
        CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
        CPHData["batch"]["id"] = ProblemID;
        CPHData["batch"]["size"] = 1;
        SetDataFromStringToFile(TOOL::GetCPHFileName("Etiger", ProblemID), CPHData.dump());

        // Sava markdown file
        string OutputContent = "";
        OutputContent += "# " + ProblemID + " " + ProblemInfo["data"]["title"].as_string() + "\n" +
                         "\n" +
                         "## 题目描述\n" +
                         "\n" +
                         FixString(EraseHTMLElement(ProblemInfo["data"]["content"].as_string())) + "\n" +
                         "\n" +
                         "## 输入格式\n" +
                         "\n" +
                         FixString(ProblemInfo["data"]["inputFormat"].as_string()) + "\n" +
                         "\n" +
                         "## 输出格式\n" +
                         "\n" +
                         FixString(ProblemInfo["data"]["outputFormat"].as_string()) + "\n" +
                         "\n";
        if (!ProblemInfo["data"]["ioName"].is_null())
            OutputContent += "## 输入输出文件\n"s +
                             "\n" +
                             "`" + FixString(ProblemInfo["data"]["ioName"].as_string()) + "`\n" +
                             "\n";
        OutputContent += "## 输入输出样例\n"s +
                         "\n";
        int Counter = 1;
        while (InputSample.find(";") != string::npos && OutputSample.find(";") != string::npos)
        {
            if (FixString(InputSample.substr(0, InputSample.find(";"))) != "无")
            {
                OutputContent += "输入 #" + to_string(Counter) + "\n" +
                                 "```\n" +
                                 FixString(InputSample.substr(0, InputSample.find(";"))) + "\n" +
                                 "```\n" +
                                 "输出 #" + to_string(Counter) + "\n" +
                                 "```\n" +
                                 FixString(OutputSample.substr(0, OutputSample.find(";"))) + "\n" +
                                 "```\n";
            }
            InputSample.erase(0, InputSample.find(";") + 1);
            OutputSample.erase(0, OutputSample.find(";") + 1);
            Counter++;
        }
        OutputContent += "\n";
        if (EraseHTMLElement(ProblemInfo["data"]["description"].as_string()) != "")
        {
            OutputContent += "## 说明\n"s +
                             "\n" +
                             FixString(EraseHTMLElement(ProblemInfo["data"]["description"].as_string())) + "\n" +
                             "\n";
        }
        OutputContent += "## 其他数据\n"s +
                         "\n" +
                         "|项目|值|\n" +
                         "|:---:|:---:|\n" +
                         "|难度|<span style=\"" +
                         "text-align: center; " +
                         "display: inline-block; " +
                         "border-radius: 3px; " +
                         "color: white; " +
                         "width: 120px; " +
                         "height: 24px; " +
                         "background-color: " + DifficultyName[ProblemInfo["data"]["level"].as_integer()].second +
                         "\">" +
                         DifficultyName[ProblemInfo["data"]["level"].as_integer()].first + "</span>|\n" +
                         "|提交次数|$" + ProblemInfo["data"]["submitInfo"]["totalCount"].as_string() + "$|\n" +
                         "|提交人数|$" + ProblemInfo["data"]["submitInfo"]["submitPersonCount"].as_string() + "$|\n" +
                         "|通过人数|$" + ProblemInfo["data"]["submitInfo"]["passCount"].as_string() + "$|\n" +
                         "|通过率|$" + ProblemInfo["data"]["submitInfo"]["passRate"].as_string() + "\\%$|\n" +
                         "\n";
        SetDataFromStringToFile("/tmp/Etiger-" + ProblemID + ".md", OutputContent);
    }

    // Open file
    if (system(string("code-insiders /tmp/Etiger-" + ProblemID + ".md").c_str()))
        cout << "Open file \"/tmp/Etiger-" << ProblemID << ".md\" failed, please open it manually" << endl;
    TOOL::Speak("Get problem detail succeed");
}
// TODO: When input is "data is too long to provide", don't add it to CPH
void ETIGER::SubmitCode(string ProblemID)
{
    // Get code and uncomment freopen
    string Code = GetDataFromFileToString("Etiger/" + ProblemID + ".cpp");
    Code = StringReplaceAll(Code, "// freopen", "freopen");

    // Create submit request
    json SubmitRequest;
    SubmitRequest["comment"] = "";
    SubmitRequest["lang"] = "CPP";
    SubmitRequest["submitType"] = 0;
    SubmitRequest["problemId"] = ProblemID;
    SubmitRequest["src"] = Code;

    // Create header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Submit
    cout << "Submitting... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/saveSubmit",
                  "",
                  "",
                  true,
                  SubmitRequest.dump(),
                  HeaderList);

    // Get result
    json SubmitInfo = json::parse(GetDataFromFileToString());
    if (SubmitInfo["code"] != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get submit result failed",
                                            SubmitInfo["code"].as_integer(),
                                            SubmitInfo["msg"].as_string());
    }
    cout << "Succeed" << endl;

    // Check whether the code is accepted
    if (SubmitInfo["data"]["grade"].as_integer() == 100)
    {
        SetDataFromStringToFile("Etiger/" + ProblemID + ".cpp", Code + "\n");
        // Remove temporary files
        cout << "Congratulations! You have solved this problem!" << endl;
        TOOL::Speak("Congratulations! You have solved this problem!");
    }
    else
    {
        // Output result
        int Counter = 1;
        for (auto i : SubmitInfo["data"]["result"])
        {
            cout << "#" << Counter << " "
                 << i["type"].as_string() << " "
                 << i["timeUsed"] << "ms "
                 << i["memUsed"] << "B" << endl;
            Counter++;
            if (i["input"].as_string() != "")
            {
                cout << "    Input: " << i["input"].as_string() << endl
                     << "    Standard output: " << i["output"].as_string() << endl
                     << "    My output: " << i["myOutput"].as_string() << endl;
                json CPHData = json::parse(GetDataFromFileToString(TOOL::GetCPHFileName("Etiger", ProblemID)));
                CPHData["tests"].push_back({{"input", i["input"].as_string()},
                                            {"output", i["output"].as_string()},
                                            {"id", Counter}});
                SetDataFromStringToFile(TOOL::GetCPHFileName("Etiger", ProblemID), CPHData.dump());
            }
        }
        cout << SubmitInfo["data"]["grade"] << "pts" << endl;
        TOOL::Speak("You did not solve this problem");
    }
}
void ETIGER::GetAnswerOrTips(string ProblemID)
{
    // Create header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json;charset=utf-8");
    HeaderList = curl_slist_append(HeaderList, "lang: zh");
    HeaderList = curl_slist_append(HeaderList, "Host: www.etiger.vip");
    HeaderList = curl_slist_append(HeaderList, string("Token: " + Token).c_str());

    // Get tips
    cout << "Getting comments page data... " << flush;
    GetDataToFile("https://www.etiger.vip/thrall-web/comment/getByQuestionForPage?questionId=" + ProblemID + "&cpage=1&pagesize=10",
                  "",
                  "",
                  false,
                  "",
                  HeaderList);

    // Get result
    json CommentsData = json::parse(GetDataFromFileToString());
    if (CommentsData["code"] != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get comments failed",
                                            CommentsData["code"].as_integer(),
                                            CommentsData["msg"].as_string());
    }
    cout << "Success" << endl;

    // Save comments to a string joined by newline
    string Comments = "";
    for (auto i : CommentsData["data"]["records"])
        Comments += FixString(i["content"].as_string()) + "\n";

    // Add comments to the code
    SetDataFromStringToFile("Etiger/" + ProblemID + ".cpp",
                            FixString(GetDataFromFileToString("Etiger/" + ProblemID + ".cpp")) +
                                "\n" +
                                "\n" +
                                "/*\n" +
                                Comments +
                                "*/" +
                                "\n");
}

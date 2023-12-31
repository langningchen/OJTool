#include "Tool.hpp"
#include "XMOJ.hpp"
XMOJ::XMOJ()
{
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
string XMOJ::GetCSRF()
{
    // Get csrf token
    GetDataToFile("http://www.xmoj.tech/csrf.php");
    string Token = GetStringBetween(GetDataFromFileToString(), "value=\"", "\"");
    if (Token == "")
        TRIGGER_ERROR("Can not find csrf token");
    return Token;
}
string XMOJ::HTMLToText(string Data)
{
    Data = EraseHTMLElement(Data);
    Data = HTMLDecode(Data);
    Data = StringReplaceAll(Data, "\t", "");
    Data = StringReplaceAll(Data, "\r", "");
    Data = StringReplaceAll(Data, "\n\n", "");
    Data = FixString(Data);
    return Data;
}
void XMOJ::Login(string Username, string Password)
{
    // Check if the user is already logged in
    cout << "Checking login... " << flush;
    GetDataToFile("http://www.xmoj.tech/mail.php");
    if (GetDataFromFileToString().find("请登录后继续操作") == string::npos)
    {
        TOOL::Speak("Already logged in");
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;
    MD5 MD5Encoder;
    cout << "Logging in... " << flush;
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
    string HTMLData = GetDataFromFileToString();
    if (HTMLData.find("history.go(-2);") == string::npos)
        TRIGGER_ERROR("Login failed: " + GetStringBetween(HTMLData, "alert('", "');"));
    TOOL::Speak("Login succeeds");
    cout << "Success" << endl;
}
void XMOJ::GetProblemDetail(string ProblemID)
{
    _GetProblemDetail(ProblemID, "id=" + ProblemID);
}
void XMOJ::_GetProblemDetail(string ProblemID, string ProblemHandle)
{
    if (!IfFileExist(TempFolder + "XMOJ-" + ProblemID + ".md"))
    {
        // Gets the problem detail page
        cout << "Getting problem detail page... " << flush;
        GetDataToFile("http://www.xmoj.tech/problem.php?" + ProblemHandle);
        string HTMLData = GetDataFromFileToString();
        string Title = GetStringBetween(HTMLData, "<h2>", "</h2>");
        if (Title == "")
            TRIGGER_ERROR("Get problem detail failed: " + GetStringBetween(HTMLData, "<h2>", "</h2>"));
        cout << "Succeed" << endl;
        string InputMethod = GetStringBetween(HTMLData, "<span class=green>输入文件: </span>", "&nbsp;");
        string OutputMethod = GetStringBetween(HTMLData, "<span class=green>输出文件: </span>", "&nbsp;");
        string TimeLimit = GetStringBetween(HTMLData, "<span class=green>时间限制: </span>", "&nbsp;");
        string MemoryLimit = GetStringBetween(HTMLData, "<span class=green>内存限制: </span>", "<br>");
        string SubmitCount = GetStringBetween(HTMLData, "<span class=green>提交: </span>", "&nbsp;");
        string PassCount = GetStringBetween(HTMLData, "<span class=green>解决: </span>", "<br>");
        string Description = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row'><div class='cnt-row-head title'>题目描述</div><div class='cnt-row-body'><div class=content>", "</div></div></div>"));
        string Range = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row-head title'>数据范围</div><div class='cnt-row-body'><div class=content>", "</div></div>"));
        string InputFormat = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row'><div class='cnt-row-head title'>输入</div><div class='cnt-row-body'><div class=content>", "</div></div></div>"));
        string OutputFormat = HTMLToText(GetStringBetween(HTMLData, "<div class='cnt-row'><div class='cnt-row-head title'>输出</div><div class='cnt-row-body'><div class=content>", "</div></div></div>"));
        vector<pair<pair<string, string>, string>> Samples;
        while (1)
        {
            string InputSample = GetStringBetween(HTMLData, "<div class='in-out-item' style='margin-right:.5em;'><span class='title'>样例输入 #" + to_string(Samples.size() + 1) + "</span><a class='copy-btn'>复制</a><pre class=content style='overflow:auto;'><span class=sampledata>", "</span></pre></div>");
            if (InputSample == "")
                break;
            string OutputSample = GetStringBetween(HTMLData, "<div class='in-out-item' style='margin-left:.5em;'><span class='title'>样例输出 #" + to_string(Samples.size() + 1) + "</span><a class='copy-btn'>复制</a><pre class=content style='overflow:auto;'><span class=sampledata>", "</span></pre></div>");
            string SampleDescription = GetStringBetween(HTMLData, "<div style='margin:.5em 0;'><div class='title' style='margin:.8em 0;'>样例说明 #" + to_string(Samples.size() + 1) + "</div><div class=content>", "</div></div></div>");
            Samples.push_back({{InputSample, OutputSample}, SampleDescription});
        }

#ifndef _WIN32
        // Save data for CPH
        MD5 MD5Encoder;
        json CPHData;
        CPHData["name"] = Title;
        CPHData["group"] = "XMOJ - test";
        CPHData["url"] = "http://www.xmoj.tech/problem.php?" + ProblemHandle;
        CPHData["interactive"] = false;
        CPHData["memoryLimit"] = atoi(MemoryLimit.substr(0, MemoryLimit.size() - 2).c_str()) * 1024 * 1024;
        CPHData["timeLimit"] = atoi(GetStringBetween(TimeLimit, "", " ").c_str()) * 1000;
        for (size_t i = 0; i < Samples.size(); i++)
        {
            json Temp;
            Temp["id"] = i;
            Temp["input"] = HTMLDecode(FixString(Samples[i].first.first));
            Temp["output"] = HTMLDecode(FixString(Samples[i].first.second));
            CPHData["tests"].push_back(json(Temp));
        }
        CPHData["local"] = false;
        CPHData["srcPath"] = "/home/langningc2009/XMOJ/" + ProblemID + ".cpp";
        CPHData["testType"] = "single";
        CPHData["input"]["type"] = "stdin";
        CPHData["output"]["type"] = "stdout";
        CPHData["languages"]["java"]["mainClass"] = "Main";
        CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
        CPHData["batch"]["id"] = MD5Encoder.encode(ProblemID);
        CPHData["batch"]["size"] = 1;
        SetDataFromStringToFile(TOOL::GetCPHFileName("XMOJ", ProblemID), CPHData.dump());
#endif

        // Save data for markdown
        string OutputContent = "# " + Title + "\n";
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
        for (auto i : Samples)
        {
            Counter++;
            OutputContent += string("Input #" + to_string(Counter) + "\n") +
                             "```\n" +
                             FixString(i.first.first) + "\n" +
                             "```\n" +
                             "Output #" + to_string(Counter) + "\n" +
                             "```\n" +
                             FixString(i.first.second) + "\n" +
                             "```\n";
            if (i.second != "")
                OutputContent += "Description #" + to_string(Counter) + "\n" +
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
                         "|Pass rate|$" + to_string(atoi(PassCount.c_str()) * 100.0 / atoi(SubmitCount.c_str())) + "\\%$|\n" +
                         "\n";
        SetDataFromStringToFile(TempFolder + "XMOJ-" + ProblemID + ".md", OutputContent);
    }

    // Open the problem detail file
    if (system(string("code-insiders /tmp/XMOJ-" + ProblemID + ".md").c_str()))
        cout << "Open file \"/tmp/XMOJ-" << ProblemID << ".md\" failed, please open it manually" << endl;
    TOOL::Speak("Get problem detail succeed");
}
void XMOJ::SubmitCode(string ProblemID)
{
    string Code = GetDataFromFileToString("XMOJ/" + ProblemID + ".cpp");
    Code = StringReplaceAll(Code, "// freopen", "freopen");
    cout << "Getting submit page data... " << flush;
    GetDataToFile("http://www.xmoj.tech/submitpage.php?id=" + ProblemID);
    cout << "Succeed" << endl;
    string SubmitPageData = GetDataFromFileToString();
    int HTTPResponseCode = 0;

    // Submit
    cout << "Submitting... " << flush;
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
    cout << "Succeed" << endl;

    cout << "Getting submission ID... " << flush;
    GetDataToFile("http://www.xmoj.tech/" + FindLocation());
    string SubmissionID = GetStringBetween(GetDataFromFileToString(), "<tbody>\r\n<tr class=\"oddrow\"><td></td><td>", "</td>");
    if (SubmissionID == "")
        TRIGGER_ERROR("Can not find submission ID");
    cout << "Succeed" << endl;
    TOOL::Speak("Submit succeed");

    // Get the record info and wait for the result
    cout << "Judging... " << flush;
    int JudgeResult = 0;
    do
    {
        GetDataToFile("http://www.xmoj.tech/status-ajax.php?solution_id=" + SubmissionID);
        JudgeResult = atoi(GetStringBetween(GetDataFromFileToString(), "", ",").c_str());
        usleep(500000);
    } while (JudgeResult < 4 || JudgeResult > 11);
    cout << "Succeed" << endl;
    if (JudgeResult == 4)
    {
        SetDataFromStringToFile("XMOJ/" + ProblemID + ".cpp", Code + "\n");
        cout << "Congratulations, you have solved this problem" << endl;
        TOOL::Speak("Congratulations, you have solved this problem");
    }
    else
    {
        // Check whether there is a compile error
        if (JudgeResult == 11)
        {
            GetDataToFile("http://www.xmoj.tech/ceinfo.php?sid=" + SubmissionID);
            cout << "Compile error: " << endl
                 << HTMLDecode(GetStringBetween(GetDataFromFileToString(), "<pre class=\"brush:c;\" id='errtxt' >", "</pre>")) << endl;
            TOOL::Speak("You have a compile error");
        }
        else
        {
            GetDataToFile("http://www.xmoj.tech/reinfo.php?sid=" + SubmissionID);
            json Result = json::parse(GetStringBetween(GetDataFromFileToString(), "var json = ", "\n"));
            int ResultCounter[17] = {0};
            if (Result["st"].as_integer() == 0)
            {
                map<string, pair<int, string>> Index;
                int Counter = 0;
                for (auto i : Result["tasks"])
                {
                    Index[((atoi(i["i"].as_string().c_str()) != 0 ||
                            i["i"].as_string() == "0") &&
                                   i["i"].as_string().length() == 1
                               ? "0"
                               : "") +
                          i["i"].as_string()] = {Counter, i["i"].as_string()};
                    Counter++;
                }
                for (auto i : Index)
                {
                    cout << "#" << i.second.second << " "
                         << Result["tasks"][i.second.first]["sc"].as_integer() << "pts "
                         << ResultName[Result["tasks"][i.second.first]["s"].as_integer()] << " "
                         << Result["tasks"][i.second.first]["t"].as_integer() << "ms "
                         << Result["tasks"][i.second.first]["m"].as_integer() << "B" << endl;
                    ResultCounter[Result["tasks"][i.second.first]["s"].as_integer()]++;
                }
            }
            else
            {
                for (auto i : Result["tasks"])
                {
                    cout << "#" << i["i"].as_integer() << " " << i["s"].as_integer() << "pts" << endl;
                    int Counter = 0;
                    for (auto j : i["t"])
                    {
                        Counter++;
                        cout << "    #" << Counter << " "
                             << j["sc"].as_integer() << "pts "
                             << ResultName[j["s"].as_integer()] << " "
                             << j["t"].as_integer() << "ms "
                             << j["m"].as_integer() << "B" << endl;
                        ResultCounter[j["s"].as_integer()]++;
                    }
                }
            }
            std::string SpeakString = "You have ";
            for (int i = 0; i < 17; i++)
                if (ResultCounter[i] != 0)
                {
                    SpeakString += to_string(ResultCounter[i]) + " ";
                    for (size_t j = 0; j < ResultName[i].length(); j++)
                    {
                        SpeakString.push_back(ResultName[i][j]);
                        SpeakString.push_back(' ');
                    }
                    SpeakString += ", ";
                }
            SpeakString = SpeakString.substr(0, SpeakString.length() - 2);
            SpeakString += " in this problem";
            TOOL::Speak(SpeakString);
        }
    }
}
void XMOJ::GetContestProblemsDetails(string ContestID)
{
    GetDataToFile("http://www.xmoj.tech/contest.php?cid=" + ContestID);
    string ContestPageData = GetDataFromFileToString();
    int ProblemCount = 0;
    while (1)
    {
        string ProblemID = GetStringBetween(ContestPageData, "\t&nbsp;", " &nbsp;");
        if (ProblemID == "")
            break;
        _GetProblemDetail(ProblemID, "cid=" + ContestID + "&pid=" + to_string(ProblemCount));
        ContestPageData = ContestPageData.substr(ContestPageData.find("\t&nbsp;") + 1);
        ProblemCount++;
        cout << "Problem " << ProblemID << " has been downloaded" << endl;
    }
}

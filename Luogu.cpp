#include "Tool.hpp"
TOOL::LUOGU::LUOGU()
{
    ColorList["blue-1"] = "e0f7ff";
    ColorList["blue-2"] = "89d1f5";
    ColorList["blue-3"] = "3498db";
    ColorList["blue-4"] = "14558f";
    ColorList["blue-5"] = "052242";
    ColorList["green-1"] = "d9f0c7";
    ColorList["green-2"] = "94d66d";
    ColorList["green-3"] = "52c41a";
    ColorList["green-4"] = "22700a";
    ColorList["green-5"] = "072401";
    ColorList["purple-1"] = "fbedff";
    ColorList["purple-2"] = "ce8ee8";
    ColorList["purple-3"] = "9d3dcf";
    ColorList["purple-4"] = "561982";
    ColorList["purple-5"] = "1f0736";
    ColorList["orange-1"] = "ffedb5";
    ColorList["orange-2"] = "ffce63";
    ColorList["orange-3"] = "f39c11";
    ColorList["orange-4"] = "a65b00";
    ColorList["orange-5"] = "592b00";
    ColorList["pink-1"] = "fff0f0";
    ColorList["pink-2"] = "ff9ea3";
    ColorList["pink-3"] = "fe4c61";
    ColorList["pink-4"] = "b3243e";
    ColorList["pink-5"] = "660e24";
    ColorList["lapis-1"] = "cad5e8";
    ColorList["lapis-2"] = "728dcf";
    ColorList["lapis-3"] = "2949b4";
    ColorList["lapis-4"] = "0e1d69";
    ColorList["lapis-5"] = "02051c";
    ColorList["gold-1"] = "fff6ba";
    ColorList["gold-2"] = "ffe169";
    ColorList["gold-3"] = "ffc116";
    ColorList["gold-4"] = "b37700";
    ColorList["gold-5"] = "663d00";
    ColorList["cyan-1"] = "b5f5ec";
    ColorList["cyan-2"] = "5cdbd3";
    ColorList["cyan-3"] = "13c2c2";
    ColorList["cyan-4"] = "006d75";
    ColorList["cyan-5"] = "002329";
    ColorList["yellow-1"] = "ffffb8";
    ColorList["yellow-2"] = "fffb8f";
    ColorList["yellow-3"] = "fadb14";
    ColorList["yellow-4"] = "ad8b00";
    ColorList["yellow-5"] = "614700";
    ColorList["red-1"] = "ffebe6";
    ColorList["red-2"] = "ffa694";
    ColorList["red-3"] = "e74c3c";
    ColorList["red-4"] = "9c1d19";
    ColorList["red-5"] = "4f080a";
    ColorList["grey-1"] = "fafafa";
    ColorList["grey-2"] = "e8e8e8";
    ColorList["grey-3"] = "bfbfbf";
    ColorList["grey-4"] = "595959";
    ColorList["grey-5"] = "262626";
    ColorList["lgreen-1"] = "dae0d3";
    ColorList["lgreen-2"] = "aac791";
    ColorList["lgreen-3"] = "70ad47";
    ColorList["lgreen-4"] = "34611e";
    ColorList["lgreen-5"] = "091405";
    ColorList["primary"] = "3498db";
    ColorList["link"] = "3498db";
    ColorList["success"] = "52c41a";
    ColorList["warning"] = "ffc116";
    ColorList["error"] = "e74c3c";
    ColorList["clicked"] = "2949b4";
    ColorList["background"] = "e8e8e8";
    ColorList["level-0"] = "bfbfbf";
    ColorList["level-1"] = "3498db";
    ColorList["level-2"] = "52c41a";
    ColorList["level-3"] = "f39c11";
    ColorList["level-4"] = "fe4c61";
    ColorList["level-5"] = "9d3dcf";
    ColorList["level--1"] = "ad8b00";
    ColorList["user-color-Cheater"] = "ad8b00";
    ColorList["user-color-Gray"] = "bfbfbf";
    ColorList["user-color-Blue"] = "3498db";
    ColorList["user-color-Green"] = "52c41a";
    ColorList["user-color-Orange"] = "f39c11";
    ColorList["user-color-Red"] = "fe4c61";
    ColorList["user-color-Purple"] = "9d3dcf";
    ColorList["vip"] = "dfc289";

    // Get the configuration information of the luogu website.
    cout << "Getting luogu config... " << flush;
    GetDataToFile("https://www.luogu.com.cn/_lfe/config");
    json Config = json::parse(GetDataFromFileToString());
    cout << "Succeed" << endl;

    // Get the tag information of the luogu website.
    cout << "Getting luogu tags... " << flush;
    GetDataToFile("https://www.luogu.com.cn/_lfe/tags");
    json Tag = json::parse(GetDataFromFileToString());
    cout << "Succeed" << endl;

    // Get the language information of the luogu website.
    for (auto i : Config["codeLanguages"])
    {
        LanguageName[i["value"].as_integer()] = i["name"].as_string();
        LanguageMarkdownName[i["value"].as_integer()] = i["hljsMode"].as_string();
    }
    LanguageName[0] = "自动识别语言";

    // Get the difficulty information of the luogu website.
    for (auto i : Config["problemDifficulty"])
        DifficultyName[i["id"].as_integer()] = make_pair(i["name"].as_string(),
                                                         i["color"].as_string());

    // Get the problem type information of the luogu website.
    for (auto i : Config["problemTypes"])
        TypeName[i["id"].as_string()] = i["name"].as_string();
    json Temp;

    // Get the tag type information of the luogu website.
    for (auto i : Tag["types"])
        Temp[i["id"].as_integer()] = i["color"].as_string();

    // Get the tag information of the luogu website.
    for (auto i : Tag["tags"])
        TagName[i["id"].as_integer()] = make_pair(i["name"].as_string(),
                                                  Temp[i["type"].as_integer()]);

    // Get the submission status information of the luogu website.
    for (auto i : Config["recordStatus"])
        RecordName[i["id"].as_integer()] = make_pair(i["name"].as_string(),
                                                     i["shortName"].as_string());
}
string TOOL::LUOGU::GetCSRF()
{
    // Get csrf token
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<meta name=\"csrf-token\" content=\"", "\"");
    if (Token == "")
    {
        TRIGGER_ERROR("Can not find csrf token");
    }
    return Token;
}
void TOOL::LUOGU::Login(string Username, string Password)
{
    // Check if the user is logged in.
    int HTTPResponseCode = 0;
    cout << "Checking login... " << flush;
    GetDataToFile("https://www.luogu.com.cn/auth/login",
                  "Header.tmp",
                  "Body.tmp",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode == 302)
    {
        cout << "Already logged in" << endl;
        return;
    }
    cout << "Not logged in" << endl;

    string Token = GetCSRF();
    int ErrorCounter = 0;
    while (1)
    {
        // Get login captcha
        cout << "Getting login captcha... " << flush;
        GetDataToFile("https://www.luogu.com.cn/api/verify/captcha",
                      "Header.tmp",
                      "Captcha.jpeg");
        cout << "Succeed" << endl;

        // Predict captcha
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, "Content-Type: application/json");
        cout << "Predicting captcha by web api... " << flush;
        string Captcha = "";
        try
        {
            GetDataToFile("https://luogu-captcha-bypass.piterator.com/predict/",
                          "Header.tmp",
                          "Body.tmp",
                          true,
                          "data:image/jpeg;base64," +
                              Base64Encode(
                                  GetDataFromFileToString("Captcha.jpeg")),
                          HeaderList);
            cout << "Succeed" << endl;
            Captcha = GetDataFromFileToString();
        }
        catch (CLNException &Exception)
        {
            cout << "Failed" << endl
                 << "Predicting captcha by tensorflow... " << flush;
            if (system(("python " + CurrentDir + "Projects/OJTool/PredictLuoguCaptcha.py > /dev/null 2>&1").c_str()) == 0)
            {
                cout << "Succeed" << endl;
                Captcha = FixString(GetDataFromFileToString("Captcha.txt"));
            }
            else
            {
                cout << "Failed" << endl;
                system(("code " + CurrentDir + "Captcha.jpeg").c_str());
                cout << "Please input the captcha: ";
                cin >> Captcha;
            }
        }
        remove((CurrentDir + "Captcha.jpeg").c_str());

        // Create a json object to store the login request info
        json LoginRequest;
        LoginRequest["username"] = Username;
        LoginRequest["password"] = Password;
        LoginRequest["captcha"] = Captcha;

        // Create a header list for the curl request
        HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
        HeaderList = curl_slist_append(HeaderList, string("Content-Length: " +
                                                          to_string(LoginRequest.dump().size()))
                                                       .c_str());
        HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/auth/login");
        HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

        // Send the login request to the server
        cout << "Logging in... " << flush;
        GetDataToFile("https://www.luogu.com.cn/api/auth/userPassLogin",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      LoginRequest.dump(),
                      HeaderList);

        // Parse the response to a json object
        json LoginInfo = json::parse(GetDataFromFileToString());
        if (!LoginInfo["status"].is_null())
        {
            // If the captcha is incorrect and the error counter is less than 5, try again.
            if (LoginInfo["data"].as_string() != "验证码错误" && ErrorCounter < 5)
            {
                TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Login failed",
                                                    LoginInfo["status"].as_integer(),
                                                    LoginInfo["data"].as_string());
            }
            else
                cout << "Failed (Captcha check failed for " << ErrorCounter + 1 << " times)" << endl;
        }
        else
        {
            cout << "Succeed" << endl;
            break;
        }
        ErrorCounter++;
    }
}
void TOOL::LUOGU::ClockIn()
{
    // Gets the clock-in page data
    cout << "Get clock in page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/");
    string Token = GetCSRF();
    cout << "Succeed" << endl;

    // Gets the clock-in header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

    // Clocks in
    cout << "Clocking in... " << flush;
    GetDataToFile("https://www.luogu.com.cn/index/ajax_punch",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  "{}",
                  HeaderList);

    // Parse the response to a json object
    json ClockInInfo = json::parse(GetDataFromFileToString());
    if (ClockInInfo["code"].as_integer() != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Clock in failed",
                                            ClockInInfo["code"].as_integer(),
                                            ClockInInfo["message"].as_string());
    }
    cout << "Succeed" << endl;
}
void TOOL::LUOGU::GetQuestionDetail(string QuestionID)
{
    // Gets the question detail page
    cout << "Getting question detail page... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID + "?_contentOnly=1");
    json QuestionInfo = json::parse(GetDataFromFileToString());
    if (QuestionInfo["code"].as_integer() != 200)
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get question detail failed",
                                            QuestionInfo["code"].as_integer(),
                                            QuestionInfo["currentData"]["errorMessage"].as_string());
    }
    cout << "Succeed" << endl;

    // Save data for CPH
    MD5 MD5Encoder;
    json CPHData;
    CPHData["name"] = QuestionInfo["currentData"]["problem"]["title"].as_string();
    CPHData["group"] = "Luogu - test";
    CPHData["url"] = "https://www.luogu.com.cn/problem/" + QuestionID;
    CPHData["interactive"] = false;
    CPHData["memoryLimit"] = 0;
    for (auto i : QuestionInfo["currentData"]["problem"]["limits"]["memory"])
        CPHData["memoryLimit"] = max(CPHData["memoryLimit"].as_integer(), i.as_integer());
    CPHData["timeLimit"] = 0;
    for (auto i : QuestionInfo["currentData"]["problem"]["limits"]["time"])
        CPHData["timeLimit"] = max(CPHData["timeLimit"].as_integer(), i.as_integer());
    for (size_t i = 0; i < QuestionInfo["currentData"]["problem"]["samples"].size(); i++)
    {
        json Temp;
        Temp["id"] = i;
        Temp["input"] = FixString(QuestionInfo["currentData"]["problem"]["samples"][i][0].as_string());
        Temp["output"] = FixString(QuestionInfo["currentData"]["problem"]["samples"][i][1].as_string());
        CPHData["tests"].push_back(json(Temp));
    }
    CPHData["local"] = false;
    CPHData["srcPath"] = CurrentDir + "Luogu/" + QuestionID + ".cpp";
    CPHData["testType"] = "single";
    CPHData["input"]["type"] = "stdin";
    CPHData["output"]["type"] = "stdout";
    CPHData["languages"]["java"]["mainClass"] = "Main";
    CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
    CPHData["batch"]["id"] = MD5Encoder.encode(QuestionID);
    CPHData["batch"]["size"] = 1;
    SetDataFromStringToFile(GetCPHFileName("Luogu", QuestionID), CPHData.dump());

    // Save data for markdown
    string OutputContent = "# " + QuestionID + " " + QuestionInfo["currentData"]["problem"]["title"].as_string() + "\n";
    if (QuestionInfo["currentData"]["problem"]["accepted"].as_bool())
        OutputContent += "***您已经通过此题！***\n"s +
                         "\n";
    else if (QuestionInfo["currentData"]["problem"]["submitted"].as_bool())
        OutputContent += "***您已经提交过此题但未通过！***\n"s +
                         "\n";
    if (QuestionInfo["currentData"]["problem"]["background"].as_string() != "")
        OutputContent += "## Background\n"s +
                         "\n" +
                         FixString(QuestionInfo["currentData"]["problem"]["background"]) + "\n" +
                         "\n";
    OutputContent += "## Description\n"s +
                     "\n" +
                     FixString(QuestionInfo["currentData"]["problem"]["description"]) + "\n" +
                     "\n" +
                     "## Input format\n" +
                     "\n" +
                     FixString(QuestionInfo["currentData"]["problem"]["inputFormat"]) + "\n" +
                     "\n" +
                     "## Output format\n" +
                     "\n" +
                     FixString(QuestionInfo["currentData"]["problem"]["outputFormat"]) + "\n" +
                     "\n" +
                     "## Samples\n" +
                     "\n";
    if (QuestionInfo["currentData"]["problem"]["samples"].size() == 0)
        OutputContent += "None\n\n";
    else
    {
        int Counter = 0;
        for (auto i : QuestionInfo["currentData"]["problem"]["samples"])
        {
            Counter++;
            OutputContent += string("Input #" + to_string(Counter) + "\n") +
                             "```\n" +
                             FixString(i[0].as_string()) + "\n" +
                             "```\n" +
                             "Output #" + to_string(Counter) + "\n" +
                             "```\n" +
                             FixString(i[1].as_string()) + "\n" +
                             "```\n";
        }
    }
    OutputContent += "\n"s +
                     "## Hint\n" +
                     "\n" +
                     FixString(QuestionInfo["currentData"]["problem"]["hint"]) +
                     "\n" +
                     "\n";
    OutputContent += "## Limits\n";
    OutputContent += "|Test case|Time limit|Memory limit|\n"s +
                     "|:---:|:---:|:---:|\n";
    for (unsigned int Counter = 0; Counter < QuestionInfo["currentData"]["problem"]["limits"]["memory"].size(); Counter++)
    {
        OutputContent += "|$" + to_string(Counter + 1) + "$|" +
                         "$" + to_string(QuestionInfo["currentData"]["problem"]["limits"]["memory"][Counter].as_integer() / 1024.0) + "MB$|" +
                         "$" + to_string(QuestionInfo["currentData"]["problem"]["limits"]["time"][Counter].as_integer() / 1000) + "s$|\n";
    }
    OutputContent += "\n"s +
                     "## Last submit code\n" +
                     "\n" +
                     "```" + LanguageMarkdownName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] + "\n" +
                     "" + FixString(QuestionInfo["currentData"]["lastCode"].as_string()) + "\n" +
                     "```\n" +
                     "\n" +
                     "## Other information\n" +
                     "\n";
    string Tags = "";
    for (auto i : QuestionInfo["currentData"]["problem"]["tags"])
        Tags += "<span style=\"display: inline-block; "s +
                "margin-right: 5px; " +
                "margin-bottom: 5px; " +
                "border-radius: 2px; " +
                "color: white; " +
                "padding: 0px 8px; " +
                "background-color: #" + ColorList[TagName[i.as_integer()].second] + "; \">" +
                TagName[i.as_integer()].first +
                "</span>";
    OutputContent += "|Item|Value|\n"s +
                     "|:---:|:---:|\n" +
                     "|Difficulty|<span style=\"font-weight: bold; color: #" + ColorList[DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].second] + "\">" + DifficultyName[QuestionInfo["currentData"]["problem"]["difficulty"].as_integer()].first + "</span>|\n" +
                     "|Label|" + Tags + "|\n" +
                     "|Submit count|$" + QuestionInfo["currentData"]["problem"]["totalSubmit"].as_string() + "$|\n" +
                     "|Pass count|$" + QuestionInfo["currentData"]["problem"]["totalAccepted"].as_string() + "$|\n" +
                     "|Pass rate|$f " + to_string(QuestionInfo["currentData"]["problem"]["totalAccepted"].as_integer() * 100.0 / QuestionInfo["currentData"]["problem"]["totalSubmit"].as_integer()) + "\\%$|\n" +
                     "|From|`" + TypeName[QuestionInfo["currentData"]["problem"]["type"].as_string()] + "`|\n" +
                     "|Last submit language|`" + LanguageName[QuestionInfo["currentData"]["lastLanguage"].as_integer()] + "`|\n" +
                     "\n";
    SetDataFromStringToFile("Luogu/" + QuestionID + ".md", OutputContent);

#ifndef TEST
    // Open the file
    if (system(string("code " + CurrentDir + "Luogu/" + QuestionID + ".md").c_str()))
        cout << "Open file \"" + CurrentDir + "Luogu/" << QuestionID << ".md\" failed, please open it manually" << endl;
    Speak("Get question detail succeed");
#endif
}
void TOOL::LUOGU::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString("Luogu/" + QuestionID + ".cpp");

    // Get the token
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + QuestionID);
    string Token = GetCSRF();
    cout << "Succeed" << endl;

    // Create the request
    json SubmitRequest;
    SubmitRequest["code"] = Code;
    SubmitRequest["enableO2"] = 1;
    SubmitRequest["lang"] = 0;

    // Create the header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, string("Content-Length: " +
                                                      to_string(SubmitRequest.dump().size()))
                                                   .c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, string("Referer: https://www.luogu.com.cn/problem/" +
                                                      QuestionID)
                                                   .c_str());
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

    // Submit the code
    cout << "Submitting... " << flush;
    GetDataToFile("https://www.luogu.com.cn/fe/api/problem/submit/" + QuestionID,
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  SubmitRequest.dump(),
                  HeaderList);

    // Get the result
    json SubmitInfo = json::parse(GetDataFromFileToString());
    if (!SubmitInfo["status"].is_null())
    {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Submit failed",
                                            SubmitInfo["status"].as_integer(),
                                            SubmitInfo["errorMessage"].as_string());
    }
    cout << "Succeed" << endl;

    // Get the record ID
    int RecordID = SubmitInfo["rid"].as_integer();

    // Get the record info and wait for the result
    json RecordInfo;
    cout << "Judging... " << flush;
    while (1)
    {
        GetDataToFile("https://www.luogu.com.cn/record/" + to_string(RecordID) + "?_contentOnly=1");
        RecordInfo = json::parse(GetDataFromFileToString());
        if (RecordInfo["currentData"]["record"]["status"].is_number() &&
            RecordInfo["currentData"]["record"]["status"].as_integer() >= 2)
            break;
        usleep(500000);
    }
    cout << "Succeed" << endl;

    // Check whether there is a compile error
    if (!RecordInfo["currentData"]["record"]["detail"]["compileResult"]["success"].as_bool())
    {
        cout << "Compile error: " << endl
             << RecordInfo["currentData"]["record"]["detail"]["compileResult"]["message"].as_string() << endl;
    }
    else
    {
        // Check whether the code is accepted
        if (RecordInfo["currentData"]["record"]["score"].as_integer() == 100)
        {
            // Delete the temporary files
            remove((CurrentDir + GetCPHFileName("Luogu", QuestionID)).c_str());
            remove(string(CurrentDir + "Luogu/" + QuestionID + ".md").c_str());
            remove(string(CurrentDir + "Luogu/" + QuestionID).c_str());
            cout << "Congratulations! You have passed this question!" << endl;
            Speak("Congratulations! You have passed this question!");
        }
        else
        {
            // Get the result
            for (auto jit : RecordInfo["currentData"]
                                      ["record"]
                                      ["detail"]
                                      ["judgeResult"]
                                      ["subtasks"])
            {
                cout << "#" << jit["id"].as_string() << endl;
                for (auto jit2 : RecordInfo["currentData"]
                                           ["record"]
                                           ["detail"]
                                           ["judgeResult"]
                                           ["subtasks"]
                                           [atoi(jit["id"].as_string().c_str())]
                                           ["testCases"])
                    cout
                        << "    #" << jit2["id"].as_integer() << " "
                        << jit2["score"].as_integer() << "pts "
                        << RecordName[jit2["status"].as_integer()].second << " "
                        << jit2["time"].as_integer() << "ms "
                        << jit2["memory"].as_integer() << "KB" << endl;
            }
            cout << RecordInfo["currentData"]["record"]["score"].as_integer() << "pts" << endl;
            Speak("You did not pass this question");
        }
    }
}
void TOOL::LUOGU::GetAnswerOrTips(string QuestionID)
{
    // Get the solution page data
    cout << "Getting solution page data... " << flush;
    GetDataToFile("https://www.luogu.com.cn/problem/solution/" + QuestionID + "?_contentOnly=1");
    json SolutionInfo = json::parse(GetDataFromFileToString());
    cout << "Succeed" << endl;
    for (auto i : SolutionInfo["currentData"]["solutions"]["result"])
    {
        string Answer = "";

        // Iterate through all the code blocks
        vector<string> Spilt = SpiltString(i["content"].as_string(), "```");
        for (size_t j = 0; j < Spilt.size(); j++)
        {
            if (j % 2)
            {
                // Get the code block
                string CurrentAnswer = Spilt[j];

                // If the code block is only one line, skip it
                size_t k = 0;
                while (k < CurrentAnswer.size() && CurrentAnswer[k] != '\n')
                    k++;
                if (k == CurrentAnswer.size())
                    continue;

                // Delete the first line which is the language names
                CurrentAnswer = CurrentAnswer.substr(k + 1, string::npos);

                // If the code block is a C++ code block and it's longer than the current answer, replace the current answer
                if (CurrentAnswer.find("main") != string::npos &&
                    CurrentAnswer.find("include") != string::npos &&
                    CurrentAnswer.find("return") != string::npos &&
                    CurrentAnswer.find(";") != string::npos &&
                    CurrentAnswer.size() > Answer.size())
                    Answer = CurrentAnswer;
            }
        }
        // Delete leading and trailing spaces and line breaks.
        Answer = FixString(Answer);
        if (Answer != "")
        {
            // Write the answer as a comment to the file.
            SetDataFromStringToFile("Luogu/" + QuestionID + ".cpp",
                                    FixString(GetDataFromFileToString("Luogu/" + QuestionID + ".cpp")) +
                                        "\n" +
                                        "\n" +
                                        "/*\n" +
                                        Answer +
                                        "\n*/" +
                                        "\n");
            break;
        }
    }
}

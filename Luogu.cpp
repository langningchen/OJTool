/**********************************************************************
OJTool: Get problem and submit code for OJ just from your CLI!
Copyright (C) 2024  langningchen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
**********************************************************************/

#include <Luogu.hpp>
#include <StringOperation.hpp>
#include <Tool.hpp>
LUOGU::LUOGU() {
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
    std::cout << "Getting luogu config... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/_lfe/config");
    json Config = json::parse(GetDataFromFileToString());
    std::cout << "Succeed" << std::endl;

    // Get the tag information of the luogu website.
    std::cout << "Getting luogu tags... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/_lfe/tags");
    json Tag = json::parse(GetDataFromFileToString());
    std::cout << "Succeed" << std::endl;

    // Get the language information of the luogu website.
    for (auto i : Config["codeLanguages"]) {
        LanguageName[i["value"].as_integer()] = i["name"].as_string();
        LanguageMarkdownName[i["value"].as_integer()] = i["hljsMode"].as_string();
    }
    LanguageName[0] = "自动识别语言";
    LanguageMarkdownName[0] = "cpp";

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
std::string LUOGU::GetCSRF() {
    // Get csrf token
    std::string Token = GetStringBetween(GetDataFromFileToString(),
                                         "<meta name=\"csrf-token\" content=\"", "\"");
    if (Token == "")
        TRIGGER_ERROR("Can not find csrf token");
    return Token;
}
void LUOGU::Login(std::string Username, std::string Password) {
    // Check if the user is logged in.
    int HTTPResponseCode = 0;
    std::cout << "Checking login... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/chat",
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

    GetDataToFile("https://www.luogu.com.cn/auth/login");
    std::string Token = GetCSRF();
    int ErrorCounter = 0;
    while (1) {
        // Get login captcha
        std::cout << "Getting login captcha... " << std::flush;
        GetDataToFile("https://www.luogu.com.cn/api/verify/captcha",
                      "",
                      "/OJTool/Captcha.jpg");
        std::cout << "Succeed" << std::endl;

        // Predict captcha
        std::string Captcha = "";
        std::cout << "Predicting captcha by AI model... " << std::flush;
        if (system("python PredictLuoguCaptcha.py > /dev/null 2>&1") == 0) {
            std::cout << "Succeed" << std::endl;
            Captcha = FixString(GetDataFromFileToString("/OJTool/Captcha.txt"));
        } else {
            std::cout << "Failed" << std::endl;
            system("code-insiders /OJTool/Captcha.jpg");
            std::cout << "Please input the captcha: ";
            std::cin >> Captcha;
        }

        // Create a json object to store the login request info
        json LoginRequest;
        LoginRequest["username"] = Username;
        LoginRequest["password"] = Password;
        LoginRequest["captcha"] = Captcha;

        // Create a header list for the curl request
        curl_slist *HeaderList = NULL;
        HeaderList = curl_slist_append(HeaderList, std::string("X-CSRF-TOKEN: " + Token).c_str());
        HeaderList = curl_slist_append(HeaderList, std::string("Content-Length: " +
                                                               std::to_string(LoginRequest.dump().size()))
                                                       .c_str());
        HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/auth/login");
        HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
        HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

        // Send the login request to the server
        std::cout << "Logging in... " << std::flush;
        GetDataToFile("https://www.luogu.com.cn/api/auth/userPassLogin",
                      "",
                      "",
                      true,
                      LoginRequest.dump(),
                      HeaderList);

        // Parse the response to a json object
        json LoginInfo = json::parse(GetDataFromFileToString());
        if (!LoginInfo["status"].is_null() && LoginInfo["data"].as_string() != "您已经登录") {
            // If the captcha is incorrect and the error counter is less than 5, try again.
            if (LoginInfo["data"].as_string() != "验证码错误" && ErrorCounter < 5) {
                TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Login failed",
                                                    LoginInfo["status"].as_integer(),
                                                    LoginInfo["data"].as_string());
            } else
                std::cout << "Failed (Captcha check failed for " << ErrorCounter + 1 << " times)" << std::endl;
        } else {
            std::cout << "Succeed" << std::endl;
            break;
        }
        ErrorCounter++;
    }
}
void LUOGU::ClockIn() {
    // Gets the clock-in page data
    std::cout << "Get clock in page data... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/");
    std::string HTMLData = GetDataFromFileToString();
    if (HTMLData.find("C3VK") != std::string::npos) {
        std::string CookieData = "www.luogu.com.cn\tTRUE\t/\tTRUE\t" + std::to_string(time(nullptr) + 60 * 60 * 24 * 7) + "\tC3VK\t" + GetStringBetween(HTMLData, "C3VK=", ";");
        GetDataToFile("https://www.luogu.com.cn/", "", "", false, "", nullptr, nullptr, "", CookieData);
        HTMLData = GetDataFromFileToString();
    }
    std::string Token = GetCSRF();
    std::cout << "Succeed" << std::endl;

    // Gets the clock-in header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, std::string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "Referer: https://www.luogu.com.cn/");
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

    // Clocks in
    std::cout << "Clocking in... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/index/ajax_punch",
                  "",
                  "",
                  true,
                  "{}",
                  HeaderList);

    // Parse the response to a json object
    json ClockInInfo = json::parse(GetDataFromFileToString());
    if (ClockInInfo["code"].as_integer() != 200) {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Clock in failed",
                                            ClockInInfo["code"].as_integer(),
                                            ClockInInfo["message"].as_string());
    }
    std::cout << "Succeed" << std::endl;
}
void LUOGU::GetProblemDetail(std::string ProblemID) {
    if (!IfFileExist("/OJTool/Luogu-" + ProblemID + ".md")) {
        // Gets the problem detail page
        std::cout << "Getting problem detail page... " << std::flush;
        GetDataToFile("https://www.luogu.com.cn/problem/" + ProblemID + "?_contentOnly=1");
        json ProblemInfo = json::parse(GetDataFromFileToString());
        if (ProblemInfo["code"].as_integer() != 200) {
            TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Get problem detail failed",
                                                ProblemInfo["code"].as_integer(),
                                                ProblemInfo["currentData"]["errorMessage"].as_string());
        }
        std::cout << "Succeed" << std::endl;

        // Save data for CPH
        MD5 MD5Encoder;
        json CPHData;
        CPHData["name"] = ProblemInfo["currentData"]["problem"]["title"].as_string();
        CPHData["group"] = "Luogu - test";
        CPHData["url"] = "https://www.luogu.com.cn/problem/" + ProblemID;
        CPHData["interactive"] = false;
        CPHData["memoryLimit"] = 0;
        for (auto i : ProblemInfo["currentData"]["problem"]["limits"]["memory"])
            CPHData["memoryLimit"] = std::max(CPHData["memoryLimit"].as_integer(), i.as_integer());
        CPHData["timeLimit"] = 0;
        for (auto i : ProblemInfo["currentData"]["problem"]["limits"]["time"])
            CPHData["timeLimit"] = std::max(CPHData["timeLimit"].as_integer(), i.as_integer());
        for (size_t i = 0; i < ProblemInfo["currentData"]["problem"]["samples"].size(); i++) {
            json Temp;
            Temp["id"] = i;
            Temp["input"] = FixString(ProblemInfo["currentData"]["problem"]["samples"][i][0].as_string());
            Temp["output"] = FixString(ProblemInfo["currentData"]["problem"]["samples"][i][1].as_string());
            CPHData["tests"].push_back(json(Temp));
        }
        CPHData["local"] = false;
        CPHData["srcPath"] = TOOL::GetSourceCodePath(ProblemID);
        CPHData["testType"] = "single";
        CPHData["input"]["type"] = "stdin";
        CPHData["output"]["type"] = "stdout";
        CPHData["languages"]["java"]["mainClass"] = "Main";
        CPHData["languages"]["java"]["taskClass"] = "GCastleDefense";
        CPHData["batch"]["id"] = MD5Encoder.encode(ProblemID);
        CPHData["batch"]["size"] = 1;
        std::cout << TOOL::GetCPHFileName(ProblemID) << " " << TOOL::GetSourceCodePath(ProblemID) << std::endl;
        SetDataFromStringToFile(TOOL::GetCPHFileName(ProblemID), CPHData.dump());

        // Save data for markdown
        std::string OutputContent = "# " + ProblemID + " " + ProblemInfo["currentData"]["problem"]["title"].as_string() + "\n";
        if (ProblemInfo["currentData"]["problem"]["accepted"].as_bool())
            OutputContent += "***您已经通过此题！***\n"s +
                             "\n";
        else if (ProblemInfo["currentData"]["problem"]["submitted"].as_bool())
            OutputContent += "***您已经提交过此题但未通过！***\n"s +
                             "\n";
        if (ProblemInfo["currentData"]["problem"]["background"].as_string() != "")
            OutputContent += "## Background\n"s +
                             "\n" +
                             FixString(ProblemInfo["currentData"]["problem"]["background"]) + "\n" +
                             "\n";
        OutputContent += "## Description\n"s +
                         "\n" +
                         FixString(ProblemInfo["currentData"]["problem"]["description"]) + "\n" +
                         "\n" +
                         "## Input format\n" +
                         "\n" +
                         FixString(ProblemInfo["currentData"]["problem"]["inputFormat"]) + "\n" +
                         "\n" +
                         "## Output format\n" +
                         "\n" +
                         FixString(ProblemInfo["currentData"]["problem"]["outputFormat"]) + "\n" +
                         "\n" +
                         "## Samples\n" +
                         "\n";
        if (ProblemInfo["currentData"]["problem"]["samples"].size() == 0)
            OutputContent += "None\n\n";
        else {
            int Counter = 0;
            for (auto i : ProblemInfo["currentData"]["problem"]["samples"]) {
                Counter++;
                OutputContent += std::string("Input #" + std::to_string(Counter) + "\n") +
                                 "```\n" +
                                 FixString(i[0].as_string()) + "\n" +
                                 "```\n" +
                                 "Output #" + std::to_string(Counter) + "\n" +
                                 "```\n" +
                                 FixString(i[1].as_string()) + "\n" +
                                 "```\n";
            }
        }
        OutputContent += "\n"s +
                         "## Hint\n" +
                         "\n" +
                         FixString(ProblemInfo["currentData"]["problem"]["hint"]) +
                         "\n" +
                         "\n";
        OutputContent += "## Limits\n";
        OutputContent += "|Test case|Time limit|Memory limit|\n"s +
                         "|:---:|:---:|:---:|\n";
        for (unsigned int Counter = 0; Counter < ProblemInfo["currentData"]["problem"]["limits"]["memory"].size(); Counter++) {
            OutputContent += "|$" + std::to_string(Counter + 1) + "$|" +
                             "$" + std::to_string(ProblemInfo["currentData"]["problem"]["limits"]["memory"][Counter].as_integer() / 1024.0) + "MB$|" +
                             "$" + std::to_string(ProblemInfo["currentData"]["problem"]["limits"]["time"][Counter].as_integer() / 1000) + "s$|\n";
        }
        OutputContent += "\n"s +
                         "## Last submit code\n" +
                         "\n" +
                         "```" + LanguageMarkdownName[ProblemInfo["currentData"]["lastLanguage"].as_integer()] + "\n" +
                         "" + FixString(ProblemInfo["currentData"]["lastCode"].as_string()) + "\n" +
                         "```\n" +
                         "\n" +
                         "## Other information\n" +
                         "\n";
        std::string Tags = "";
        for (auto i : ProblemInfo["currentData"]["problem"]["tags"])
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
                         "|Difficulty|<span style=\"font-weight: bold; color: #" + ColorList[DifficultyName[ProblemInfo["currentData"]["problem"]["difficulty"].as_integer()].second] + "\">" + DifficultyName[ProblemInfo["currentData"]["problem"]["difficulty"].as_integer()].first + "</span>|\n" +
                         "|Label|" + Tags + "|\n" +
                         "|Submit count|$" + ProblemInfo["currentData"]["problem"]["totalSubmit"].as_string() + "$|\n" +
                         "|Pass count|$" + ProblemInfo["currentData"]["problem"]["totalAccepted"].as_string() + "$|\n" +
                         "|Pass rate|$" + std::to_string(ProblemInfo["currentData"]["problem"]["totalAccepted"].as_integer() * 100.0 / ProblemInfo["currentData"]["problem"]["totalSubmit"].as_integer()) + "\\%$|\n" +
                         "|From|`" + TypeName[ProblemInfo["currentData"]["problem"]["type"].as_string()] + "`|\n" +
                         "|Last submit language|`" + LanguageName[ProblemInfo["currentData"]["lastLanguage"].as_integer()] + "`|\n" +
                         "\n";
        SetDataFromStringToFile("/OJTool/Luogu-" + ProblemID + ".md", OutputContent);
    }

    // Open the file
    if (system(std::string("code-insiders /OJTool/Luogu-" + ProblemID + ".md").c_str()))
        std::cout << "Open file \"/OJTool/Luogu-" << ProblemID << ".md\" failed, please open it manually" << std::endl;
}
void LUOGU::SubmitCode(std::string ProblemID) {
    // Get the code
    std::string Code = GetDataFromFileToString("../" + ProblemID + ".cpp");

    // Get the token
    std::cout << "Getting submit page data... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/problem/" + ProblemID);
    std::string Token = GetCSRF();
    std::cout << "Succeed" << std::endl;

    // Create the request
    json SubmitRequest;
    SubmitRequest["code"] = Code;
    SubmitRequest["enableO2"] = 1;
    SubmitRequest["lang"] = 0;

    // Create the header
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList, std::string("X-CSRF-TOKEN: " + Token).c_str());
    HeaderList = curl_slist_append(HeaderList, std::string("Content-Length: " +
                                                           std::to_string(SubmitRequest.dump().size()))
                                                   .c_str());
    HeaderList = curl_slist_append(HeaderList, "Host: www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, std::string("Referer: https://www.luogu.com.cn/problem/" +
                                                           ProblemID)
                                                   .c_str());
    HeaderList = curl_slist_append(HeaderList, "Origin: https://www.luogu.com.cn");
    HeaderList = curl_slist_append(HeaderList, "X-Requested-With: XMLHttpRequest");

    // Submit the code
    std::cout << "Submitting... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/fe/api/problem/submit/" + ProblemID,
                  "",
                  "",
                  true,
                  SubmitRequest.dump(),
                  HeaderList);

    // Get the result
    json SubmitInfo = json::parse(GetDataFromFileToString());
    if (!SubmitInfo["status"].is_null()) {
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Submit failed",
                                            SubmitInfo["status"].as_integer(),
                                            SubmitInfo["errorMessage"].as_string());
    }
    std::cout << "Succeed" << std::endl;

    // Get the record ID
    int RecordID = SubmitInfo["rid"].as_integer();

    // Get the record info and wait for the result
    json RecordInfo;
    std::cout << "Judging... " << std::flush;
    while (1) {
        GetDataToFile("https://www.luogu.com.cn/record/" + std::to_string(RecordID) + "?_contentOnly=1");
        RecordInfo = json::parse(GetDataFromFileToString());
        if (RecordInfo["currentData"]["record"]["status"].is_number() &&
            RecordInfo["currentData"]["record"]["status"].as_integer() >= 2)
            break;
        usleep(500000);
    }
    std::cout << "Succeed" << std::endl;

    // Check whether there is a compile error
    if (!RecordInfo["currentData"]["record"]["detail"]["compileResult"]["success"].as_bool()) {
        std::cout << "Compile error: " << std::endl
                  << RecordInfo["currentData"]["record"]["detail"]["compileResult"]["message"].as_string() << std::endl;
    } else {
        // Get the result
        for (auto jit : RecordInfo["currentData"]
                                  ["record"]
                                  ["detail"]
                                  ["judgeResult"]
                                  ["subtasks"]) {
            std::cout << "#" << jit["id"].as_string() << std::endl;
            for (auto jit2 : RecordInfo["currentData"]
                                       ["record"]
                                       ["detail"]
                                       ["judgeResult"]
                                       ["subtasks"]
                                       [atoi(jit["id"].as_string().c_str())]
                                       ["testCases"])
                std::cout
                    << "    #" << jit2["id"].as_integer() << " "
                    << jit2["score"].as_integer() << "pts "
                    << RecordName[jit2["status"].as_integer()].second << " "
                    << jit2["time"].as_integer() << "ms "
                    << jit2["memory"].as_integer() << "KB" << std::endl;
        }
        std::cout << RecordInfo["currentData"]["record"]["score"].as_integer() << "pts" << std::endl;
    }
}
void LUOGU::GetAnswerOrTips(std::string ProblemID) {
    // Get the solution page data
    std::cout << "Getting solution page data... " << std::flush;
    GetDataToFile("https://www.luogu.com.cn/problem/solution/" + ProblemID + "?_contentOnly=1");
    json SolutionInfo = json::parse(GetDataFromFileToString());
    std::cout << "Succeed" << std::endl;
    for (auto i : SolutionInfo["currentData"]["solutions"]["result"]) {
        std::string Answer = "";

        // Iterate through all the code blocks
        std::vector<std::string> Spilt = SpiltString(i["content"].as_string(), "```");
        for (size_t j = 0; j < Spilt.size(); j++) {
            if (j % 2) {
                // Get the code block
                std::string CurrentAnswer = Spilt[j];

                // If the code block is only one line, skip it
                size_t k = 0;
                while (k < CurrentAnswer.size() && CurrentAnswer[k] != '\n')
                    k++;
                if (k == CurrentAnswer.size())
                    continue;

                // Delete the first line which is the language names
                CurrentAnswer = CurrentAnswer.substr(k + 1, std::string::npos);

                // If the code block is a C++ code block and it's longer than the current answer, replace the current answer
                if (CurrentAnswer.find("main") != std::string::npos &&
                    CurrentAnswer.find("include") != std::string::npos &&
                    CurrentAnswer.find("return") != std::string::npos &&
                    CurrentAnswer.find(";") != std::string::npos &&
                    CurrentAnswer.size() > Answer.size())
                    Answer = CurrentAnswer;
            }
        }
        // Delete leading and trailing spaces and line breaks.
        Answer = FixString(Answer);
        if (Answer != "") {
            // Write the answer as a comment to the file.
            SetDataFromStringToFile("../" + ProblemID + ".cpp",
                                    FixString(GetDataFromFileToString("../" + ProblemID + ".cpp")) +
                                        "\n" +
                                        "/*\n" +
                                        Answer +
                                        "\n" +
                                        "*/\n");
            break;
        }
    }
}

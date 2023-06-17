#include "Tool.hpp"
string TOOL::CODEFORCES::GetCSRF()
{
    // Get csrf token
    string Token = GetStringBetween(GetDataFromFileToString(),
                                    "<input type='hidden' name='csrf_token' value='", "'/>");
    if (Token == "")
    {
        TRIGGER_ERROR("Can not find csrf token");
    }
    return Token;
}
string TOOL::CODEFORCES::OutputPre(TiXmlElement *Input)
{
    // Output pre tag
    string Output;
    Output += "```\n";
    for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
        // If the node is text, output it
        if (i->Type() == TiXmlNode::TINYXML_TEXT)
            Output += i->ToText()->Value();

        // If the node is br, output a newline
        else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
            if (string(i->Value()) == "br")
                Output += "\n";

    // If the last character is not a newline, add a newline
    if (Output[Output.size() - 1] != '\n')
        Output += "\n";
    Output += "```";
    return Output;
}
string TOOL::CODEFORCES::Output(TiXmlElement *Input, bool InLatex)
{
    string OutputValue = "";
    string Value = Input->Value();

    // If the node is pre, call OutputPre to output it
    if (Value == "pre")
    {
        OutputValue += "\n" + OutputPre(Input) + "\n";
        return OutputValue;
    }

    // If the node is img, output it as a markdown image
    else if (Value == "img")
    {
        OutputValue += " ![](" + string(Input->Attribute("src")) + ") ";
        return OutputValue;
    }

    // If the node is a ul output as a newline
    else if (Value == "ul")
        OutputValue += "\n";

    // If the node is a li output as a list
    else if (Value == "li")
        OutputValue += "- ";

    // If the node is a span, output it as it should be
    else if (Value == "span" && Input->Attribute("class") != NULL)
    {
        string Class = Input->Attribute("class");

        // If it is bold
        if (Class == "tex-font-style-bf")
            OutputValue += " **";

        // If it is italic
        else if (Class == "tex-font-style-tt")
            OutputValue += " `";

        // Else it is a latex expressions
        else
            OutputValue += " $";
        InLatex = true;
    }

    // If the node is a sup, output it as a superscript
    else if (Value == "sup")
        OutputValue += "^{";

    // If the node is a sub, output it as a subscript
    else if (Value == "sub")
        OutputValue += "_{";

    // Output the node's children
    for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
        // If the node is text, output it
        if (i->Type() == TiXmlNode::TINYXML_TEXT)
            OutputValue += i->ToText()->Value();

        // If the node is element, call Output to output it
        else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
            OutputValue += Output(i->ToElement(), InLatex);

    // End all expressions as above
    if (Value == "span" && Input->Attribute("class") != NULL)
    {
        string Class = Input->Attribute("class");
        if (Class == "tex-font-style-bf")
            OutputValue += "** ";
        else if (Class == "tex-font-style-tt")
            OutputValue += "` ";
        else
            OutputValue += "$ ";
    }
    else if (Value == "li")
        OutputValue += "\n";
    else if (Value == "ul")
        OutputValue += "\n";
    else if (Value == "sup")
        OutputValue += "}";
    else if (Value == "sub")
        OutputValue += "}";
    else if (Value == "p")
        OutputValue += "\n";
    return OutputValue;
}
string TOOL::CODEFORCES::ToNormalName(string Input)
{
    // Convert the Codeforces name to normal judge name
    if (Input == "OK")
        return "AC";
    if (Input == "FAILED")
        return "FAIL";
    if (Input == "PARTIAL")
        return "PRT";
    if (Input == "COMPILATION_ERROR")
        return "CE";
    if (Input == "RUNTIME_ERROR")
        return "RE";
    if (Input == "WRONG_ANSWER")
        return "WA";
    if (Input == "PRESENTATION_ERROR")
        return "PE";
    if (Input == "TIME_LIMIT_EXCEEDED")
        return "TLE";
    if (Input == "MEMORY_LIMIT_EXCEEDED")
        return "MLE";
    if (Input == "IDLENESS_LIMIT_EXCEEDED")
        return "ILE";
    if (Input == "SECURITY_VIOLATED")
        return "SV";
    if (Input == "CRASHED")
        return "CRS";
    if (Input == "INPUT_PREPARATION_CRASHED")
        return "IPC";
    if (Input == "CHALLENGED")
        return "CHL";
    if (Input == "SKIPPED")
        return "SKP";
    if (Input == "TESTING")
        return "TST";
    if (Input == "REJECTED")
        return "REJ";
    return Input;
}
void TOOL::CODEFORCES::Login(string Username, string Password)
{
    // Check if the user is already logged in
    int HTTPResponseCode = 0;
    cout << "Checking login... " << flush;
    GetDataToFile("https://codeforces.com/enter",
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
    HTTPResponseCode = 0;

    // Login
    cout << "Logging in... " << flush;
    GetDataToFile("https://codeforces.com/enter",
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string("csrf_token=" + GetCSRF() +
                         "&action=enter" +
                         "&ftaa=" + ftaa +
                         "&bfaa=" + bfaa +
                         "&handleOrEmail=" + URLEncode(Username.c_str()) +
                         "&password=" + URLEncode(Password.c_str()) +
                         "&_tta=176" +
                         "&remember=on")
                      .c_str(),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
    {
        // Login failed
        string LoginPageData = GetDataFromFileToString();

        // If the login failed because of the check of javascript
        if (LoginPageData.find("toNumbers"))
        {
            // Get the javascript code and write it to a file
            SetDataFromStringToFile("Run.js",
                                    // Get the javascript library
                                    GetDataFromFileToString("aes.min.js") +
                                        "\n\n\n\nfunction " +
                                        // Remove set cookie code and replace it with a variable
                                        StringReplaceAll(
                                            GetStringBetween(LoginPageData,
                                                             "<script>function ",
                                                             "document.location.href="),
                                            "document.cookie", "var Output") +
                                        "\n\nconsole.log(Output);\n");

            // Run the javascript code
            system(string("nodejs " + CurrentDir + "Run.js >> " + CurrentDir + "Output.tmp").c_str());

            // Delete the javascript code
            unlink(string(CurrentDir + "Run.js").c_str());

            // Get the output of the javascript code and try to login again
            GetDataToFile(GetStringBetween(LoginPageData, "document.location.href=\"", "\";</script>"),
                          "Header.tmp",
                          "Body.tmp",
                          true,
                          string("csrf_token=" + GetCSRF() +
                                 "&action=enter" +
                                 "&ftaa=" + ftaa +
                                 "&bfaa=" + bfaa +
                                 "&handleOrEmail=" + URLEncode(Username.c_str()) +
                                 "&password=" + URLEncode(Password.c_str()) +
                                 "&_tta=176" +
                                 "&remember=on")
                              .c_str(),
                          NULL,
                          &HTTPResponseCode,
                          FORM,
                          // Set the cookie
                          "#HttpOnly_codeforces.com\tFALSE\t/\tFALSE\t0\tRCPC\t" + GetStringBetween(GetDataFromFileToString("Output.tmp"), "RCPC=", ";"));

            // Remove the javascript output file
            unlink(string(CurrentDir + "Output.tmp").c_str());
            if (HTTPResponseCode == 200)
            {
                TRIGGER_ERROR("Login failed");
            }
        }
        else
        {
            TRIGGER_ERROR("Login failed");
        }
    }
    cout << "Succeed" << endl;
}
void TOOL::CODEFORCES::GetQuestionDetail(string QuestionID)
{
    // Get the question detail
    cout << "Getting question detail... " << flush;
    GetDataToFile("https://codeforces.com/problemset/problem/" +
                  QuestionID.substr(0, QuestionID.size() - 1) + "/" +
                  QuestionID.substr(QuestionID.size() - 1));
    cout << "Succeed" << endl;

    // Format the question detail and prase it
    cout << "Parsing question detail... " << flush;
    TiXmlDocument QuestionXmlDocument;
    QuestionXmlDocument.Parse(TidyHTMLDocument(GetDataFromFileToString()).c_str());
    if (QuestionXmlDocument.Error())
    {
        TRIGGER_ERROR("Parse question detail error: "s + QuestionXmlDocument.ErrorDesc());
    }
    ofstream OutputFileStream(string(CurrentDir + "Codeforces/" + QuestionID + ".md").c_str());
    cout << "Succeed" << endl;

    // Find the question detail
    TiXmlHandle QuestionXmlHandle = TiXmlHandle(&QuestionXmlDocument)
                                        .FirstChild("html")
                                        .FirstChild("body")
                                        .Child("div", 3)
                                        .Child("div", 4)
                                        .Child("div", 1)
                                        .Child("div", 2)
                                        .Child("div", 1)
                                        .Child("div", 0);

    // Output the question detail
    OutputFileStream << "# " << QuestionXmlHandle.Child(0).Child(0).ToElement()->GetText()
                     << endl
                     << endl
                     << "## Description" << endl
                     << Output(QuestionXmlHandle.Child(1).ToElement()) << endl
                     << endl;
    for (TiXmlNode *i = QuestionXmlHandle.Child(2).Node(); i != NULL; i = i->NextSibling())
    {
        TiXmlNode *j = i->ToElement()->FirstChild();
        OutputFileStream << "## " << j->ToElement()->FirstChild()->ToText()->Value() << endl
                         << endl;
        j = j->NextSibling();
        for (; j != NULL; j = j->NextSibling())
            OutputFileStream << Output(j->ToElement()) << endl;
        OutputFileStream << endl;
    }
    OutputFileStream << "## More details" << endl
                     << endl
                     << "|Name|Value|" << endl
                     << "|:---:|:---:|" << endl
                     << "|Time Limit|" << QuestionXmlHandle.Child(0).Child(1).Child(1).ToText()->Value() << "|" << endl
                     << "|Memory Limit|" << QuestionXmlHandle.Child(0).Child(2).Child(1).ToText()->Value() << "|" << endl
                     << "|Input|" << QuestionXmlHandle.Child(0).Child(3).Child(1).ToText()->Value() << "|" << endl
                     << "|Output|" << QuestionXmlHandle.Child(0).Child(4).Child(1).ToText()->Value() << "|" << endl
                     << endl;
    OutputFileStream.close();

#ifndef TEST
    // Open the question detail file
    if (system(string("code " + CurrentDir + "Codeforces/" + QuestionID + ".md").c_str()))
        cout << "Open file \"Codeforces/" << QuestionID << ".md\" failed, please open it manually" << endl;
    Speak("Get question detail succeed");
#endif
}
void TOOL::CODEFORCES::SubmitCode(string QuestionID)
{
    // Get the code
    string Code = GetDataFromFileToString("Codeforces/" + QuestionID + ".cpp");

    // Add a number to the code to avoid submitting the same code
    Code += "\n\n// " + to_string(time(NULL)) + "\n";

    // Get submit page data
    cout << "Getting submit page data... " << flush;
    GetDataToFile("https://codeforces.com/problemset/submit");
    cout << "Succeed" << endl;

    // Submit the code
    int HTTPResponseCode = 0;
    cout << "Submitting... " << flush;
    GetDataToFile("https://codeforces.com/problemset/submit?csrf_token=" + GetCSRF(),
                  "Header.tmp",
                  "Body.tmp",
                  true,
                  string(
                      "csrf_token=" + GetCSRF() +
                      "&ftaa=" + ftaa +
                      "&bfaa=" + bfaa +
                      "&action=submitSolutionFormSubmitted" +
                      "&contestId=" + QuestionID.substr(0, QuestionID.size() - 1) +
                      "&submittedProblemIndex=" + QuestionID.substr(QuestionID.size() - 1) +
                      "&programTypeId=50" +
                      "&source=" + URLEncode(Code) +
                      "&tabSize=4&sourceFile=&_tta=153")
                      .c_str(),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
    {
        TRIGGER_ERROR("Submit failed");
    }
    cout << "Succeed" << endl;

    // Crate a header list
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList,
                                   "Referer: https://codeforces.com/problemset/status/page/1?my=on");

    // Get the submission list page data
    cout << "Getting submission ID... " << flush;
    GetDataToFile("https://codeforces.com/problemset/status/page/1?my=on");
    cout << "Succeed" << endl;

    // Parse the submission list
    TiXmlDocument SubmitListXmlDocument;
    SubmitListXmlDocument.Parse(TidyHTMLDocument(GetDataFromFileToString()).c_str());
    if (SubmitListXmlDocument.Error())
    {
        TRIGGER_ERROR("Parse submission list error: "s + SubmitListXmlDocument.ErrorDesc());
    }

    // Get the submission ID
    string SubmitID = TiXmlHandle(&SubmitListXmlDocument)
                          .FirstChild("html")
                          .FirstChild("body")
                          .Child("div", 3)
                          .Child("div", 4)
                          .FirstChild("div")
                          .Child("div", 3)
                          .Child("div", 5)
                          .FirstChild("table")
                          .Child("tr", 1)
                          .ToElement()
                          ->Attribute("data-submission-id");
    cout << "Judging... " << flush;

    // Get the submission result
    json result;
    do
    {
        GetDataToFile("https://codeforces.com/data/submitSource",
                      "Header.tmp",
                      "Body.tmp",
                      true,
                      string("submissionId=" + SubmitID +
                             "&csrf_token=" + GetCSRF()),
                      HeaderList,
                      NULL,
                      FORM);
        result = json::parse(GetDataFromFileToString());
    } while (!result["waiting"].is_null() && result["waiting"].as_string() == "true");
    cout << "Succeed" << endl;

    // Get the submission result
    int ACNumber = 0;
    int TestNumber = atoi(result["testCount"].as_string().c_str());
    for (int i = 1; i <= TestNumber; i++)
    {
        // Save the input and output file
        SetDataFromStringToFile("Codeforces/" + QuestionID + "_" + to_string(i) + ".in",
                                result["input#" + to_string(i)].as_string());
        SetDataFromStringToFile("Codeforces/" + QuestionID + "_" + to_string(i) + ".out",
                                result["answer#" + to_string(i)].as_string());

        // Print the result
        cout << "#" << i << " "
             << ToNormalName(result["verdict#" + to_string(i)].as_string()) << " "
             << result["timeConsumed#" + to_string(i)].as_string() << "ms "
             << result["memoryConsumed#" + to_string(i)].as_string() << "B     "
             << result["checkerStdoutAndStderr#" + to_string(i)].as_string();
        if (result["rejected#" + to_string(i)].as_string() == "false")
            ACNumber++;
    }
    cout << int(ACNumber * 1.0 / TestNumber) << "pts" << endl;
}

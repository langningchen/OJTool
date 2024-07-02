#include <Tool.hpp>
#include <USACO.hpp>
void USACO::Login(std::string Username, std::string Password) {
    // Login to USACO
    std::cout << "Logging in... " << std::flush;
    GetDataToFile("https://train.usaco.org/usacogate",
                  "",
                  "",
                  true,
                  "NAME=" + URLEncode(Username) +
                      "&PASSWORD=" + URLEncode(Password) +
                      "&SUBMIT=ENTER",
                  NULL,
                  NULL,
                  "application/x-www-form-urlencoded");
    Token = GetStringBetween(GetDataFromFileToString(), "a=", "\"");
    if (Token == "")
        TRIGGER_ERROR("Login failed");
    std::cout << "Succeed" << std::endl;
    this->Username = Username;
}
void USACO::GetProblemDetail(std::string ProblemID) {
    if (!IfFileExist("/tmp/USACO-" + ProblemID + ".md")) {
        // Get the problem detail
        std::cout << "Getting problem detail... " << std::flush;
        GetDataToFile("https://train.usaco.org/usacoprob2?a=" + Token + "&S=" + ProblemID);
        std::string ProblemDetail = GetDataFromFileToString();
        ProblemDetail = "<table><td><b" + GetStringBetween(ProblemDetail, "<td><b", "</div>");
        SetDataFromStringToFile(
            "/tmp/USACO-" + ProblemID + ".md",
            ProblemDetail);
        std::cout << "Succeed" << std::endl;
    }

    // Open the problem detail file
    if (system(std::string("code-insiders /tmp/USACO-" + ProblemID + ".md").c_str()))
        std::cout << "Open file \"/tmp/USACO-" << ProblemID << ".md\" failed, please open it manually" << std::endl;
}
void USACO::SubmitCode(std::string ProblemID) {
    std::string Code = GetDataFromFileToString("USACO/" + ProblemID + ".cpp");
    Code = "/*\n"s +
           "ID: " + Username + "\n" +
           "TASK: " + ProblemID + "\n" +
           "LANG: C++14\n" +
           "*/\n" +
           Code;
    Code = FixString(Code);
    Code += "\n";
    std::string MultiPartData = "--" + MULTIPART_BOUNDARY + "\n" +
                                "Content-Disposition: form-data; name=\"filename\"; filename=\"" + ProblemID + ".cpp\"\n" +
                                "Content-Type: application/octet-stream\n" +
                                "\n" +
                                Code + "\n" +
                                "--" + MULTIPART_BOUNDARY + "\n" +
                                "Content-Disposition: form-data; name=\"a\"\n" +
                                "\n" +
                                Token + "\n" +
                                "--" + MULTIPART_BOUNDARY + "--\n";
    SetDataFromStringToFile("MultiPartData.tmp", MultiPartData);

    // Submit code
    std::cout << "Submitting code... " << std::flush;
    GetDataToFile("https://train.usaco.org/upload3",
                  "",
                  "",
                  true,
                  MultiPartData,
                  NULL,
                  NULL,
                  MULTIPART);
    std::cout << "Succeed" << std::endl;

    SetDataFromStringToFile("/tmp/" + ProblemID + ".log",
                            EraseHTMLElement(
                                GetStringBetween(
                                    GetDataFromFileToString(),
                                    "<div style=background-color:white;padding:5px;>",
                                    "</div>")));
    system(("code-insiders /tmp/" + ProblemID + ".log").c_str());
}

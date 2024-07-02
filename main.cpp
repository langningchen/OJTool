// TODO Codeforces GetProblemDetail parsing file failed

#include "Tool.hpp"
#include <errno.h>
#include <regex>

int main(int argc, char **argv) {
    CLN_TRY
    string Username;
    string Password;
    string OJ;
    string Operation;
    string ProblemID;
    for (int i = 1; i < argc; i++) {
        string Argument = argv[i];
        string NextArgument = i + 1 == argc ? "" : argv[i + 1];
        if (Argument == "-u" || Argument == "--username") {
            Username = NextArgument;
            i++;
        } else if (Argument == "-p" || Argument == "--password") {
            Password = NextArgument;
            i++;
        } else if (Argument == "-oj" || Argument == "--oj") {
            OJ = NextArgument;
            i++;
        } else if (Argument == "-o" || Argument == "--operation") {
            Operation = NextArgument;
            i++;
        } else if (Argument == "-pr" || Argument == "--problem-id") {
            ProblemID = NextArgument;
            i++;
        } else
            TRIGGER_ERROR("Unknown option \"" + Argument + "\"");
    }
    if (Username == "")
        TRIGGER_ERROR("No username provided");
    if (Password == "")
        TRIGGER_ERROR("No password provided");
    if (OJ == "")
        TRIGGER_ERROR("No OJ provided");
    if (Operation == "")
        TRIGGER_ERROR("No operation provided");
    if (Operation != "ClockIn" && ProblemID == "")
        TRIGGER_ERROR("No problem ID provided");
    TOOL Tool;
    Tool.Username = Username;
    Tool.Password = Password;
    Tool.OJ = OJ;
    Tool.Operation = Operation;
    Tool.ProblemID = ProblemID;
    Tool.Execute();
    CLN_CATCH
    return 0;
}

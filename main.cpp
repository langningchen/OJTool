// TODO Codeforces GetQuestionDetail parsing file failed

#include <regex>
#include <errno.h>
#include "Tool.hpp"

int main(int argc, char **argv)
{
    CLN_TRY
    string Username;
    string Password;
    string OJ;
    string Operation;
    string QuestionID;
    for (int i = 1; i < argc; i++)
    {
        string Argument = argv[i];
        string NextArgument = i + 1 == argc ? "" : argv[i + 1];
        if (Argument == "-u" || Argument == "--username")
        {
            Username = NextArgument;
            i++;
        }
        else if (Argument == "-p" || Argument == "--password")
        {
            Password = NextArgument;
            i++;
        }
        else if (Argument == "-oj" || Argument == "--oj")
        {
            OJ = NextArgument;
            i++;
        }
        else if (Argument == "-o" || Argument == "--operation")
        {
            Operation = NextArgument;
            i++;
        }
        else if (Argument == "-q" || Argument == "--question-id")
        {
            QuestionID = NextArgument;
            i++;
        }
        else
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
    if (Operation != "ClockIn" && QuestionID == "")
        TRIGGER_ERROR("No question id provided");
    TOOL Tool;
    Tool.Username = Username;
    Tool.Password = Password;
    Tool.OJ = OJ;
    Tool.Operation = Operation;
    Tool.QuestionID = QuestionID;
    Tool.Execute();
    CLN_CATCH
    return 0;
}

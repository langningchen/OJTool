// TODO Codeforces GetQuestionDetail parsing file failed

#include <regex>
#include <errno.h>
#include "Tool.hpp"

int main(int argc, char **argv)
{
    CLN_TRY
    GetCurrentDir();
#ifdef TEST
    TOOL("Luogu/P1000.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("Luogu/P1000.cpp", "SubmitCode");
    OutputSummary("");
    TOOL("Luogu/P1000.cpp", "GetAnswerOrTips");
    OutputSummary("");

    TOOL("Etiger/0001.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("Etiger/0001.cpp", "SubmitCode");
    OutputSummary("");
    TOOL("Etiger/0001.cpp", "GetAnswerOrTips");
    OutputSummary("");

    TOOL("UVa/00100.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("UVa/00100.cpp", "SubmitCode");
    OutputSummary("");

    TOOL("Codeforces/1A.cpp", "GetQuestionDetail");
    OutputSummary("");
    TOOL("Codeforces/1A.cpp", "SubmitCode");
    OutputSummary("");
#else
    // If the argument count is 1, the data comes from the user's input
    if (argc == 1)
        TOOL Tool;

    // If the argument count is 3, the tool is used to GetQuestionDetail/SubmitCode/GetAnswerOrTips
    else if (argc == 3)
        TOOL Tool(argv[1], argv[2]);

    // If the argument count is 4, the tool is used to login and clock in
    else if (argc == 4)
        TOOL Tool(argv[1], argv[2], argv[3]);
    else
    {
        TRIGGER_ERROR("Arguments invalid");
    }
#endif
    CLN_CATCH
    return 0;
}

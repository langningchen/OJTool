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

// TODO Codeforces GetProblemDetail parsing file failed

#include <Tool.hpp>
#include <errno.h>
#include <regex>

int main(int argc, char **argv) {
    CLN_TRY
    std::string Username;
    std::string Password;
    std::string OJ;
    std::string Operation;
    std::string ProblemID;
    for (int i = 1; i < argc; i++) {
        std::string Argument = argv[i];
        std::string NextArgument = i + 1 == argc ? "" : argv[i + 1];
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

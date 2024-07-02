#include <StringOperation.hpp>
std::string StringReplaceAll(std::string Data, std::string Before, std::string After) {
    size_t Index = 0;
    while ((Index = Data.find(Before)) != std::string::npos)
        Data.replace(Index, Before.size(), After);
    return Data;
}
std::string StringReplaceAllNoLoop(std::string Data, std::string Before, std::string After) {
    std::string Identifier = "${TEMP" + std::to_string(time(NULL)) + "}";
    Data = StringReplaceAll(Data, Before, Identifier);
    Data = StringReplaceAll(Data, Identifier, After);
    return Data;
}
std::string GetStringBetween(std::string Data, std::string Start, std::string End) {
    int StartPos = Data.find(Start);
    if (StartPos == -1)
        return "";
    StartPos += Start.size();
    int EndPos = Data.find(End, StartPos + 1);
    if (EndPos == -1)
        return "";
    return Data.substr(StartPos, EndPos - StartPos);
}
std::vector<std::string> SpiltString(std::string Input, std::string Separator) {
    Input += Separator;
    std::vector<std::string> Output;
    size_t Last = 0;
    for (size_t i = 0; i < Input.size() - Separator.size() + 1; i++)
        if (Input.substr(i, Separator.size()) == Separator) {
            Output.push_back(Input.substr(Last, i - Last));
            i += Separator.size();
            Last = i;
            i--;
        }
    return Output;
}
bool IfFileExist(std::string FileName) {
    std::ifstream InputFileStream(FileName);
    if (InputFileStream.bad() || !InputFileStream.is_open())
        return false;
    InputFileStream.close();
    return true;
}
std::string GetDataFromFileToString(std::string FileName) {
    std::string Data = "";
    FILE *FilePointer = fopen(FileName.c_str(), "r");
    if (FilePointer == NULL)
        TRIGGER_ERROR("Cannot open input file: " + FileName);
    while (!feof(FilePointer))
        Data.push_back(fgetc(FilePointer));
    fclose(FilePointer);
    while (Data.size() > 0 && (Data[Data.size() - 1] == 0x00 || Data[Data.size() - 1] == 0xFF || Data[Data.size() - 1] == -1 || Data[Data.size() - 1] == '\r' || Data[Data.size() - 1] == '\n'))
        Data.erase(Data.size() - 1);
    return Data;
}
void SetDataFromStringToFile(std::string FileName, std::string Data) {
    FILE *FilePointer = fopen(FileName.c_str(), "w");
    if (FilePointer == NULL)
        TRIGGER_ERROR("Cannot open output file: " + FileName);
    for (auto i : Data)
        fputc(i, FilePointer);
    fclose(FilePointer);
}
std::string FixString(std::string Data) {
    while (Data[0] == '\n' ||
           Data[0] == '\t' ||
           Data[0] == '\r' ||
           Data[0] == ' ')
        Data.erase(0, 1);
    while (Data[Data.size() - 1] == '\n' ||
           Data[Data.size() - 1] == '\t' ||
           Data[Data.size() - 1] == '\r' ||
           Data[Data.size() - 1] == ' ')
        Data.erase(Data.size() - 1, 1);
    return Data;
}
std::string GetCurrentDir() {
    char Buffer[256] = {0};
    getcwd(Buffer, sizeof(Buffer));
    return Buffer;
}
std::string GetRealpath(std::string Input) {
    char Buffer[4096] = {0};
    realpath(Input.c_str(), Buffer);
    return Buffer;
}
std::string GetUserHomeFolder() {
    char *HomeFolder = getenv("HOME");
    if (HomeFolder == NULL)
        TRIGGER_ERROR("Cannot get user home folder");
    return HomeFolder;
}
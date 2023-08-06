#include "Curl.hpp"
string UA = "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36 Edg/108.0.1462.76";
int GetDataToFileProgressCallback(void *_Param,
                                  curl_off_t DownloadTotal, curl_off_t DownloadNow,
                                  curl_off_t UploadTotal, curl_off_t UploadNow)
{
    if (DownloadTotal == 0)
        return 0;
    struct PROGRESS *Param = (struct PROGRESS *)_Param;
    CURL *Curl = Param->Curl;
    double Speed = 0;
    curl_easy_getinfo(Curl, CURLINFO_SPEED_DOWNLOAD, &Speed);

    // Output download progress bar
    string ProgressBarString[8] = {"▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"};
    string CurrentProgressBarString = "|";
    int ProgressBarLength = 50;
    double CurrentProgressBarLength = DownloadNow * 1.0 / DownloadTotal * ProgressBarLength;
    for (int i = 0; i < floor(CurrentProgressBarLength); i++)
        CurrentProgressBarString += ProgressBarString[7];
    CurrentProgressBarString += ProgressBarString[(int)((CurrentProgressBarLength - floor(CurrentProgressBarLength)) * 8)];
    for (int i = 0; i < ProgressBarLength - ceil(CurrentProgressBarLength); i++)
        CurrentProgressBarString += " ";
    CurrentProgressBarString += "|";

    // Output network status
    string NetworkStatus;
    if (Speed == 0)
        NetworkStatus = "▂     ";
    else if (Speed < 1024)
        NetworkStatus = "▂▃    ";
    else if (Speed < 1024 * 1024)
        NetworkStatus = "▂▃▄   ";
    else if (Speed < 1024 * 1024 * 8)
        NetworkStatus = "▂▃▄▅  ";
    else if (Speed < 1024 * 1024 * 16)
        NetworkStatus = "▂▃▄▅▆ ";
    else
        NetworkStatus = "▂▃▄▅▆▇";

    // Output download speed
    string Unit = "";
    double SpeedInUnit = 0;
    if (Speed > 1024 * 1024 * 1024)
    {
        SpeedInUnit = Speed / 1024 / 1024 / 1024;
        Unit = "GB/s";
    }
    else if (Speed > 1024 * 1024)
    {
        SpeedInUnit = Speed / 1024 / 1024;
        Unit = "MB/s";
    }
    else if (Speed > 1024)
    {
        SpeedInUnit = Speed / 1024;
        Unit = "KB/s";
    }
    else
    {
        SpeedInUnit = Speed;
        Unit = "B/s";
    }

    // Output time left
    string TimeLeft;
    int HoursLeft = -1;
    int MinutesLeft = -1;
    int SecondsLeft = -1;
    if (Speed != 0)
    {
        double TimeLeft = (DownloadTotal - DownloadNow) / Speed;
        HoursLeft = TimeLeft / 3600;
        MinutesLeft = TimeLeft / 60 - HoursLeft * 60;
        SecondsLeft = TimeLeft - HoursLeft * 3600 - MinutesLeft * 60;
    }

    string LoadingString[8] = {"⣰", "⣤", "⣆", "⡇", "⠏", "⠛", "⠹", "⢸"};
    struct timeval TimeVal;
    gettimeofday(&TimeVal, NULL);
    string CurrentLoadingString = LoadingString[(int)(TimeVal.tv_usec / 125000) % 8];

    // Output and flush
    printf("\033[2K\r%.2f%% %s%s %s %.2f%s %02d:%02d:%02d",
           DownloadNow * 1.0 / DownloadTotal * 100,
           CurrentLoadingString.c_str(),
           CurrentProgressBarString.c_str(),
           NetworkStatus.c_str(),
           SpeedInUnit,
           Unit.c_str(),
           HoursLeft,
           MinutesLeft,
           SecondsLeft);
    fflush(stdout);
    return 0;
}
void GetDataToFile(string URL,
                   string HeaderFileName,
                   string BodyFileName,
                   bool IsPost,
                   string PostData,
                   curl_slist *HeaderList,
                   int *HTTPResponseCode,
                   string PostContentType,
                   string Cookie,
                   bool ShowProgress)
{
    FILE *CookiesFilePointer = fopen("/tmp/Cookies.tmp", "a");
    fclose(CookiesFilePointer);
    FILE *HeaderFilePointer = fopen((HeaderFileName == "" ? "/tmp/Header.tmp" : HeaderFileName.c_str()), "w");
    FILE *BodyFilePointer = fopen((BodyFileName == "" ? "/tmp/Body.tmp" : BodyFileName.c_str()), "w");
    CURLcode CurlCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CurlCode != 0)
    {
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Curl init failed", CurlCode, curl_easy_strerror(CurlCode));
    }
    CURL *Curl = curl_easy_init();
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(Curl, CURLOPT_SSL_VERIFYSTATUS, false);
    curl_easy_setopt(Curl, CURLOPT_HEADERDATA, HeaderFilePointer);
    curl_easy_setopt(Curl, CURLOPT_WRITEDATA, BodyFilePointer);
    curl_easy_setopt(Curl, CURLOPT_CONNECTTIMEOUT, 10);
    if (ShowProgress)
    {
        cout << "\033[s" << endl
             << "\033[?25l";
        struct PROGRESS Param;
        Param.Curl = Curl;
        curl_easy_setopt(Curl, CURLOPT_XFERINFOFUNCTION, GetDataToFileProgressCallback);
        curl_easy_setopt(Curl, CURLOPT_XFERINFODATA, &Param);
        curl_easy_setopt(Curl, CURLOPT_NOPROGRESS, false);
    }
    if (Cookie != "")
        curl_easy_setopt(Curl, CURLOPT_COOKIELIST, Cookie.c_str());
    curl_easy_setopt(Curl, CURLOPT_COOKIEFILE, "/tmp/Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_COOKIEJAR, "/tmp/Cookies.tmp");
    curl_easy_setopt(Curl, CURLOPT_URL, URL.c_str());
    if (IsPost)
    {
        HeaderList = curl_slist_append(HeaderList, string("Content-Type: " + PostContentType).c_str());
        curl_easy_setopt(Curl, CURLOPT_POST, true);
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, PostData.c_str());
    }
    HeaderList = curl_slist_append(HeaderList, string("User-Agent: " + UA).c_str());
    curl_easy_setopt(Curl, CURLOPT_HTTPHEADER, HeaderList);
    CurlCode = curl_easy_perform(Curl);
    if (ShowProgress)
        cout << "\033[2K\033[?25h\033[u";
    if (CurlCode != 0)
    {
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        TRIGGER_ERROR_WITH_CODE_AND_MESSAGE("Request URL " + URL + " failed", CurlCode, curl_easy_strerror(CurlCode));
    }
    int TempHTTPResponseCode = 0;
    curl_easy_getinfo(Curl, CURLINFO_RESPONSE_CODE, &TempHTTPResponseCode);
    if (TempHTTPResponseCode >= 500)
    {
        fclose(BodyFilePointer);
        fclose(HeaderFilePointer);
        TRIGGER_ERROR_WITH_CODE("Request URL " + URL + " failed", TempHTTPResponseCode);
    }
    if (HTTPResponseCode != NULL)
        *HTTPResponseCode = TempHTTPResponseCode;
    curl_easy_cleanup(Curl);
    fclose(BodyFilePointer);
    fclose(HeaderFilePointer);
}
string EraseHTMLElement(string Data)
{
    int HTMLStartIndex = 0;
    for (unsigned int i = 0; i < Data.size(); i++)
        if (Data[i] == '<')
            HTMLStartIndex = i;
        else if (Data[i] == '>')
        {
            Data.erase(HTMLStartIndex, i - HTMLStartIndex + 1);
            i = HTMLStartIndex;
        }
    return Data;
}
string Base64Encode(string Input)
{
    string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    string Output;
    for (unsigned int k = 0; k < Input.size(); k += 3)
    {
        Output.push_back(base64_chars[(Input[k] & 0xfc) >> 2]);
        Output.push_back(base64_chars[((Input[k] & 0x03) << 4) + ((Input[k + 1] & 0xf0) >> 4)]);
        Output.push_back(base64_chars[((Input[k + 1] & 0x0f) << 2) + ((Input[k + 2] & 0xc0) >> 6)]);
        Output.push_back(base64_chars[Input[k + 2] & 0x3f]);
    }
    if (Input.size() % 3 == 1)
        Output.replace(Output.size() - 2, 2, "==");
    else if (Input.size() % 3 == 2)
        Output.replace(Output.size() - 1, 1, "=");
    return Output;
}
unsigned char ToHex(unsigned char x)
{
    return x > 9 ? x + 55 : x + 48;
}
unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z')
        y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z')
        y = x - 'a' + 10;
    else if (x >= '0' && x <= '9')
        y = x - '0';
    else
    {
        TRIGGER_ERROR("Invalid Hex format");
    }
    return y;
}
string URLEncode(string Input)
{
    string Output = "";
    size_t length = Input.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)Input[i]) ||
            (Input[i] == '-') ||
            (Input[i] == '_') ||
            (Input[i] == '.') ||
            (Input[i] == '~'))
            Output += Input[i];
        else if (Input[i] == ' ')
            Output += "+";
        else
        {
            Output += '%';
            Output += ToHex((unsigned char)Input[i] >> 4);
            Output += ToHex((unsigned char)Input[i] % 16);
        }
    }
    return Output;
}
string URLDecode(string Input)
{
    string Output = "";
    size_t length = Input.length();
    for (size_t i = 0; i < length; i++)
    {
        if (Input[i] == '+')
            Output += ' ';
        else if (Input[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)Input[++i]);
            unsigned char low = FromHex((unsigned char)Input[++i]);
            Output += high * 16 + low;
        }
        else
            Output += Input[i];
    }
    return Output;
}
string HTMLEncode(string Data)
{
    Data = StringReplaceAllNoLoop(Data, "&", "&amp;");
    Data = StringReplaceAll(Data, "<", "&lt;");
    Data = StringReplaceAll(Data, ">", "&gt;");
    Data = StringReplaceAll(Data, "\"", "&quot;");
    Data = StringReplaceAll(Data, "'", "&apos;");
    Data = StringReplaceAll(Data, " ", "&nbsp;");
    Data = StringReplaceAll(Data, "‘", "&lsquo;");
    Data = StringReplaceAll(Data, "’", "&rsquo;");
    return Data;
}
string HTMLDecode(string Data)
{
    Data = StringReplaceAll(Data, "&amp;", "&");
    Data = StringReplaceAll(Data, "&lt;", "<");
    Data = StringReplaceAll(Data, "&gt;", ">");
    Data = StringReplaceAll(Data, "&quot;", "\"");
    Data = StringReplaceAll(Data, "&apos;", "'");
    Data = StringReplaceAll(Data, "&nbsp;", " ");
    Data = StringReplaceAll(Data, "&lsquo;", "‘");
    Data = StringReplaceAll(Data, "&rsquo;", "’");
    return Data;
}
string FindLocation()
{
    string Header = GetDataFromFileToString("/tmp/Header.tmp");
    Header += "\n";
    string RedirectURL = GetStringBetween(Header, "Location: ", "\n");
    if (RedirectURL == "")
        RedirectURL = GetStringBetween(Header, "location: ", "\n");
    if (RedirectURL == "")
    {
        TRIGGER_ERROR("Can not find redirect location");
    }
    return FixString(RedirectURL.substr(0, RedirectURL.size()));
}

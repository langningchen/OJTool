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

#pragma once
#include <StringOperation.hpp>
#include <configor/json.hpp>
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
using namespace configor;

struct PROGRESS {
    CURL *Curl;
};

extern std::string UA;
const std::string WECHAT_UA = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 NetType/WIFI MicroMessenger/7.0.20.1781(0x6700143B) WindowsWechat(0x6307062c)";
const std::string FORM = "application/x-www-form-urlencoded";
const std::string MULTIPART_BOUNDARY = "----WebKitFormBoundarywTx7kyVBVbT6I1IG";
const std::string MULTIPART = "multipart/form-data; boundary=" + MULTIPART_BOUNDARY;
int GetDataToFileProgressCallback(void *_Param,
                                  curl_off_t DownloadTotal, curl_off_t DownloadNow,
                                  curl_off_t UploadTotal, curl_off_t UploadNow);
void GetDataToFile(std::string URL,
                   std::string HeaderFileName = "",
                   std::string BodyFileName = "",
                   bool IsPost = false,
                   std::string PostData = "",
                   curl_slist *HeaderList = NULL,
                   int *HTTPResponseCode = NULL,
                   std::string PostContentType = "application/json",
                   std::string Cookie = "",
                   bool ShowProgress = false);
std::string EraseHTMLElement(std::string Data);
std::string Base64Encode(std::string Input);
unsigned char ToHex(unsigned char x);
unsigned char FromHex(unsigned char x);
std::string URLEncode(std::string Input);
std::string URLDecode(std::string Input);
std::string HTMLEncode(std::string Data);
std::string HTMLDecode(std::string Data);
std::string FindLocation();

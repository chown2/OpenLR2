#pragma once

#include "strclass.h"
#include <string>

int CheckRivaldataNew(int rivalID);
CSTR UrlEncode(CSTR in);
[[nodiscard]] std::string LR2IR_GetWebRankingUrl(CSTR songmd5);
int OpenUrl(const char* url);

int SaveIRID(int IRID, CSTR ID);

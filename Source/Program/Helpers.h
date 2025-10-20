#pragma once

#include "UI.h"

void SetUpBasicElem(Button *elem);

void SetUpBasicElem(TextBox* elem);

void SetUpBasicElem(ClickBox* elem);


bool ArgToInt(const std::string& arg, int& intArg);

bool ArgToFloat(const std::string& arg, float& floatArg);

bool ArgToUCHar(const std::string& arg, unsigned char& ucharArg);
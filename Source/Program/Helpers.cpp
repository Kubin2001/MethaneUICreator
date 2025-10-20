#include "Helpers.h"

void SetUpBasicElem(Button* elem){
	elem->SetColor(30, 30, 30);
	elem->SetBorder(1, 0, 100, 200);
	elem->SetRenderTextType(2);
}

void SetUpBasicElem(TextBox* elem){
	elem->SetColor(30, 30, 30);
	elem->SetBorder(1, 0, 100, 200);
	elem->SetRenderTextType(2);
}

void SetUpBasicElem(ClickBox* elem) {
	elem->SetColor(30, 30, 30);
	elem->SetBorder(1, 0, 100, 200);
	elem->SetRenderTextType(2);
}

bool ArgToInt(const std::string& arg, int& intArg) {
	try {
		intArg = std::stoi(arg);
		return true;
	}
	catch (const std::exception& e) {
		intArg = -1;
		return false;
	}
}

bool ArgToFloat(const std::string& arg, float& floatArg) {
	try {
		floatArg = std::stof(arg);
		return true;
	}
	catch (const std::exception& e) {
		floatArg = -1.0f;
		return false;
	}
}

bool ArgToUCHar(const std::string& arg, unsigned char& ucharArg) {
	try {
		ucharArg = std::stoi(arg);
		return true;
	}
	catch (const std::exception& e) {
		ucharArg = -1.0f;
		return false;
	}
}
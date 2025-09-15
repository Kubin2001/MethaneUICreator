#include "EditFunctions.h"

#include <string>

bool ArgToInt(const std::string &arg, int &intArg) {
	try {
		intArg = std::stoi(arg);
		return true;
	}
	catch (const std::exception& e) {
		intArg = -1;
		return false;
	}
}

std::vector<std::function<void(Button* btn, const std::string& arg)>> EditorFunctions::functions = {};

void EditorFunctions::CreateFunctions() {

	functions.emplace_back([](Button* btn, const std::string& arg) { // name
		btn->SetName(arg);
	});

	functions.emplace_back([](Button* btn, const std::string &arg) { //x
		int val = 0;
		if (ArgToInt(arg, val)) {
			btn->GetRectangle().x = val;
		}
	});

	functions.emplace_back([](Button* btn, const std::string& arg) { //y
		int val = 0;
		if (ArgToInt(arg, val)) {
			btn->GetRectangle().y = val;
		}
	});

	functions.emplace_back([](Button* btn, const std::string& arg) { //w
		int val = 0;
		if (ArgToInt(arg, val)) {
			btn->GetRectangle().w = val;
		}
	});

	functions.emplace_back([](Button* btn, const std::string& arg) { //h
		int val = 0;
		if (ArgToInt(arg, val)) {
			btn->GetRectangle().h = val;
		}
	});
}
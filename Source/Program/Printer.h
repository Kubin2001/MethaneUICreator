#pragma once

#include <string>
#include <fstream>

#include "UI.h"

std::string ButtonToString(Button* button) {
	std::string btnOutput = "ui->CreateButton(";
	btnOutput += button->GetName();
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().x);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().y);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().w);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().h);
	//btnOutput += ',';

	btnOutput += ");";

	return btnOutput;
}

void OutputUILayout(Button* button) {
	std::ofstream file("test.txt");

	file << ButtonToString(button) + "\n";

}



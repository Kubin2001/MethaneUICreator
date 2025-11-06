#pragma once

#include <string>
#include <fstream>

#include "CreatedElement.h"

bool firstBtn = false;
bool firsttextBox = false;
bool firstclickBox = false;
bool firstpopUpBox = false;
int printerOutType = 1;

std::string AditionalToString(Button* button, UI* ui) {
	std::string addString;
	//Texture
	std::string textureName = "";
	if (button->GetTexture() != nullptr) {
		for (auto& it : TexMan::Textures) {
			if (button->GetTexture() == it.second) {
				textureName = it.first;
			}
		}
	}
	if (textureName == "") {
		return addString;
	}
	addString += ",TexMan::GetTex(\"" + textureName + "\")";
	//Texture
	//FONT
	std::string fontStr = "";
	if (button->GetFont() != nullptr) {
		for (auto& it : ui->fontManager->fonts) {
			if (it == button->GetFont()) {
				fontStr = it->GetName();
			}
		}
	}
	if (textureName == "") {
		return addString;
	}
	addString += ",ui->GetFont(\"" + fontStr + "\")";
	//FONT
	//Text
	if (button->GetText() == "") {
		return addString;
	}
	addString += ",\"" + button->GetText() + "\"";
	//Text

	//Text
	if (button->GetTextScale() == 1.0f) {
		return addString;
	}
	addString += "," + std::to_string(button->GetTextScale());
	//Text
	//textStartX
	if (button->GetTextStartX() == 0) {
		return addString;
	}
	addString += "," + std::to_string(button->GetTextStartX());
	//textStartX
	//textStartY
	if (button->GetTextStartY() == 0) {
		return addString;
	}
	addString += "," + std::to_string(button->GetTextStartY());
	//no sense to use border here 
	return addString;
}

void SelectStrings(std::string &btnOutStr, std::string& getBtnStr, Button* button, int type) {
	if (type == 1) { // Button
		if (printerOutType == 1) {
			if (firstBtn) {
				btnOutStr = "Button *btn = ui->CreateButton(";
				firstBtn = false;
			}
			else {
				btnOutStr = "btn = ui->CreateButton(";
			}
			getBtnStr = "btn = ";
		}
		else {
			btnOutStr = "ui->CreateButton(";
			getBtnStr = "\nui->GetButton(\"" + button->GetName() + "\")->";
		}
	}
	else if (type == 2) { // TextBox
		if (printerOutType == 1) {
			if (firsttextBox) {
				btnOutStr = "TextBox *tb = ui->CreateTextBox(";
				firsttextBox = false;
			}
			else {
				btnOutStr = "tb = ui->CreateTextBox(";
			}
			getBtnStr = "tb = ";
		}
		else {
			btnOutStr = "ui->CreateTextBox(";
			getBtnStr = "\nui->GetTextBox(\"" + button->GetName() + "\")->";
		}
	}
	else if (type == 3) { 
		if (printerOutType == 1) {
			if (firstclickBox) {
				btnOutStr = "ClickBox *cb = ui->CreateClickBox(";
				firstclickBox = false;
			}
			else {
				btnOutStr = "cb = ui->CreateClickBox(";
			}
			getBtnStr = "cb = ";
		}
		else {
			getBtnStr = "\nui->GetClickBox(\"" + button->GetName() + "\")->";
			btnOutStr = "ui->CreateClickBox(";
		}
	}
	else if (type == 4) { 
		if (printerOutType == 1) {
			if (firstpopUpBox) {
				btnOutStr = "PopUpBox *pub = ui->CreatePopUpBox(";
				firstpopUpBox = false;
			}
			else {
				btnOutStr = "pub = ui->CreatePopUpBox(";
			}
			getBtnStr = "pub = ";
		}
		else {
			btnOutStr = "ui->CreatePopUpBox(";
			getBtnStr = "\nui->GetPopUpBox(\"" + button->GetName() + "\")->";
		}
	}
}

std::string ButtonToString(Button* button, int type, UI *ui) {
	std::string btnOutput = "";
	std::string getBtnStr = "";

	if (type == 0) {
		return (std::string)"Wrong type";
	}
	SelectStrings(btnOutput, getBtnStr, button, type);

	btnOutput += "\"" + button->GetName() + "\"";
	btnOutput += ',';
	if (type == 4) {
		btnOutput += "120,"; // Czas pop up boxa na ile wyskakuje
	}
	btnOutput += std::to_string(button->GetRectangle().x);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().y);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().w);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().h);
	btnOutput += AditionalToString(button, ui);
	btnOutput += ");";

	if (button->textRenderType != 1) {
		btnOutput += getBtnStr + "SetRenderTextType(" + std::to_string(button->textRenderType) + ");";
	}

	if (button->zLayer != 0) {
		btnOutput += getBtnStr + "SetZLayer(" + std::to_string(button->zLayer) + ");";
	}
	if (button->buttonColor[0] != 255 || button->buttonColor[1] != 255 || button->buttonColor[2] != 255 || button->buttonColor[3] != 255) {
		btnOutput += getBtnStr + "SetColor(" + 
			std::to_string(button->buttonColor[0]) + ',' +
			std::to_string(button->buttonColor[1]) + ',' +
			std::to_string(button->buttonColor[2]) + ',' +
			std::to_string(button->buttonColor[3]) + 
			+ ");";
	}
	if (button->borderThickness != 0 || button->borderRGB[0] != 255 || button->borderRGB[1] != 255 || button->borderRGB[2] != 255) {
		btnOutput += getBtnStr + "SetBorder(" +
			std::to_string(button->borderThickness) + ',' +
			std::to_string(button->borderRGB[0]) + ',' +
			std::to_string(button->borderRGB[1]) + ',' +
			std::to_string(button->borderRGB[2]) +
			+");";
	}
	if (button->fontRGB[0] != 255 || button->fontRGB[1] != 255 || button->fontRGB[2] != 255) {
		btnOutput += getBtnStr + "SetFontColor(" +
			std::to_string(button->fontRGB[0]) + ',' +
			std::to_string(button->fontRGB[1]) + ',' +
			std::to_string(button->fontRGB[2]) +
			+");";
	}

	return btnOutput;
}

void OutputUILayout(const std::vector<CreatedElement> &elements, UI *ui, int outputType) {
	firstBtn = true;
	firsttextBox = true;
	firstclickBox = true;
	firstpopUpBox = true;
	std::ofstream file("test.txt");
	printerOutType = outputType;
	for (auto& cElem : elements) {
		file << ButtonToString(cElem.btn,cElem.type, ui) + "\n";
	}
	firstBtn = false;
	firsttextBox = false;
	firstclickBox = false;
	firstpopUpBox = false;
	std::println("Outputed");
}



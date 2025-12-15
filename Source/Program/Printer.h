#pragma once

#include <string>
#include <fstream>

#include "CreatedElement.h"

bool firstBtn = false;
bool firsttextBox = false;
bool firstclickBox = false;
bool firstpopUpBox = false;
int printerOutType = 1;

std::string AditionalToString(UIElemBase* button, UI* ui) {
	std::string addString;
	int level = 0;
	std::array<bool, 6> arr = { 0,0,0,0,0,0 }; // Shows how many are used

	//Texture
	std::string textureName = "";
	if (button->GetTexture() != nullptr) {
		for (auto& it : TexMan::Textures) {
			if (button->GetTexture() == it.second) {
				textureName = it.first;
			}
		}
	}
	if (textureName != "") {
		level = 1;
		arr[0] = 1;
	}
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
	//FONT
	if (fontStr != "") {
		level = 2;
		arr[1] = 1;
	}
	//Text
	if (button->GetText() != "") {
		level = 3;
		arr[2] = 1;
	}
	//Text
	//Text Scale
	if (button->GetTextScale() != 1.0f) {
		level = 4;
		arr[3] = 1;
	}
	//Text Scale
	//textStartX
	if (button->GetTextStartX() != 0) {
		level = 5;
		arr[4] = 1;
	}
	//textStartX
	//textStartY
	if (button->GetTextStartY() != 0) {
		level = 6;
		arr[5] = 1;
	}
	//no sense to use border here 

	if (level == 0) {
		return addString;
	}
	if (level >= 1) {
		if (arr[0]) {
			addString += ",TexMan::GetTex(\"" + textureName + "\")";
		}
		else {
			addString += ",nullptr";
		}
	}
	if (level >= 2) {
		if (arr[1]) {
			addString += ",ui->GetFont(\"" + fontStr + "\")";
		}
		else {
			addString += ",nullptr";
		}
	}
	if (level >= 3) {
		if (arr[2]) {
			addString += ",\"" + button->GetText() + "\"";
		}
		else {
			addString += ",\"\"";
		}
	}
	if (level >= 4) {
		if (arr[3]) {
			addString += "," + std::to_string(button->GetTextScale());
		}
		else {
			addString += ",1.0f";
		}

	}
	if (level >= 5) {
		if (arr[4]) {
			addString += "," + std::to_string(button->GetTextStartX());
		}
		else {
			addString += ",0";
		}
		
	}
	if (level >= 6) {
		if (arr[5]) {
			addString += "," + std::to_string(button->GetTextStartY());
		}
		else {
			addString += ",0";
		}
	}
	return addString;
}

void SelectStrings(std::string &btnOutStr, std::string& getBtnStr, UIElemBase* button, int type) {
	if (type == 1) { // Button
		if (printerOutType == 1) {
			if (firstBtn) {
				btnOutStr = "Button *btn = ui->CreateButton(";
				firstBtn = false;
			}
			else {
				btnOutStr = "btn = ui->CreateButton(";
			}
			getBtnStr = "btn->";
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
			getBtnStr = "tb->";
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
			getBtnStr = "cb->";
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
			getBtnStr = "pub->";
		}
		else {
			btnOutStr = "ui->CreatePopUpBox(";
			getBtnStr = "\nui->GetPopUpBox(\"" + button->GetName() + "\")->";
		}
	}
}

std::string ButtonToString(UIElemBase* button, int type, UI *ui, int renderType) {
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
	if (renderType == 2) {
		btnOutput += getBtnStr + "SetRenderType(" + std::to_string(renderType) + ");";
	}
	if (button->buttonColor.R != 255 || button->buttonColor.G != 255 || button->buttonColor.B != 255 || button->buttonColor.A != 255) {
		btnOutput += getBtnStr + "SetColor(" + 
			std::to_string(button->buttonColor.R) + ',' +
			std::to_string(button->buttonColor.G) + ',' +
			std::to_string(button->buttonColor.B) + ',' +
			std::to_string(button->buttonColor.A) + 
			+ ");";
	}
	if (button->borderThickness != 0 || button->borderRGB.R != 255 || button->borderRGB.G != 255 || button->borderRGB.B != 255) {
		btnOutput += getBtnStr + "SetBorder(" +
			std::to_string(button->borderThickness) + ',' +
			std::to_string(button->borderRGB.R) + ',' +
			std::to_string(button->borderRGB.G) + ',' +
			std::to_string(button->borderRGB.B) +
			+");";
	}
	if (button->fontRGB.R != 255 || button->fontRGB.G != 255 || button->fontRGB.B != 255) {
		btnOutput += getBtnStr + "SetFontColor(" +
			std::to_string(button->fontRGB.R) + ',' +
			std::to_string(button->fontRGB.G) + ',' +
			std::to_string(button->fontRGB.B) +
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
		file << ButtonToString(cElem.btn,cElem.type, ui,cElem.renderType) + "\n";
	}
	firstBtn = false;
	firsttextBox = false;
	firstclickBox = false;
	firstpopUpBox = false;
	std::println("Outputed");
}



#pragma once

#include <string>
#include <fstream>

#include "UI.h"

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
	//textStartY
	//borderThickness
	//if (button->GetBorderThickness() == 0) {
	//	return addString;
	//}
	//addString += "," + std::to_string(button->GetBorderThickness());
	//borderThickness
	return addString;
}

std::string ButtonToString(Button* button, UI *ui) {
	std::string btnOutput = "ui->CreateButton(";
	btnOutput += "\"" + button->GetName() + "\"";
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().x);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().y);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().w);
	btnOutput += ',';
	btnOutput += std::to_string(button->GetRectangle().h);
	btnOutput += AditionalToString(button, ui);
	btnOutput += ");";

	std::string getBtnStr = "\nui->GetButton(\"" + button->GetName() + "\")->";
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

void OutputUILayout(Button* button, UI *ui) {
	std::ofstream file("test.txt");

	file << ButtonToString(button, ui) + "\n";
	std::println("Test");
}



#pragma once

#include "UI.h"

struct CreatedElement {
	Button* btn = nullptr;
	int type = 0; // 0 empty /1 btn /2 tb /3 cb/ 4 popupBox
	int renderType = 1; // 1 bazowy 2 okr¹g³y
	bool xAxisBlock = false;
	bool yAxisBlock = false;

	CreatedElement() = default;

	CreatedElement(Button* button, const int type) {
		this->btn = button;
		this->type = type;
		this->xAxisBlock = false;
		this->yAxisBlock = false;

	}
};

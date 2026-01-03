#pragma once

#include "UI.h"

struct CreatedElement {
	UIElemBase* btn = nullptr;
	int renderType = 1; // 1 bazowy 2 okr¹g³y
	bool xAxisBlock = false;
	bool yAxisBlock = false;
	bool widthOrientation = false;
	bool heightOrientation = false;

	CreatedElement() = default;

	CreatedElement(UIElemBase* button) {
		this->btn = button;
		this->xAxisBlock = false;
		this->yAxisBlock = false;
		this->widthOrientation = false;
		this->heightOrientation = false;
	}
};

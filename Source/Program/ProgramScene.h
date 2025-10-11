#pragma once

#include "SceneManager.h"

struct CreatedElement {
	Button* btn = nullptr;
	int type = 0; // 0 empty /1 btn /2 tb /3 cb/ 4 popupBox

	CreatedElement() = default;

	CreatedElement(Button* button, const int type) {
		this->btn = button;
		this->type = type;
	}
};


class ProgramScene :public Scene{
	private:
		ClickBox* runButton = nullptr;
		Button* rightPanel = nullptr;
		ClickBoxList btnCreateList;
		std::vector<CreatedElement> elements;
		CreatedElement selectedButton;
		Button* editedButton = nullptr;
		int index = 0;
		int panelType = 0; //0 no panel 1 Creation Panel 2 Edit Panel  3 run panel

		std::vector<Button*> editBtnRef;
		std::vector<TextBox*> editTextRef;
		std::vector<ClickBox*> editClickRef;

		std::vector<Button*> runBtnRef;
		std::vector<TextBox*> runTextRef;
		std::vector<ClickBox*> runClickRef;
		std::vector<PopUpBox*> runPopUpRef;

		void ShowPanel();

		void HidePanel();

		void CreateEditBox(const std::string& name, int& y, const std::string& text, const std::string& arg1 = "");

		void CreateTripleEditBox(const std::string& name, int& y, const std::string& text,
			const std::string& arg1 = "", const std::string& arg2 = "", const std::string& arg3 = "");

		void CreateQuadEditBox(const std::string& name, int& y, const std::string& text,
			const std::string& arg1 = "", const std::string& arg2 = "", const std::string& arg3 = "", const std::string& arg4 = "");

		void ShowEditPanel(Button* button);

		void HideEditPanel(Button* button);

		void ShowRunPanel();

		void HideRunPanel();

		void CreateNewElem(const int type);

		void MoveSelected();

	public:
		void Init(MT::Renderer* renderer = nullptr, UI* ui = nullptr);

		void LogicUpdate();

		void FrameUpdate();

		void Input(SDL_Event& event);

		void Render();

		void Clear();
};
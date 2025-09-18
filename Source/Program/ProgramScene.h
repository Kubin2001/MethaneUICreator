#pragma once

#include "SceneManager.h"


class ProgramScene :public Scene{
	private:
		Button* rightPanel = nullptr;
		ClickBoxList btnCreateList;
		std::vector<Button*> elements;
		Button* selectedButton = nullptr;
		Button* editedButton = nullptr;
		int index = 0;
		int panelType = 0; //0 no panel 1 Creation Panel 2 Edit Panel  

		std::vector<Button*> editBtnRef;
		std::vector<TextBox*> editTextRef;
		std::vector<ClickBox*> editClickRef;

		void ShowPanel();

		void HidePanel();

		void CreateEditBox(const std::string& name, int& y, const std::string& text);

		void CreateTripleEditBox(const std::string& name, int& y, const std::string& text);

		void CreateQuadEditBox(const std::string& name, int& y, const std::string& text);

		void ShowEditPanel(Button* button);

		void HideEditPanel(Button* button);

		void CreateNewElem();

		void MoveSelected();

	public:
		void Init(MT::Renderer* renderer = nullptr, UI* ui = nullptr);

		void LogicUpdate();

		void FrameUpdate();

		void Input(SDL_Event& event);

		void Render();

		void Clear();
};
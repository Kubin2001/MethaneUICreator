#pragma once

#include "SceneManager.h"
#include "CreatedElement.h"



class ProgramScene :public Scene{
	private:
		ClickBox* runButton = nullptr;
		Button* rightPanel = nullptr;
		UIList<ClickBox> btnCreateList;
		std::vector<CreatedElement> elements;
		CreatedElement* selectedButton;
		CreatedElement* editedButton = nullptr;
		int index = 0;
		int panelType = 0; //0 no panel 1 Creation Panel 2 Edit Panel  3 run panel
		int editPanelState = 0;// 0 normal 1 smaller options

		UISection editPanelTwo;
		std::vector<TextBox*> editTextRef;
		std::vector<ClickBox*> editClickRef;

		std::vector<Button*> runBtnRef;
		std::vector<TextBox*> runTextRef;
		std::vector<ClickBox*> runClickRef;
		std::vector<PopUpBox*> runPopUpRef;

		bool outOptions = false;
		int outputType = 1; // 1 Przez referencje 2 Przez UI getbutton("name) 

		void ShowPanel();

		void HidePanel();

		void CreateEditBox(const std::string& name, int& y, const std::string& text, const std::string& arg1 = "");

		void CreateTripleEditBox(const std::string& name, int& y, const std::string& text,
			const std::string& arg1 = "", const std::string& arg2 = "", const std::string& arg3 = "");

		void CreateQuadEditBox(const std::string& name, int& y, const std::string& text,
			const std::string& arg1 = "", const std::string& arg2 = "", const std::string& arg3 = "", const std::string& arg4 = "");

		void ShowEditPanel(CreatedElement* button);

		void HideEditPanel(CreatedElement* button);

		void ShowRunPanel();

		void HideRunPanel();

		void CreateNewElem(const int type);

		void MoveSelected();

		void CreateOutputSubPanel();

		void HideOutputSubPanel();

	public:
		void Init(MT::Renderer* renderer = nullptr, UI* ui = nullptr);

		void LogicUpdate();

		void FrameUpdate();

		void Input(SDL_Event& event);

		void Render();

		void Clear();
};
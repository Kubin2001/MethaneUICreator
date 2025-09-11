#pragma once

#include "SceneManager.h"


class ProgramScene :public Scene{
	private:
		Button* rightPanel = nullptr;
		ClickBoxList btnCreateList;
		std::vector<Button*> elements;
		Button* selectedButton = nullptr;
		int index = 0;

		void ShowPanel();

		void HidePanel();

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
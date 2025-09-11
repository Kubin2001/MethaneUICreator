#include "ProgramScene.h"


void ProgramScene::Init(MT::Renderer* renderer, UI* ui){
	this->renderer = renderer;
	this->ui = ui;

	rightPanel = ui->CreateButton("Right Panel", Global::windowWidth - 300,0,300,Global::windowHeight);
	rightPanel->SetColor(30, 30, 30);
	rightPanel->SetBorder(2, 0, 100, 200);
	rightPanel->Hide();
}

void ProgramScene::LogicUpdate(){}

void ProgramScene::FrameUpdate(){
	if (btnCreateList.Main() != nullptr) {
		if (btnCreateList.Main()->ConsumeStatus()) {
			if (btnCreateList.IsExpanded()) {
				btnCreateList.Hide();
			
			}	
			else {
				btnCreateList.Expand();
			}
		}
	}
	if (btnCreateList.IsExpanded()) {
		if (btnCreateList.Get(0)->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
		if (btnCreateList.Get(1)->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
		if (btnCreateList.Get(2)->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
		if (btnCreateList.Get(3)->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
	}

	MoveSelected();
}

void ProgramScene::Input(SDL_Event& event){
	if (event.type == SDL_KEYUP) {
		if (event.button.button == SDL_SCANCODE_M) {
			if (rightPanel->IsHidden()) {
				ShowPanel();
			}
			else {
				HidePanel();
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (selectedButton != nullptr) {
				elements.emplace_back(selectedButton);
				selectedButton = nullptr;
			}
		}
	}
}

void ProgramScene::Render(){}

void ProgramScene::Clear(){
	ui->ClearAll();
}


void ProgramScene::ShowPanel() {
	rightPanel->Show();
	Point center = rightPanel->GetRectangle().GetCenter();
	int w = 100;
	int h = 50;
	int x = center.x - (w / 2);
	int y = center.y - (h / 2);
	ClickBox *cb = ui->CreateClickBox("BtnCreatorMain", x, y, w ,h, nullptr, ui->GetFont("arial20px"),"New");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 0, 100, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120);
	std::vector<std::string> names = { "list1","list2", "list3", "list4"};
	std::string texts[] = {"Button","Click Box", "Massage Box", "Pop Up Box"};
	btnCreateList.Innit(ui, cb, names, w, h, 30, 30, 30, texts, 1);

	for (auto& it : btnCreateList.GetAll()) {
		it->SetColor(30, 30, 30);
		it->SetBorder(1, 0, 100, 200);
		it->SetRenderTextType(2);
		it->SetHoverFilter(true, 255, 255, 255, 120);
	}
}

void ProgramScene::HidePanel() {
	rightPanel->Hide();
	btnCreateList.Clear();
}

void ProgramScene::CreateNewElem() {
	if (selectedButton != nullptr) { return; }
	index++;
	int x, y;
	SDL_GetMouseState(&x, &y);
	selectedButton = ui->CreateButton("btn" + std::to_string(index), x - 50, y - 50, 100, 100);
	HidePanel();
}

void ProgramScene::MoveSelected() {
	if (selectedButton == nullptr) { return; }
	int x, y;
	SDL_GetMouseState(&x, &y);
	selectedButton->GetRectangle().x = x - (selectedButton->GetRectangle().w / 2);
	selectedButton->GetRectangle().y = y - (selectedButton->GetRectangle().h / 2);
}
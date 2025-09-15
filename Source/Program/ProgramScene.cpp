#include "ProgramScene.h"

#include <print>

#include "Helpers.h"
#include "EditFunctions.h"

void ProgramScene::Init(MT::Renderer* renderer, UI* ui){
	this->renderer = renderer;
	this->ui = ui;
	
	EditorFunctions::CreateFunctions();

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
		if (btnCreateList[0]->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
		if (btnCreateList[1]->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
		if (btnCreateList[2]->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
		if (btnCreateList[3]->ConsumeStatus()) {
			CreateNewElem();
			return;
		}
	}

	for (size_t i = 0; i < editClickRef.size(); i++) {
		if (editClickRef[i]->ConsumeStatus()) {
			if (EditorFunctions::functions.size() > i) {
				EditorFunctions::functions[i](editedButton,editTextRef[i]->GetText());
			}
			break;
		}
	}

	MoveSelected();
}

void ProgramScene::Input(SDL_Event& event){
	if (event.type == SDL_KEYUP) {
		if (event.button.button == SDL_SCANCODE_M) {
			if (panelType != 1) {
				ShowPanel();
			}
			else {
				HidePanel();
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		MT::Rect mouseRect{ x,y,1,1 };
		if (event.button.button == SDL_BUTTON_LEFT) {;
			if (selectedButton != nullptr) {
				elements.emplace_back(selectedButton);
				selectedButton = nullptr;
			}
			else {
				for (auto& it : elements) {
					if (it->GetRectangle().IsColliding(mouseRect)) {
						selectedButton = it;
						break;
					}
				}
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			for (auto& it : elements) {
				if (it->GetRectangle().IsColliding(mouseRect)) {
					ShowEditPanel(it);
				}
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
	btnCreateList.Innit(ui, cb, w, h, 30, 30, 30, { "Button","Click Box", "Massage Box", "Pop Up Box" }, 1);

	for (auto& it : btnCreateList.GetAll()) {
		it->SetColor(30, 30, 30);
		it->SetBorder(1, 0, 100, 200);
		it->SetRenderTextType(2);
		it->SetHoverFilter(true, 255, 255, 255, 120);
	}
	panelType = 1;
}

void ProgramScene::HidePanel() {
	rightPanel->Hide();
	btnCreateList.Clear();
	panelType = 0;
}

void ProgramScene::ShowEditPanel(Button *button) {
	if (panelType == 2) {
		HideEditPanel(button);
		return;
	}
	rightPanel->Show();
	Button* btn = nullptr;
	TextBox* tb = nullptr;
	ClickBox* cb = nullptr;
	int x = rightPanel->GetRectangle().x + 20;
	int y = rightPanel->GetRectangle().y + 20;
	int jump = 40;

	std::vector<std::string> names = { "KeyEditName","KeyEditX","KeyEditY","KeyEditW",
	"KeyEditH","KeyEditTexture"};

	std::vector<std::string> texts = {"Key: ","X: ","Y: " ,"W: " ,"H: " ,"Texture: " };

	for (size_t i = 0; i < names.size(); i++) {
		cb = ui->CreateClickBox(names[i], x, y, 80, 30, nullptr, ui->GetFont("arial12px"), texts[i]);
		SetUpBasicElem(cb);
		editClickRef.emplace_back(cb);
		cb->SetHoverFilter(true,255,255,255,120);

		tb = ui->CreateTextBox(names[i] + "tb", x + 100, y, 80, 30, nullptr, ui->GetFont("arial12px"));
		SetUpBasicElem(tb);
		editTextRef.emplace_back(tb);
		y += jump;
	}
	editedButton = button;
	panelType = 2;
}

void ProgramScene::HideEditPanel(Button* button) {
	rightPanel->Hide();
	for (auto& btn : editBtnRef) {
		ui->DeleteButton(btn->GetName());
	}
	for (auto& btn : editTextRef) {
		ui->DeleteTextBox(btn->GetName());
	}
	for (auto& btn : editClickRef) {
		ui->DeleteClickBox(btn->GetName());
	}
	editBtnRef.clear();
	editTextRef.clear();
	editClickRef.clear();
	editedButton = nullptr;
	panelType = 0;
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
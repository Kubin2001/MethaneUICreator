#include "ProgramScene.h"

#include <print>

#include "Helpers.h"

bool ArgToInt(const std::string& arg, int& intArg) {
	try {
		intArg = std::stoi(arg);
		return true;
	}
	catch (const std::exception& e) {
		intArg = -1;
		return false;
	}
}

bool ArgToFloat(const std::string& arg, float& floatArg) {
	try {
		floatArg = std::stof(arg);
		return true;
	}
	catch (const std::exception& e) {
		floatArg = -1.0f;
		return false;
	}
}

bool ArgToUCHar(const std::string& arg, unsigned char& ucharArg) {
	try {
		ucharArg = std::stoi(arg);
		return true;
	}
	catch (const std::exception& e) {
		ucharArg = -1.0f;
		return false;
	}
}

void ProgramScene::Init(MT::Renderer* renderer, UI* ui){
	this->renderer = renderer;
	this->ui = ui;
	
	//EditorFunctions::CreateFunctions();

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
	if (ui->GetClickBox("KeyEditName") != nullptr) {
		if (ui->GetClickBox("KeyEditName")->ConsumeStatus()) {
			editedButton->SetName(ui->GetTextBox("KeyEditNametb")->GetText());
		}
		else if (ui->GetClickBox("KeyEditX")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditXtb")->GetText(), val)) {
				editedButton->GetRectangle().x = val;
			}
		}
		else if (ui->GetClickBox("KeyEditY")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditYtb")->GetText(), val)) {
				editedButton->GetRectangle().y = val;
			}
		}
		else if (ui->GetClickBox("KeyEditW")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditWtb")->GetText(), val)) {
				editedButton->GetRectangle().w = val;
			}
		}
		else if (ui->GetClickBox("KeyEditH")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditHtb")->GetText(), val)) {
				editedButton->GetRectangle().h = val;
			}
		}
		else if (ui->GetClickBox("KeyEditTexture")->ConsumeStatus()) {
			std::string& textureName = ui->GetTextBox("KeyEditTexturetb")->GetText();
			if (TexMan::GetTex(textureName) != nullptr) {
				editedButton->SetTexture(TexMan::GetTex(textureName));
			}
		}
		else if (ui->GetClickBox("KeyEditFont")->ConsumeStatus()) {
			std::string& textureName = ui->GetTextBox("KeyEditFonttb")->GetText();
			if (ui->GetFont(textureName) != nullptr) {
				editedButton->SetFont(ui->GetFont(textureName));
			}
		}
		else if (ui->GetClickBox("KeyEditText")->ConsumeStatus()) {
			editedButton->SetText(ui->GetTextBox("KeyEditTexttb")->GetText());
		}
		else if (ui->GetClickBox("KeyEditTextSize")->ConsumeStatus()) {
			float val = 0.0f;
			if (ArgToFloat(ui->GetTextBox("KeyEditTextSizetb")->GetText(), val)) {
				editedButton->SetTextScale(val);
			}
		}
		else if (ui->GetClickBox("KeyEditTextX")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditTextXtb")->GetText(), val)) {
				editedButton->SetTextStartX(val);
			}
		}
		else if (ui->GetClickBox("KeyEditTextY")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditTextYtb")->GetText(), val)) {
				editedButton->SetTextStartY(val);
			}
		}
		else if (ui->GetClickBox("KeyTextRender")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyTextRendertb")->GetText(), val)) {
				editedButton->SetRenderTextType(val);
			}
		}
		else if (ui->GetClickBox("KeyColor")->ConsumeStatus()) {
			std::string& R = ui->GetTextBox("KeyColor1")->GetText();
			std::string& G = ui->GetTextBox("KeyColor2")->GetText();
			std::string& B = ui->GetTextBox("KeyColor3")->GetText();
			std::string& A = ui->GetTextBox("KeyColor4")->GetText();
			unsigned char argR = 0;
			unsigned char argG = 0;
			unsigned char argB = 0;
			unsigned char argA = 0;
			if (ArgToUCHar(R, argR) && ArgToUCHar(G, argG)&& ArgToUCHar(B, argB)&& ArgToUCHar(A, argA)) {
				editedButton->SetColor(argR, argG, argB, argA);
			}
		}
		else if (ui->GetClickBox("KeyBorder")->ConsumeStatus()) {
			std::string& W = ui->GetTextBox("KeyBorder1")->GetText();
			std::string& R = ui->GetTextBox("KeyBorder2")->GetText();
			std::string& G = ui->GetTextBox("KeyBorder3")->GetText();
			std::string& B = ui->GetTextBox("KeyBorder4")->GetText();
			int argW = 0;
			unsigned char argR = 0;
			unsigned char argG = 0;
			unsigned char argB = 0;
			if (ArgToInt(W, argW) && ArgToUCHar(R, argR) && ArgToUCHar(G, argG) && ArgToUCHar(B, argB)) {
				editedButton->SetBorder(argW, argR, argG, argB);
			}
		}
		else if (ui->GetClickBox("KeyFontColor")->ConsumeStatus()) {
			std::string& R = ui->GetTextBox("KeyFontColor1")->GetText();
			std::string& G = ui->GetTextBox("KeyFontColor2")->GetText();
			std::string& B = ui->GetTextBox("KeyFontColor3")->GetText();
			unsigned char argR = 0;
			unsigned char argG = 0;
			unsigned char argB = 0;
			if (ArgToUCHar(R, argR) && ArgToUCHar(G, argG) && ArgToUCHar(B, argB)) {
				editedButton->SetFontColor(argR, argG, argB);
			}
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

void ProgramScene::CreateEditBox(const std::string &name, int &y, const std::string &text, const std::string &arg1) {
	ClickBox *cb = ui->CreateClickBox(name, rightPanel->GetRectangle().x + 20
		, y, 80, 30, nullptr, ui->GetFont("arial12px"), text);
	SetUpBasicElem(cb);
	editClickRef.emplace_back(cb);
	cb->SetHoverFilter(true, 255, 255, 255, 120);

	TextBox* tb = ui->CreateTextBox(name + "tb",
		rightPanel->GetRectangle().x + 120, y, 80, 30, nullptr, ui->GetFont("arial12px"),arg1);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);
	y += 40;
}

void ProgramScene::CreateTripleEditBox(const std::string& name, int& y, const std::string& text) {
	ClickBox* cb = ui->CreateClickBox(name, rightPanel->GetRectangle().x + 95
		, y, 80, 30, nullptr, ui->GetFont("arial12px"), text);
	SetUpBasicElem(cb);
	editClickRef.emplace_back(cb);
	cb->SetHoverFilter(true, 255, 255, 255, 120);

	y += 40;
	TextBox* tb = ui->CreateTextBox(name + "1",
		rightPanel->GetRectangle().x + 20, y, 60, 30, nullptr, ui->GetFont("arial12px"));
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	tb = ui->CreateTextBox(name + "2",
		rightPanel->GetRectangle().x + 90, y, 60, 30, nullptr, ui->GetFont("arial12px"));
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	tb = ui->CreateTextBox(name + "3",
		rightPanel->GetRectangle().x + 160, y, 60, 30, nullptr, ui->GetFont("arial12px"));
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);
	y += 40;
}


void ProgramScene::CreateQuadEditBox(const std::string& name, int& y, const std::string& text,
	const std::string &arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4) {
	ClickBox* cb = ui->CreateClickBox(name, rightPanel->GetRectangle().x + 95
		, y, 80, 30, nullptr, ui->GetFont("arial12px"), text);
	SetUpBasicElem(cb);
	editClickRef.emplace_back(cb);
	cb->SetHoverFilter(true, 255, 255, 255, 120);

	y += 40;
	TextBox* tb = ui->CreateTextBox(name + "1",
		rightPanel->GetRectangle().x + 20, y, 50, 30, nullptr, ui->GetFont("arial12px"), arg1);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	 tb = ui->CreateTextBox(name + "2",
		rightPanel->GetRectangle().x + 80, y, 50, 30, nullptr, ui->GetFont("arial12px"), arg2);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	tb = ui->CreateTextBox(name + "3",
		rightPanel->GetRectangle().x + 140, y, 50, 30, nullptr, ui->GetFont("arial12px"), arg3);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	tb = ui->CreateTextBox(name + "4",
		rightPanel->GetRectangle().x + 200, y, 50, 30, nullptr, ui->GetFont("arial12px"),arg4);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);
	y += 40;
}

void ProgramScene::ShowEditPanel(Button *button) {
	if (panelType == 2) {
		HideEditPanel(button);
		return;
	}
	editedButton = button;
	rightPanel->Show();

	int y = rightPanel->GetRectangle().y + 20;

	CreateEditBox("KeyEditName", y, "Key: ",editedButton->GetName());
	CreateEditBox("KeyEditX", y, "X: ",std::to_string(editedButton->GetRectangle().x));
	CreateEditBox("KeyEditY", y, "Y: ", std::to_string(editedButton->GetRectangle().y));
	CreateEditBox("KeyEditW", y, "W: ", std::to_string(editedButton->GetRectangle().w));
	CreateEditBox("KeyEditH", y, "H: ", std::to_string(editedButton->GetRectangle().h));
	CreateEditBox("KeyEditTexture", y, "Texture: ");
	CreateEditBox("KeyEditFont", y, "Font: ");
	CreateEditBox("KeyEditText", y, "Text: ",editedButton->GetText());
	CreateEditBox("KeyEditTextSize", y, "TextSize: ",std::to_string(editedButton->GetTextScale()));
	CreateEditBox("KeyEditTextX", y, "Text X: ", std::to_string(editedButton->GetTextStartX()));
	CreateEditBox("KeyEditTextY", y, "Text Y: ", std::to_string(editedButton->GetTextStartY()));
	CreateEditBox("KeyTextRender", y, "Text Render: ", std::to_string(editedButton->textRenderType));

	CreateQuadEditBox("KeyColor", y, "Color", std::to_string(editedButton->buttonColor[0]),
		std::to_string(editedButton->buttonColor[1]), std::to_string(editedButton->buttonColor[2]), 
		std::to_string(editedButton->buttonColor[3]));
	CreateQuadEditBox("KeyBorder", y, "Border");
	CreateTripleEditBox("KeyFontColor", y, "Font Color");

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
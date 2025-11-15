#include "ProgramScene.h"

#include <print>

#include "Helpers.h"
#include "Printer.h"

void CreateErrorBox(UI* ui, const std::string& text) {
	int random = RandInt(0, 2000);
	PopUpBox* pb = ui->CreatePopUpBox("PBName" + std::to_string(random), 240, 10, 10, Global::windowWidth / 3, 100,
		nullptr, ui->GetFont("arial12px"), text);

	pb->SetColor(200, 200, 200);
	pb->SetFontColor(255, 0, 0);
	pb->SetRenderTextType(2);
}

void ProgramScene::Init(MT::Renderer* renderer, UI* ui){
	this->renderer = renderer;
	this->ui = ui;
	
	//EditorFunctions::CreateFunctions();

	rightPanel = ui->CreateButton("Right Panel", Global::windowWidth - 300,0,300,Global::windowHeight);
	rightPanel->SetColor(30, 30, 30);
	rightPanel->SetBorder(2, 0, 100, 200);
	rightPanel->Hide();

	runButton = ui->CreateClickBox("RunCB",5,5,30,30,TexMan::GetTex("runBtn"));
	runButton->SetBorder(1, 100, 100, 230);
	runButton->SetHoverFilter(true, 255, 255, 255, 120);
}

void ProgramScene::LogicUpdate(){}

void ProgramScene::FrameUpdate(){
	if (runButton->ConsumeStatus()) {
		ShowRunPanel();
	}
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
			CreateNewElem(1);
			return;
		}
		if (btnCreateList[1]->ConsumeStatus()) {
			CreateNewElem(2);
			return;
		}
		if (btnCreateList[2]->ConsumeStatus()) {
			CreateNewElem(3);
			return;
		}
		if (btnCreateList[3]->ConsumeStatus()) {
			CreateNewElem(4);
			return;
		}
	}
	if (panelType == 1) {
		if (ui->GetClickBox("BackRgb")->ConsumeStatus()) {
			std::string& R = ui->GetTextBox("BackRgb1")->GetText();
			std::string& G = ui->GetTextBox("BackRgb2")->GetText();
			std::string& B = ui->GetTextBox("BackRgb3")->GetText();
			unsigned char argR = 0;
			unsigned char argG = 0;
			unsigned char argB = 0;
			if (ArgToUCHar(R, argR) && ArgToUCHar(G, argG) && ArgToUCHar(B, argB)) {
				Global::defaultDrawColor[0] = argR;
				Global::defaultDrawColor[1] = argG;
				Global::defaultDrawColor[2] = argB;
			}
		}
		if (ui->GetClickBox("WindowW")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("WindowWtb")->GetText(), val)) {
				if (val >= 300 && val <= 4000) {
					Global::windowWidth = val;
					SDL_SetWindowSize(SceneMan::GetData<SDL_Window*>("Window"), val, Global::windowHeight);
					rightPanel->GetRectangle().Set(Global::windowWidth - 300, 0, 300, Global::windowHeight);
				}
				else {
					CreateErrorBox(ui, "Size must be between 300 and 4000");
				}
			}
		}
		if (ui->GetClickBox("WindowH")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("WindowHtb")->GetText(), val)) {
				if (val >= 300 && val <= 4000) {
					Global::windowHeight = val;
					SDL_SetWindowSize(SceneMan::GetData<SDL_Window*>("Window"), Global::windowWidth, val);
					rightPanel->GetRectangle().Set(Global::windowWidth - 300, 0, 300, Global::windowHeight);
				}
				else {
					CreateErrorBox(ui, "Size must be between 300 and 4000");
				}
			}
		}
	}

	else if (panelType == 2) {
		if (ui->GetClickBox("KeyUpdateAll")->ConsumeStatus()) {
			ui->GetClickBox("KeyEditName")->SetStatus(true);
			ui->GetClickBox("KeyEditX")->SetStatus(true);
			ui->GetClickBox("KeyEditY")->SetStatus(true);
			ui->GetClickBox("KeyEditW")->SetStatus(true);
			ui->GetClickBox("KeyEditH")->SetStatus(true);
			ui->GetClickBox("KeyEditFont")->SetStatus(true);
			ui->GetClickBox("KeyEditText")->SetStatus(true);
			ui->GetClickBox("KeyEditTextX")->SetStatus(true);
			ui->GetClickBox("KeyEditTextY")->SetStatus(true);

			ui->GetClickBox("KeyTextRender")->SetStatus(true);
			ui->GetClickBox("KeyZLayer")->SetStatus(true);
			ui->GetClickBox("KeyRenderType")->SetStatus(true);
			ui->GetClickBox("KeyColor")->SetStatus(true);
			ui->GetClickBox("KeyBorder")->SetStatus(true);
			ui->GetClickBox("KeyFontColor")->SetStatus(true);
		}

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
		else if (ui->GetClickBox("KeyZLayer")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyZLayertb")->GetText(), val)) {
				editedButton->SetZLayer(val);
			}
		}
		else if (ui->GetClickBox("KeyRenderType")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyRenderTypetb")->GetText(), val)) {
				editedButton->SetRenderType(val);
				for (auto& it : elements) {
					if (it.btn == editedButton) {
						it.renderType = val;
					}
				}
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

	if (outOptions) {
		if (ui->GetClickBox("btnRefOpt")->ConsumeStatus()) {
			outputType = 1;
			ui->GetClickBox("brnDirOut")->SetColor(255, 0, 0);
			ui->GetClickBox("btnRefOpt")->SetColor(0, 255, 0);
		}
		if (ui->GetClickBox("brnDirOut")->ConsumeStatus()) {
			outputType = 2;
			ui->GetClickBox("brnDirOut")->SetColor(0,255,0);
			ui->GetClickBox("btnRefOpt")->SetColor(255, 0, 0);
		}
		if(ui->GetClickBox("outConfBtn")->ConsumeStatus()){
			OutputUILayout(elements, ui, outputType);
			HideOutputSubPanel();
			outOptions = false;
		}
	}

	MoveSelected();
}

void ProgramScene::Input(SDL_Event& event){
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.scancode == SDL_SCANCODE_M) {
			if (panelType != 1 && panelType != 2) {
				ShowPanel();
			}
			else if(panelType == 1) {
				HidePanel();
			}
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_O) {
			if (!outOptions) {
				CreateOutputSubPanel();
				outOptions = true;
			}
			else {
				HideOutputSubPanel();
				outOptions = false;
			}
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_DELETE) {
			CreatedElement* elem = nullptr;
			Point p = GetMousePos();
			MT::Rect mouseRect{ p.x,p.y,1,1 };
			for (auto& it : elements) { // bez break aby by³ wybierany najnowszy zawsze
				if (it.btn->GetRectangle().IsColliding(mouseRect)) {
					elem = &it;
				}
			}
			if (elem != nullptr) {
				if (elem->btn == editedButton) { HideEditPanel(editedButton); }
				ui->DeleteButton(elem->btn->GetName());
				std::erase_if(elements, [&](const CreatedElement& e) {return &e == elem;});
			}
		}

		else if (event.key.keysym.scancode == SDL_SCANCODE_C) {
			CreatedElement* elem = nullptr;
			Point p = GetMousePos();
			MT::Rect mouseRect{ p.x,p.y,1,1 };
			for (auto& it : elements) { // bez break aby by³ wybierany najnowszy zawsze
				if (it.btn->GetRectangle().IsColliding(mouseRect)) {
					elem = &it;
				}
			}
			if (elem != nullptr) {
				selectedButton.btn = ui->CreateButton(elem->btn->GetName() + "copy" + std::to_string(rand()),10,10,10,10);
				if (selectedButton.btn == nullptr) {
					return;
				}
				*selectedButton.btn = *elem->btn;
				selectedButton.btn->SetName(elem->btn->GetName() + "copy" + std::to_string(rand()));
				selectedButton.renderType = elem->renderType;
				selectedButton.type = elem->type;
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		Point p = GetMousePos();
		MT::Rect mouseRect{ p.x,p.y,1,1 };
		if (event.button.button == SDL_BUTTON_LEFT) {;
			if (selectedButton.btn != nullptr) {
				elements.emplace_back(selectedButton);
				selectedButton.btn = nullptr;
			}
			else {
				for (auto& it : elements) { // bez break aby by³ wybierany najnowszy zawsze
					if (it.btn->GetRectangle().IsColliding(mouseRect)) {
						selectedButton.btn = it.btn;
					}
				}
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			if (panelType == 1) {return;}

			bool found = false;
			for (auto& it : elements) {
				if (it.btn->GetRectangle().IsColliding(mouseRect)) {
					ShowEditPanel(it.btn);
					found = true;
				}
			}
			if (!found) {
				if (panelType == 2) {
					HideEditPanel(editedButton);
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
	btnCreateList.Innit(ui, cb, w, h, 30, 30, 30, { "Button","Click Box", "Text Box", "Pop Up Box" }, 1);

	for (auto& it : btnCreateList.GetAll()) {
		it->SetColor(30, 30, 30);
		it->SetBorder(1, 0, 100, 200);
		it->SetRenderTextType(2);
		it->SetHoverFilter(true, 255, 255, 255, 120);
	}
	y = 100;

	std::string R = std::to_string(Global::defaultDrawColor[0]);
	std::string G = std::to_string(Global::defaultDrawColor[1]);
	std::string B = std::to_string(Global::defaultDrawColor[2]);

	CreateTripleEditBox("BackRgb", y, "BackGround", R, G, B);

	SDL_Window* window = SceneMan::GetData<SDL_Window*>("Window");
	int winW, winH;
	SDL_GetWindowSize(window,&winW,&winH);
	CreateEditBox("WindowW", y, "Window W: ", std::to_string(winW));
	CreateEditBox("WindowH", y, "Window H: ", std::to_string(winH));

	panelType = 1;
}

void ProgramScene::HidePanel() {
	rightPanel->Hide();
	btnCreateList.Clear();
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

void ProgramScene::CreateTripleEditBox(const std::string& name, int& y, const std::string& text,
	const std::string& arg1, const std::string& arg2, const std::string& arg3) {
	ClickBox* cb = ui->CreateClickBox(name, rightPanel->GetRectangle().x + 95
		, y, 80, 30, nullptr, ui->GetFont("arial12px"), text);
	SetUpBasicElem(cb);
	editClickRef.emplace_back(cb);
	cb->SetHoverFilter(true, 255, 255, 255, 120);

	y += 40;
	TextBox* tb = ui->CreateTextBox(name + "1",
		rightPanel->GetRectangle().x + 20, y, 60, 30, nullptr, ui->GetFont("arial12px"),arg1);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	tb = ui->CreateTextBox(name + "2",
		rightPanel->GetRectangle().x + 90, y, 60, 30, nullptr, ui->GetFont("arial12px"),arg2);
	SetUpBasicElem(tb);
	editTextRef.emplace_back(tb);

	tb = ui->CreateTextBox(name + "3",
		rightPanel->GetRectangle().x + 160, y, 60, 30, nullptr, ui->GetFont("arial12px"),arg3);
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
	}
	editedButton = button;
	rightPanel->Show();

	int y = rightPanel->GetRectangle().y + 10;

	ui->CreateClickBoxF("KeyUpdateAll", Global::windowWidth - 80, Global::windowHeight / 2, 70, 30, nullptr, "arial12px", "Update All");
	SetUpBasicElem(ui->GetClickBox("KeyUpdateAll"));
	ui->GetClickBox("KeyUpdateAll")->SetHoverFilter(true, 255, 255, 255, 120);

	CreateEditBox("KeyEditName", y, "Key: ",editedButton->GetName());
	CreateEditBox("KeyEditX", y, "X: ",std::to_string(editedButton->GetRectangle().x));
	CreateEditBox("KeyEditY", y, "Y: ", std::to_string(editedButton->GetRectangle().y));
	CreateEditBox("KeyEditW", y, "W: ", std::to_string(editedButton->GetRectangle().w));
	CreateEditBox("KeyEditH", y, "H: ", std::to_string(editedButton->GetRectangle().h));
	std::string textureName = "";
	if (editedButton->GetTexture() != nullptr) {
		for (auto& it : TexMan::Textures) {
			if (editedButton->GetTexture() == it.second) {
				textureName = it.first;
			}
		}
	}

	CreateEditBox("KeyEditTexture", y, "Texture: ",textureName);
	std::string fontStr = "";
	if (editedButton->GetFont() != nullptr) {
		for (auto& it : ui->fontManager->fonts) {
			if (it == editedButton->GetFont()) {
				fontStr = it->GetName();
			}
		}
	}
	CreateEditBox("KeyEditFont", y, "Font: ",fontStr);
	CreateEditBox("KeyEditText", y, "Text: ",editedButton->GetText());
	CreateEditBox("KeyEditTextSize", y, "TextSize: ",std::to_string(editedButton->GetTextScale()));
	CreateEditBox("KeyEditTextX", y, "Text X: ", std::to_string(editedButton->GetTextStartX()));
	CreateEditBox("KeyEditTextY", y, "Text Y: ", std::to_string(editedButton->GetTextStartY()));
	CreateEditBox("KeyTextRender", y, "Text Render: ", std::to_string(editedButton->textRenderType));
	CreateEditBox("KeyZLayer", y, "Z Layer: ", std::to_string(editedButton->zLayer));
	CreateEditBox("KeyRenderType", y, "Render Type: ", "");

	unsigned char* color = editedButton->buttonColor;
	CreateQuadEditBox("KeyColor", y, "Color", std::to_string(color[0]),
		std::to_string(color[1]), std::to_string(color[2]),std::to_string(color[3]));

	unsigned char* borderRGB = editedButton->borderRGB;
	CreateQuadEditBox("KeyBorder", y, "Border", std::to_string(editedButton->borderThickness),
		std::to_string(borderRGB[0]), std::to_string(borderRGB[1]),std::to_string(borderRGB[2]));

	unsigned char* fontColor = editedButton->fontRGB;

	CreateTripleEditBox("KeyFontColor", y, "Font Color", std::to_string(fontColor[0]),
		std::to_string(fontColor[1]), std::to_string(fontColor[2]));

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
	ui->DeleteClickBox("KeyUpdateAll");
	editedButton = nullptr;
	panelType = 0;
}

template <typename T>
void ConvertElement(T* cBtn, Button *btn, UI *Ui) {
	static_assert(std::is_same_v<T, Button> || std::is_same_v<T, TextBox> 
		|| std::is_same_v<T, ClickBox> || std::is_same_v<T, PopUpBox>, "Wrong type");

	cBtn->SetTexture(btn->GetTexture());
	cBtn->SetFont(btn->GetFont());
	cBtn->SetText(btn->GetText());
	cBtn->SetTextScale(btn->GetTextScale());
	cBtn->SetTextStartX(btn->GetTextStartX());
	cBtn->SetTextStartY(btn->GetTextStartY());
	cBtn->SetRenderTextType(btn->textRenderType);
	cBtn->SetColor(btn->buttonColor[0], btn->buttonColor[1], btn->buttonColor[2], btn->buttonColor[3]);
	cBtn->SetBorder(btn->borderThickness, btn->borderRGB[0], btn->borderRGB[1], btn->borderRGB[2]);
	cBtn->SetFontColor(btn->fontRGB[0], btn->fontRGB[1], btn->fontRGB[2]);
}

void ProgramScene::ShowRunPanel() {
	if (panelType == 3) {
		HideRunPanel();
		return;
	}
	HidePanel();
	HideEditPanel(editedButton);
	runButton->SetTexture(TexMan::GetTex("pauseBtn"));

	for (auto& it : elements) {
		it.btn->Hide();
		Button* btn = it.btn;
		MT::Rect& rect = btn->GetRectangle();
		switch(it.type){
			case 1: {
				Button* cBtn = ui->CreateButton(btn->name + "R", rect.x, rect.y, rect.w, rect.h);
				ConvertElement(cBtn,btn,ui);
				runBtnRef.emplace_back(cBtn);
				break;
			}

			case 2: {
				ClickBox* cBtn = ui->CreateClickBox(btn->name + "R", rect.x, rect.y, rect.w, rect.h);
				ConvertElement(cBtn, btn, ui);
				runClickRef.emplace_back(cBtn);
				break;
			}
			case 3: {
				TextBox* cBtn = ui->CreateTextBox(btn->name + "R", rect.x, rect.y, rect.w, rect.h);
				ConvertElement(cBtn, btn, ui);
				runTextRef.emplace_back(cBtn);
				break;
			}
			case 4: {
				PopUpBox* cBtn = ui->CreatePopUpBox(btn->name + "R", 120, rect.x, rect.y, rect.w, rect.h);
				ConvertElement(cBtn, btn, ui);
				runPopUpRef.emplace_back(cBtn);
				break;
			}
		}
	}

	panelType = 3;
}

void ProgramScene::HideRunPanel() {
	runButton->SetTexture(TexMan::GetTex("runBtn"));
	for (auto& it : elements) {
		it.btn->Show();
	}
	for (auto& it : runBtnRef) {
		ui->DeleteAnyElem(it->GetName());
	}
	for (auto& it : runTextRef) {
		ui->DeleteAnyElem(it->GetName());
	}
	for (auto& it : runClickRef) {
		ui->DeleteAnyElem(it->GetName());

	}
	for (auto& it : runPopUpRef) {
		ui->DeleteAnyElem(it->GetName());
	}
	panelType = 0;
}

void ProgramScene::CreateNewElem(const int type) {
	if (selectedButton.btn != nullptr) { return; }
	index++;
	int x, y;
	SDL_GetMouseState(&x, &y);
	selectedButton.btn = ui->CreateButton("btn" + std::to_string(index), x - 50, y - 50, 100, 100);
	selectedButton.type = type;
	HidePanel();
}

void ProgramScene::MoveSelected() {
	if (selectedButton.btn == nullptr) { return; }
	int x, y;
	SDL_GetMouseState(&x, &y);
	selectedButton.btn->GetRectangle().x = x - (selectedButton.btn->GetRectangle().w / 2);
	selectedButton.btn->GetRectangle().y = y - (selectedButton.btn->GetRectangle().h / 2);
}

void ProgramScene::CreateOutputSubPanel() {
	Button *btn = ui->CreateButton("outBtnBack", 100, 100, 200, 250,nullptr,ui->GetFont("arial20px"),"OutputOptions",1.0f,0,10);
	btn->SetRenderTextType(4);
	btn->SetColor(50, 30, 50, 255);
	btn->SetBorder(2, 100, 100, 255);

	ClickBox *cb = ui->CreateClickBox("btnRefOpt", 120, 160, 60, 60, nullptr, ui->GetFont("arial12px"), "Reference", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(255, 0, 0, 255);
	cb->SetBorder(1, 100, 100, 255);
	cb->SetHoverFilter(true, 255, 255, 255, 120,"hoverSound");

	cb = ui->CreateClickBox("brnDirOut", 220, 160, 60, 60, nullptr, ui->GetFont("arial12px"), "Direct", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(0, 255, 0, 255);
	cb->SetBorder(1, 100, 100, 255);
	cb->SetHoverFilter(true, 255, 255, 255, 120,"hoverSound");

	cb = ui->CreateClickBox("outConfBtn", 150, 240, 100, 50, nullptr, ui->GetFont("arial20px"), "Confirm");
	cb->SetRenderTextType(2);
	cb->SetColor(70, 30, 70, 255);
	cb->SetBorder(2, 50, 50, 255);
	cb->SetHoverFilter(true, 255, 255, 255, 120,"hoverSound");

}

void ProgramScene::HideOutputSubPanel() {
	ui->DeleteAnyElem("outBtnBack");
	ui->DeleteAnyElem("btnRefOpt");
	ui->DeleteAnyElem("brnDirOut");
	ui->DeleteAnyElem("outConfBtn");
}
#include "ProgramScene.h"

#include <print>

#include "Helpers.h"
#include "Printer.h"
#include "Loader.h"

void CreateErrorBox(UI* ui, const std::string& text) {
	int random = RandInt(0, 2000);
	PopUpBox* pb = ui->CreatePopUpBox("PBName" + std::to_string(random), 240, 10, 10, Global::windowWidth / 3, 100,
		nullptr, ui->GetFont("arial12px"), text);

	pb->SetColor(200, 200, 200);
	pb->SetFontColor(255, 0, 0);
	pb->SetRenderTextType(2);
}

void ProgramScene::Init(){
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
		Button* btn = editedButton->btn;
		if (editPanelState == 1) {
			if (editedButton->btn != nullptr) {

				if (ui->GetClickBox("XAxisToogle")->ConsumeStatus()) {
					if (editedButton->xAxisBlock) {
						editedButton->xAxisBlock = false;
						ui->GetClickBox("XAxisToogle")->SetColor(0, 100, 200, 0);
					}
					else {
						editedButton->xAxisBlock = true;
						ui->GetClickBox("XAxisToogle")->SetColor(0, 100, 200, 255);
					}

				}
				if (ui->GetClickBox("YAxisToogle")->ConsumeStatus()) {
					if (editedButton->yAxisBlock) {
						editedButton->yAxisBlock = false;
						ui->GetClickBox("YAxisToogle")->SetColor(0, 100, 200, 0);
					}
					else {
						editedButton->yAxisBlock = true;
						ui->GetClickBox("YAxisToogle")->SetColor(0, 100, 200, 255);
					}
				}
			}
			else {
				std::println("Edited is null");
			}

		}

		if (ui->GetClickBox("KeyUpdateAll")->ConsumeStatus()) {
			for (auto& it : editClickRef) {
				it->SetStatus(true);
			}
		}

		if (ui->GetClickBox("setingBtn")->ConsumeStatus()) {
			if (editPanelState == 0) {
				ui->GetClickBox("XAxisToogle")->TurnOn();
				ui->GetClickBox("XAxisToogle")->Show();
				ui->GetClickBox("YAxisToogle")->TurnOn();
				ui->GetClickBox("YAxisToogle")->Show();
				for (auto& it : editClickRef) {
					it->Hide();
					it->TurnOff();
				}
				for (auto& it : editTextRef) {
					it->Hide();
				}
				ui->GetClickBox("KeyUpdateAll")->Hide();
				ui->GetClickBox("KeyUpdateAll")->TurnOff();
				editPanelState = 1;
			}
			else {
				ui->GetClickBox("XAxisToogle")->Hide();
				ui->GetClickBox("XAxisToogle")->TurnOff();
				ui->GetClickBox("YAxisToogle")->Hide();
				ui->GetClickBox("YAxisToogle")->TurnOff();
				for (auto& it : editClickRef) {
					it->Show();
					it->TurnOn();
				}
				for (auto& it : editTextRef) {
					it->Show();
				}
				ui->GetClickBox("KeyUpdateAll")->Show();
				ui->GetClickBox("KeyUpdateAll")->TurnOn();
				editPanelState = 0;
			}
		}

		if (ui->GetClickBox("KeyEditName")->ConsumeStatus()) {
			btn->SetName(ui->GetTextBox("KeyEditNametb")->GetText());
		}
		else if (ui->GetClickBox("KeyEditX")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditXtb")->GetText(), val)) {
				btn->GetRectangle().x = val;
			}
		}
		else if (ui->GetClickBox("KeyEditY")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditYtb")->GetText(), val)) {
				btn->GetRectangle().y = val;
			}
		}
		else if (ui->GetClickBox("KeyEditW")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditWtb")->GetText(), val)) {
				btn->GetRectangle().w = val;
			}
		}
		else if (ui->GetClickBox("KeyEditH")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditHtb")->GetText(), val)) {
				btn->GetRectangle().h = val;
			}
		}
		else if (ui->GetClickBox("KeyEditTexture")->ConsumeStatus()) {
			std::string& textureName = ui->GetTextBox("KeyEditTexturetb")->GetText();
			if (TexMan::GetTex(textureName) != nullptr) {
				btn->SetTexture(TexMan::GetTex(textureName));
			}
		}
		else if (ui->GetClickBox("KeyEditFont")->ConsumeStatus()) {
			std::string& textureName = ui->GetTextBox("KeyEditFonttb")->GetText();
			if (ui->GetFont(textureName) != nullptr) {
				btn->SetFont(ui->GetFont(textureName));
			}
		}
		else if (ui->GetClickBox("KeyEditText")->ConsumeStatus()) {
			btn->SetText(ui->GetTextBox("KeyEditTexttb")->GetText());
		}
		else if (ui->GetClickBox("KeyEditTextSize")->ConsumeStatus()) {
			float val = 0.0f;
			if (ArgToFloat(ui->GetTextBox("KeyEditTextSizetb")->GetText(), val)) {
				btn->SetTextScale(val);
			}
		}
		else if (ui->GetClickBox("KeyEditTextX")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditTextXtb")->GetText(), val)) {
				btn->SetTextStartX(val);
			}
		}
		else if (ui->GetClickBox("KeyEditTextY")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditTextYtb")->GetText(), val)) {
				btn->SetTextStartY(val);
			}
		}
		else if (ui->GetClickBox("KeyTextRender")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyTextRendertb")->GetText(), val)) {
				btn->SetRenderTextType(val);
			}
		}
		else if (ui->GetClickBox("KeyZLayer")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyZLayertb")->GetText(), val)) {
				btn->SetZLayer(val);
			}
		}
		else if (ui->GetClickBox("KeyRenderType")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyRenderTypetb")->GetText(), val)) {
				btn->SetRenderType(val);
				for (auto& it : elements) {
					if (it.btn == btn) {
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
				btn->SetColor(argR, argG, argB, argA);
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
				btn->SetBorder(argW, argR, argG, argB);
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
				btn->SetFontColor(argR, argG, argB);
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

		if (ui->GetClickBox("outJsonCb")->ConsumeStatus()) {
			std::vector<UIElemBase*> dumpElements;
			for (auto& elem : elements) {
				dumpElements.emplace_back(elem.btn);
			}
			ui->DumpToJson("jsonDump",dumpElements);
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
		else if (event.key.keysym.scancode == SDL_SCANCODE_O) { // output
			if (panelType == 2) { return; }
			if (!outOptions) {
				CreateOutputSubPanel();
				outOptions = true;
			}
			else {
				HideOutputSubPanel();
				outOptions = false;
			}
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_I) { // input
			LoadUIFromText(ui, "README.md");
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
				if (elem == editedButton) { 
					HideEditPanel(editedButton);
					editedButton = nullptr;
				}
				if (elem == selectedButton) {
					selectedButton = nullptr;
				}
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
				std::string id = std::to_string(rand());
				CreatedElement newElement(ui->CreateButton(elem->btn->GetName() + "copy" + id, 10, 10, 10, 10),elem->type);
				newElement.renderType = elem->renderType;
				*newElement.btn = *elem->btn;
				newElement.btn->name = elem->btn->GetName() + "copy" + id;
				elements.emplace_back(newElement);
				selectedButton = &elements.back();
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		Point p = GetMousePos();
		MT::Rect mouseRect{ p.x,p.y,1,1 };
		if (event.button.button == SDL_BUTTON_LEFT) {;
			if (selectedButton != nullptr) {
				selectedButton = nullptr;
			}
			else {
				for (auto& it : elements) { // bez break aby by³ wybierany najnowszy zawsze
					if (it.btn->GetRectangle().IsColliding(mouseRect)) {
						selectedButton = &it;
					}
				}
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			if (panelType == 1) {return;}

			bool found = false;
			for (auto& it : elements) {
				if (it.btn->GetRectangle().IsColliding(mouseRect)) {
					ShowEditPanel(&it);
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
	for (auto& btn : editTextRef) {
		ui->DeleteTextBox(btn->GetName());
	}
	for (auto& btn : editClickRef) {
		ui->DeleteClickBox(btn->GetName());
	}
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

void ProgramScene::ShowEditPanel(CreatedElement *button) {

	if (panelType == 2) {
		HideEditPanel(button);
	}
	editedButton = button;
	Button *ebBtn = editedButton->btn;
	rightPanel->Show();
	editPanelTwo.Init(ui);

	int y = rightPanel->GetRectangle().y + 10;

	ClickBox* cb = ui->CreateClickBox("setingBtn", Global::windowWidth -40, 10, 30, 30, TexMan::GetTex("kogIcon"));
	cb->SetBorder(1, 0, 100, 200);
	cb->SetHoverFilter(true, 255, 255, 255, 120);


	ui->CreateClickBoxF("KeyUpdateAll", Global::windowWidth - 80, Global::windowHeight / 2, 70, 30, nullptr, "arial12px", "Update All");
	SetUpBasicElem(ui->GetClickBox("KeyUpdateAll"));
	ui->GetClickBox("KeyUpdateAll")->SetHoverFilter(true, 255, 255, 255, 120);

	CreateEditBox("KeyEditName", y, "Key: ", ebBtn->GetName());
	CreateEditBox("KeyEditX", y, "X: ",std::to_string(ebBtn->GetRectangle().x));
	CreateEditBox("KeyEditY", y, "Y: ", std::to_string(ebBtn->GetRectangle().y));
	CreateEditBox("KeyEditW", y, "W: ", std::to_string(ebBtn->GetRectangle().w));
	CreateEditBox("KeyEditH", y, "H: ", std::to_string(ebBtn->GetRectangle().h));
	std::string textureName = "";
	if (ebBtn->GetTexture() != nullptr) {
		for (auto& it : TexMan::Textures) {
			if (ebBtn->GetTexture() == it.second) {
				textureName = it.first;
			}
		}
	}

	CreateEditBox("KeyEditTexture", y, "Texture: ",textureName);
	std::string fontStr = "";
	if (ebBtn->GetFont() != nullptr) {
		for (auto& it : ui->fontManager->fonts) {
			if (it == ebBtn->GetFont()) {
				fontStr = it->GetName();
			}
		}
	}
	CreateEditBox("KeyEditFont", y, "Font: ",fontStr);
	CreateEditBox("KeyEditText", y, "Text: ", ebBtn->GetText());
	CreateEditBox("KeyEditTextSize", y, "TextSize: ",std::to_string(ebBtn->GetTextScale()));
	CreateEditBox("KeyEditTextX", y, "Text X: ", std::to_string(ebBtn->GetTextStartX()));
	CreateEditBox("KeyEditTextY", y, "Text Y: ", std::to_string(ebBtn->GetTextStartY()));
	CreateEditBox("KeyTextRender", y, "Text Render: ", std::to_string(ebBtn->textRenderType));
	CreateEditBox("KeyZLayer", y, "Z Layer: ", std::to_string(ebBtn->zLayer));
	CreateEditBox("KeyRenderType", y, "Render Type: ", "");

	MT::ColorA color = ebBtn->buttonColor;
	CreateQuadEditBox("KeyColor", y, "Color", std::to_string(color.R),
		std::to_string(color.G), std::to_string(color.B),std::to_string(color.A));

	MT::Color borderRGB = ebBtn->borderRGB;
	CreateQuadEditBox("KeyBorder", y, "Border", std::to_string(ebBtn->borderThickness),
		std::to_string(borderRGB.R), std::to_string(borderRGB.G),std::to_string(borderRGB.B));

	MT::Color fontColor = ebBtn->fontRGB;

	CreateTripleEditBox("KeyFontColor", y, "Font Color", std::to_string(fontColor.R),
		std::to_string(fontColor.G), std::to_string(fontColor.B));


	editPanelTwo.Add(ui->CreateClickBoxF("XAxisToogle",Global::windowWidth -100,100,30,30,nullptr,"arial12px"));
	editPanelTwo.GetClickBoxes().back()->SetBorder(1, 0, 100, 200);
	editPanelTwo.GetClickBoxes().back()->SetColor(255, 255, 255, 0);
	editPanelTwo.GetClickBoxes().back()->TurnOff();
	editPanelTwo.GetClickBoxes().back()->SetText("X Axis Block");
	editPanelTwo.GetClickBoxes().back()->SetTextStartX(-80);
	editPanelTwo.GetClickBoxes().back()->SetTextStartY(10);
	editPanelTwo.GetClickBoxes().back()->Hide();
	editPanelTwo.Add(ui->CreateClickBoxF("YAxisToogle", Global::windowWidth - 100, 150, 30, 30, nullptr, "arial12px"));
	editPanelTwo.GetClickBoxes().back()->SetBorder(1, 0, 100, 200);
	editPanelTwo.GetClickBoxes().back()->SetColor(255, 255, 255, 0);
	editPanelTwo.GetClickBoxes().back()->Hide();
	editPanelTwo.GetClickBoxes().back()->SetText("Y Axis Block");
	editPanelTwo.GetClickBoxes().back()->SetTextStartX(-80);
	editPanelTwo.GetClickBoxes().back()->SetTextStartY(10);
	editPanelState = 0;
	panelType = 2;
}

void ProgramScene::HideEditPanel(CreatedElement* button) {
	rightPanel->Hide();
	for (auto& btn : editTextRef) {
		ui->DeleteTextBox(btn->GetName());
	}
	for (auto& btn : editClickRef) {
		ui->DeleteClickBox(btn->GetName());
	}
	editTextRef.clear();
	editClickRef.clear();
	ui->DeleteClickBox("KeyUpdateAll");
	ui->DeleteClickBox("setingBtn");
	editedButton = nullptr;
	editPanelTwo.Clear();
	editPanelState = 0;
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
	cBtn->SetColor(btn->buttonColor.R, btn->buttonColor.G, btn->buttonColor.B, btn->buttonColor.A);
	cBtn->SetBorder(btn->borderThickness, btn->borderRGB.R, btn->borderRGB.G, btn->borderRGB.B);
	cBtn->SetFontColor(btn->fontRGB.R, btn->fontRGB.G, btn->fontRGB.B);
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
	if (selectedButton != nullptr) { return; }
	index++;
	int x, y;
	SDL_GetMouseState(&x, &y);
	elements.emplace_back(ui->CreateButton("btn" + std::to_string(index), x - 50, y - 50, 100, 100), type);
	selectedButton = &elements.back();
	HidePanel();
}

void ProgramScene::MoveSelected() {
	if (selectedButton == nullptr) { return; }
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (!selectedButton->xAxisBlock) {
		selectedButton->btn->GetRectangle().x = x - (selectedButton->btn->GetRectangle().w / 2);
	}
	if (!selectedButton->yAxisBlock) {
		selectedButton->btn->GetRectangle().y = y - (selectedButton->btn->GetRectangle().h / 2);
	}
}

void ProgramScene::CreateOutputSubPanel() {
	Button *btn = ui->CreateButton("outBtnBack", 100, 100, 400, 250,nullptr,ui->GetFont("arial20px"),"OutputOptions",1.0f,0,10);
	btn->SetRenderTextType(4);
	btn->SetColor(50, 30, 50, 255);
	btn->SetBorder(2, 100, 100, 255);

	auto Adjust = [](ClickBox* cb) {
		cb->SetBorder(1, 100, 100, 255);
		cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	};

	ClickBox *cb = ui->CreateClickBox("btnRefOpt", 120, 160, 60, 60, nullptr, ui->GetFont("arial12px"), "Reference", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(255, 0, 0, 255);
	Adjust(cb);

	cb = ui->CreateClickBox("brnDirOut", 220, 160, 60, 60, nullptr, ui->GetFont("arial12px"), "Direct", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(0, 255, 0, 255);
	Adjust(cb);

	cb = ui->CreateClickBox("outJsonCb", 320, 160, 60, 60, nullptr, ui->GetFont("arial12px"), "Json", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(255, 0, 0, 255);
	Adjust(cb);

	cb = ui->CreateClickBox("loadJsonCb", 420, 160, 60, 60, nullptr, ui->GetFont("arial12px"), "JsonLoad", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(0, 255, 0, 255);
	Adjust(cb);

	cb = ui->CreateClickBox("outConfBtn", 300, 240, 100, 50, nullptr, ui->GetFont("arial20px"), "Confirm");
	cb->SetRenderTextType(2);
	cb->SetColor(70, 30, 70, 255);
	Adjust(cb);

}

void ProgramScene::HideOutputSubPanel() {
	ui->DeleteAnyElem("outBtnBack");
	ui->DeleteAnyElem("btnRefOpt");
	ui->DeleteAnyElem("brnDirOut");
	ui->DeleteAnyElem("outConfBtn");
}
#include "ProgramScene.h"

#include <print>

#include "Helpers.h"

#include "Files.h"
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
	rightPanel = ui->CreateButton("Right Panel", Global::windowWidth - 300,0,300,Global::windowHeight);
	rightPanel->SetColor(30, 30, 30);
	rightPanel->SetBorder(2, 0, 100, 200);
	rightPanel->Hide();

	currentSection.Init(ui);
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
			CreateNewElem((int)CastType::Button);
			return;
		}
		if (btnCreateList[1]->ConsumeStatus()) {
			CreateNewElem((int)CastType::ClickBox);
			return;
		}
		if (btnCreateList[2]->ConsumeStatus()) {
			CreateNewElem((int)CastType::TextBox);
			return;
		}
		if (btnCreateList[3]->ConsumeStatus()) {
			CreateNewElem((int)CastType::PopUpBox);
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
		UIElemBase* btn = editedButton->btn;
		if (editPanelState == 1) {
			if (editedButton->btn != nullptr) {
				auto ToogleHelper = [&](const std::string& name, bool& flag) {
					if (ui->ConsumeIfExist(name)) {
						if (flag) {
							flag = false;
							ui->GetClickBox(name)->SetColor(255, 0, 0);
						}
						else {
							flag = true;
							ui->GetClickBox(name)->SetColor(0, 100, 200, 255);
						}
					}
				};
				ToogleHelper("XAxisToogle", editedButton->xAxisBlock);
				ToogleHelper("YAxisToogle", editedButton->xAxisBlock);
				ToogleHelper("WidthOrientation", editedButton->widthOrientation);
				ToogleHelper("HeightOrientation", editedButton->heightOrientation);
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
				ui->GetClickBox("WidthOrientation")->TurnOn();
				ui->GetClickBox("WidthOrientation")->Show();
				ui->GetClickBox("HeightOrientation")->TurnOn();
				ui->GetClickBox("HeightOrientation")->Show();
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
				ui->GetClickBox("WidthOrientation")->Hide();
				ui->GetClickBox("WidthOrientation")->TurnOff();
				ui->GetClickBox("HeightOrientation")->Hide();
				ui->GetClickBox("HeightOrientation")->TurnOff();
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
			ui->RenameElem(btn->GetName(), ui->GetTextBox("KeyEditNametb")->GetText());
		}
		else if (ui->GetClickBox("KeyEditX")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditXtb")->GetText(), val)) {
				if (editedButton->widthOrientation) {
					btn->GetRectangle().x = Global::windowWidth - val;
				}
				else {
					btn->GetRectangle().x = val;
				}

			}
		}
		else if (ui->GetClickBox("KeyEditY")->ConsumeStatus()) {
			int val = 0;
			if (ArgToInt(ui->GetTextBox("KeyEditYtb")->GetText(), val)) {
				btn->GetRectangle().y = val;
				if (editedButton->heightOrientation) {
					btn->GetRectangle().y = Global::windowHeight - val;
				}
				else {
					btn->GetRectangle().y = val;
				}
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
		else if (ui->GetClickBox("KeyFilter")->ConsumeStatus()) {
			std::string& R = ui->GetTextBox("KeyFilter1")->GetText();
			std::string& G = ui->GetTextBox("KeyFilter2")->GetText();
			std::string& B = ui->GetTextBox("KeyFilter3")->GetText();
			std::string& A = ui->GetTextBox("KeyFilter4")->GetText();
			unsigned char argR = 0;
			unsigned char argG = 0;
			unsigned char argB = 0;
			unsigned char argA = 0;
			if (ArgToUCHar(R, argR) && ArgToUCHar(G, argG) && ArgToUCHar(B, argB) && ArgToUCHar(A, argA)) {
				btn->SetHoverFilter(true, argR, argG, argB, argA);
			}
		}

		if (btn->castType == (int)CastType::ClickBox) {
			ClickBox* castedCB = static_cast<ClickBox*>(btn);
			if (ui->ConsumeIfExist("KeyTurnedOn")) {
				int val = castedCB->turnedOn;
				if (ArgToInt(ui->GetTextBox("KeyTurnedOntb")->GetText(), val)) {
					if (val) {
						castedCB->TurnOn();
					}
					else {
						castedCB->TurnOff();
					}
				}
			}

			if (ui->ConsumeIfExist("KeyClickSound")) {
				std::string val = ui->GetTextBox("KeyClickSoundtb")->GetText();
				castedCB->clickSound = val;
			}
		}
	}
		
	if (ui->ConsumeIfExist("btnRefOpt")) {
		outputType = 1;
		ui->GetClickBox("brnDirOut")->SetColor(255, 0, 0);
		ui->GetClickBox("btnRefOpt")->SetColor(0, 255, 0);
	}
	if (ui->ConsumeIfExist("brnDirOut")) {
		outputType = 2;
		ui->GetClickBox("brnDirOut")->SetColor(0,255,0);
		ui->GetClickBox("btnRefOpt")->SetColor(255, 0, 0);
	}
	if (ui->ConsumeIfExist("outJsonCb")) {
		std::vector<UIElemBase*> dumpElements;
		for (auto& elem : elements) {
			dumpElements.emplace_back(elem.btn);
		}
		ui->DumpToJson("jsonDump",dumpElements);
	}	
	if(ui->ConsumeIfExist("outConfBtn")){
		OutputUILayout(elements, ui, outputType);
		HideOutputSubPanel();
	}

	// Output
	if(ui->ConsumeIfExist("loadJson")){
		FileExplorer fe;
		std::string fileName = fe.Open("");
		std::vector <UIElemBase*> loadedElements = ui->LoadFromJson(fileName);
		for (auto& elem : loadedElements) {
			int type = 0;
			if (dynamic_cast<Button*>(elem) != nullptr) {
				type = 1;
			}
			if (dynamic_cast<TextBox*>(elem) != nullptr) {
				type = 2;
			}
			if (dynamic_cast<ClickBox*>(elem) != nullptr) {
				type = 3;
			}
			if (dynamic_cast<PopUpBox*>(elem) != nullptr) {
				type = 4;
			}
			elements.emplace_back(elem,type);
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
			if (outInPanel == 1) {
				HideOutputSubPanel();
			}
			else {
				CreateOutputSubPanel();
			}
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_I) { // input
			if (panelType == 2) { return; }
			if (outInPanel == 2) {
				HideInputSubPanel();
			}
			else {
				CreateInputSubPanel();
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
				if (elem == editedButton) { 
					HideEditPanel(editedButton);
					editedButton = nullptr;
				}
				if (elem == selectedButton) {
					selectedButton = nullptr;
				}
				ui->DeleteElement(elem->btn->GetName());
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

	if (event.type == SDL_MOUSEWHEEL) {
		int wheelWal = event.wheel.y;
		int scroolSpeed = 10;

		if (panelType != 2 && editPanelState != 1) { return; }
		if (wheelWal > 0) { // down
			if (currentScrool > 0) { return; }
			currentScrool += scroolSpeed;
			for (auto& cb : editClickRef) {
				cb->GetRectangle().y += scroolSpeed;
			}
			for (auto& tb : editTextRef) {
				tb->GetRectangle().y += scroolSpeed;
			}
		}
		else if (wheelWal < 0) { // up
			if (currentScrool < -500) { return; }
			currentScrool -= scroolSpeed;
			for (auto& cb : editClickRef) {
				cb->GetRectangle().y -= scroolSpeed;
			}
			for (auto& tb : editTextRef) {
				tb->GetRectangle().y -= scroolSpeed;
			}
		}
		//std::println("{}", currentScrool);
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
		ui->DeleteElement(btn->GetName());
	}
	for (auto& btn : editClickRef) {
		ui->DeleteElement(btn->GetName());
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
	currentScrool = 0;
	if (panelType == 2) {
		HideEditPanel(button);
	}
	editedButton = button;
	UIElemBase *ebBtn = editedButton->btn;
	rightPanel->Show();

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
		for (auto& it : TexMan::GetAllTex()) {
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

	MT::ColorA borderRGBA = ebBtn->borderRGB;
	CreateQuadEditBox("KeyBorder", y, "Border", std::to_string(ebBtn->borderThickness),
		std::to_string(borderRGBA.R), std::to_string(borderRGBA.G),std::to_string(borderRGBA.B));

	MT::ColorA fontColor = ebBtn->fontRGB;

	CreateTripleEditBox("KeyFontColor", y, "Font Color", std::to_string(fontColor.R),
		std::to_string(fontColor.G), std::to_string(fontColor.B));

	MT::ColorA hooverFilter = ebBtn->hoverFilter;
	CreateQuadEditBox("KeyFilter", y, "Filter", std::to_string(hooverFilter.R),
		std::to_string(hooverFilter.G), std::to_string(hooverFilter.B), std::to_string(hooverFilter.A));



	if (ebBtn->castType == (int)CastType::ClickBox) {
		ClickBox *castedElem = static_cast<ClickBox*>(ebBtn);
		bool turnedOn = castedElem->turnedOn;
		CreateEditBox("KeyTurnedOn", y, "Turned On: ", std::to_string(turnedOn));

		std::string clickSound = castedElem->clickSound;
		CreateEditBox("KeyClickSound", y, "Click Sound: ", clickSound);
	}
 

	// Additional Settings
	auto setDefault = [](ClickBox* cb) {
		cb->SetColor(255, 0, 0);
		cb->TurnOff();
		cb->SetTextStartX(-100);
		cb->SetTextStartY(10);
		cb->Hide();
		//cb->SetRenderType(2);
	};

	currentSection.Add(ui->CreateClickBoxF("XAxisToogle",Global::windowWidth -100,100,30,30,nullptr,"arial12px", "X Axis Block"));
	cb = currentSection.GetClickBoxes().back();
	setDefault(cb);

	currentSection.Add(ui->CreateClickBoxF("YAxisToogle", Global::windowWidth - 100, 150, 30, 30, nullptr, "arial12px", "Y Axis Block"));
	cb = currentSection.GetClickBoxes().back();
	setDefault(cb);

	currentSection.Add(ui->CreateClickBoxF("WidthOrientation", Global::windowWidth - 100, 200, 30, 30, nullptr, "arial12px", "Width Relative"));
	cb = currentSection.GetClickBoxes().back();
	setDefault(cb);

	currentSection.Add(ui->CreateClickBoxF("HeightOrientation", Global::windowWidth - 100, 250, 30, 30, nullptr, "arial12px", "Heigth Relative"));
	cb = currentSection.GetClickBoxes().back();
	setDefault(cb);

	editPanelState = 0;
	panelType = 2;
}

void ProgramScene::HideEditPanel(CreatedElement* button) {
	rightPanel->Hide();
	for (auto& btn : editTextRef) {
		ui->DeleteElement(btn->GetName());
	}
	for (auto& btn : editClickRef) {
		ui->DeleteElement(btn->GetName());
	}
	editTextRef.clear();
	editClickRef.clear();
	ui->DeleteElement("KeyUpdateAll");
	ui->DeleteElement("setingBtn");
	editedButton = nullptr;
	currentSection.Clear();
	editPanelState = 0;
	panelType = 0;
}

template <typename T>
void ConvertElement(T* cBtn, UIElemBase* btn, UI *Ui) {
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

void ProgramScene::CreateNewElem(const int type) {
	if (selectedButton != nullptr) { return; }
	index++;
	Point p = GetMousePos();

	std::string name  = "btn" + std::to_string(index);

	switch (type) {
		case (int)CastType::Button:
			elements.emplace_back(ui->CreateButton(name, p.x - 50, p.y - 50, 100, 100), type);
			break;
		case (int)CastType::ClickBox:
			elements.emplace_back(ui->CreateClickBox(name, p.x - 50, p.y - 50, 100, 100), type);
			break;
		case (int)CastType::TextBox:
			elements.emplace_back(ui->CreateTextBox(name, p.x - 50, p.y - 50, 100, 100), type);
			break;
		case (int)CastType::PopUpBox:
			elements.emplace_back(ui->CreatePopUpBox(name, 1'000'000, p.x - 50, p.y - 50, 100, 100), type);
			break;
	}


	selectedButton = &elements.back();
	HidePanel();
}

void ProgramScene::MoveSelected() {
	if (selectedButton == nullptr) { return; }
	Point p = GetMousePos();
	if (!selectedButton->xAxisBlock) {
		selectedButton->btn->GetRectangle().x = p.x - (selectedButton->btn->GetRectangle().w / 2);
	}
	if (!selectedButton->yAxisBlock) {
		selectedButton->btn->GetRectangle().y = p.y - (selectedButton->btn->GetRectangle().h / 2);
	}
}

void ProgramScene::CreateOutputSubPanel() {
	currentSection.Clear();
	Button *btn = ui->CreateButton("outBtnBack", 100, 100, 300, 250,nullptr,ui->GetFont("arial20px"),"OutputOptions",1.0f,0,10);
	btn->SetRenderTextType(4);
	btn->SetColor(50, 30, 50, 255);
	btn->SetBorder(2, 100, 100, 255);
	currentSection.Add(btn);

	auto Adjust = [&](ClickBox* cb) {
		cb->SetBorder(1, 100, 100, 255);
		cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
		currentSection.Add(cb);
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

	cb = ui->CreateClickBox("outConfBtn", 200, 240, 100, 50, nullptr, ui->GetFont("arial20px"), "Confirm");
	cb->SetRenderTextType(2);
	cb->SetColor(70, 30, 70, 255);
	Adjust(cb);
	outInPanel = 1;

}

void ProgramScene::HideOutputSubPanel() {
	currentSection.Clear();
	outInPanel = 0;
}

void ProgramScene::CreateInputSubPanel() {
	currentSection.Clear();
	Button* btn = ui->CreateButton("outBtnBack", 100, 100, 150, 150, nullptr, ui->GetFont("arial20px"), "OutputOptions", 1.0f, 0, 10);
	btn->SetRenderTextType(4);
	btn->SetColor(50, 30, 50, 255);
	btn->SetBorder(2, 100, 100, 255);
	currentSection.Add(btn);

	auto Adjust = [&](ClickBox* cb) {
		cb->SetBorder(1, 100, 100, 255);
		cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
		currentSection.Add(cb);
		};

	ClickBox* cb = ui->CreateClickBoxF("loadJson", 120, 160, 60, 60, nullptr, "arial12px", "Load Json", 1.0f, 0, -15);
	cb->SetRenderTextType(4);
	cb->SetColor(255, 0, 0, 255);
	Adjust(cb);
	outInPanel = 2;
}

void ProgramScene::HideInputSubPanel() {
	currentSection.Clear();
	outInPanel = 0;
}
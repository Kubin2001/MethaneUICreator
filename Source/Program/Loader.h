#pragma once
#include <print>
#include <fstream>
#include <vector>

#include "UI.h"

void AnalyzeInput(UI* ui, const std::vector<std::string> input) {

}

void LoadUIFromText(UI *ui, const char* fileName) {
	std::println("Loading started");
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::println("Cannot open file in function LoadUIFromText aborting");
	}
	std::vector<std::string> LoadedFileText;
	std::string line;
	while (std::getline(file, line)) {
		LoadedFileText.emplace_back(line);
	}
	AnalyzeInput(ui,LoadedFileText);
	for (auto& line : LoadedFileText) {
		std::println("{}",line);
	}
	std::println("Loading finisched");
}
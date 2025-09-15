#pragma once

#include <functional>
#include <vector>

#include <UI.h>

class EditorFunctions {
	private:
		

	public:
		static std::vector<std::function<void(Button* btn, const std::string& arg)>> functions;
		static void CreateFunctions();
};
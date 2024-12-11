#include "../include/ImGuiFilePicker.hpp"

#include "../../Bolt-imgui/include/ImGuiFileDialog.h"

void ImGuiFilePicker::render() {
	IGFD::FileDialogConfig config;
	config.path = "./resources/mesh/";
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*", config);

	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

			// if is using windows parse the path before using
#ifdef _WIN32
			{
				// make custom path for windows
				std::vector<std::string> words;
				std::string word;
				std::istringstream stream(filePathName);
				bool start_writing = false, add_sep = true;
				string res = "./";

				while (std::getline(stream, word, '\\')) {
					std::istringstream subStream(word);
					if (!start_writing && word == "resources") {
						start_writing = true;
					}

					if (start_writing) {
						res.append(word);
						res.append("/");
					}
				}

				if (!res.empty()) {
					res.pop_back();
				}
				filePathName = string(res);
			}
#endif
			// this->obj_observer->changeTexture(filePathName);
            this->m_action(filePathName);
			this->close();
		}

		// close
		ImGuiFileDialog::Instance()->Close();
	}
}

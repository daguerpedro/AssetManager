#pragma once
struct Console {
	std::vector<std::string> messages;

	void log(const std::string& m)
	{
		messages.push_back(m);
	}

	void clear()
	{
		messages.clear();
	}

	void draw()
	{
		ImGui::Begin("LOG");
		if (ImGui::SmallButton("Clear")) clear();

		if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -(ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing())), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NavFlattened))
		{
			for (auto s : messages)
				ImGui::TextUnformatted(s.c_str());
		}
		ImGui::EndChild();
		ImGui::End();
	}
};
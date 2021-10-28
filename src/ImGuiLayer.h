#pragma once
#include "Layer.h"


class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	virtual void OnImGuiRender() override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void Begin();
	void End();
};


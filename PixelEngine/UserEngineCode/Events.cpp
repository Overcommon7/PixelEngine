#include "pch.h"
#include "Events.h"
#include "DepthBuffer.h"
#include "MatrixStack.h"
#include "Clipper.h"
#include "VariableEditor.h"


void Events::OnScriptLoaded()
{
	Clipper::OnScriptInit();
}

void Events::OnScriptInit()
{
	DepthBuffer::Initialize();
}

void Events::OnNewFrame()
{
	MatrixStack::Update();
	DepthBuffer::Update();
}

#include "pch.h"
#include "Events.h"

#include "DepthBuffer.h"
#include "MatrixStack.h"
#include "Clipper.h"
#include "LightManager.h"
#include "PrimitiveManager.h"


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
	LightManager::OnNewFrame();
	PrimitiveManager::OnNewFrame();
}

void Events::OnDrawFrame()
{
	Clipper::Draw();
}

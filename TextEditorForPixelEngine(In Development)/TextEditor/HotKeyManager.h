#pragma once
enum class Action
{
	None,
    Save,
	SaveAs,
	Copy,
	Paste,
	Cut,
	Duplicate,
	MoveLeft,
	MoveRight
};

class HotKeyManager
{
	HotKeyManager() = delete;
	HotKeyManager(const HotKeyManager& h) = delete;
	HotKeyManager& operator=(const HotKeyManager& h) = delete;

public:
	static Action GetHotKeyExecuted();
};

										   
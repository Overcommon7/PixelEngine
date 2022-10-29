#include "pch.h"
#include "HotKeyManager.h"
#include "User.h"

Action HotKeyManager::GetHotKeyExecuted()
{
    bool CTRL = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
    bool SHIFT = IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    char c = tolower(User::GetChar());
    if (CTRL)
    {
        if (c == 's')
            if (SHIFT) return Action::SaveAs;
            else return Action::Save;

        if (c == 'c') return Action::Copy;
        if (c == 'v') return Action::Paste;
        if (c == 'x') return Action::Cut;
        if (c == 'd') return Action::Duplicate;
    }

    if (User::GetKey() == KEY_LEFT) return Action::MoveLeft;
    if (User::GetKey() == KEY_RIGHT) return Action::MoveRight;
    return Action::None;
}

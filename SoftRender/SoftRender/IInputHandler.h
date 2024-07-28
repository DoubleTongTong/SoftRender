#pragma once

class IInputHandler {
public:
    virtual void OnKeyDown(int virtualKeyCode) = 0;
    virtual void OnKeyUp(int virtualKeyCode) = 0;
    virtual void OnMouseMove(
        int posX,
        int posY,
        bool leftButton,
        bool rightButton,
        bool middleButton) = 0;
};
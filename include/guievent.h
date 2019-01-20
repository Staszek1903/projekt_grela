#ifndef GUIEVENT_H
#define GUIEVENT_H

#define ENTER 13
#define BACKSPACE 8

struct GuiEvent
{
    int mouse_x, mouse_y;
    bool mouse_pressed, mouse_released;
    int char_clicked;

    GuiEvent()
        :mouse_x(0),mouse_y(0), mouse_pressed(false), mouse_released(false),char_clicked(0){}
};

#endif // GUIEVENT_H

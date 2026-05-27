#ifndef YUBI_H
#define YUBI_H

enum game_state {
    GAMEPLAY,
    MENU,
    PAUSED
};

namespace cpu_render {
    void draw(void *userdata);
}


#endif

/** global.hpp **/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#define DRAW_3D true
//If false, use parallel 3D instead which is the opposite for cross-eyed 3D
//If you use parallel 3D you should probably lower the resolution in main.cpp
#define CROSS_EYED true

extern const short WIDTH;
extern const short HEIGHT;

extern Uint8 *playerinputs;

#endif

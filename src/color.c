#include "../include/minirt.h"
#include <stdint.h>

void set_red(t_color *color, uint8_t colour)
{
    color->r = colour;
}

void set_green(t_color *color, uint8_t colour)
{
    color->g = colour;
}

void set_blue(t_color *color, uint8_t colour)
{
    color->b = colour;
}

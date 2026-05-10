#include "../input/input.h"
#include "../render/utils.h"

void start_credits(bool *show_credits, bool *pause, const float height);
void advance_credits(const float dt, bool *show_credits, const float height);
void display_credits(const float width, const float height);
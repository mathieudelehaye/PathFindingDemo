#include "room.h"

Room::Room(int hs, int vs) : obstacle_map(hs, vs, 0) {
	horizontalSize = hs;
    verticalSize = vs;
    // obstacle_map[9][9]=1; obstacle_map[9][10]=1; obstacle_map[10][9]=1; obstacle_map[10][10]=1;
}

#pragma once

enum mesh_t
{
    MESH_BLOCK
};

enum keys_t
{
	KEY_ESCAPE = 0,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
    KEY_R,
	KEY_SPACE,
	KEY_LEFT_SHIFT
};

namespace constants
{
    extern Mesh* blockMesh;
    extern double blockSize;
}

#pragma once

namespace emu
{
	namespace cpu
	{
		namespace vdp
		{
			//VRAM/CRAM/regs size
			static const int VDP_VRAM_SIZE = 1024 * 16;
			static const int VDP_CRAM_SIZE = 32;
			static const int VDP_NUM_REGISTERS = 16;

			//Screen and planes
			static const int VDP_SCREEN_WIDTH = 256;
			static const int VDP_SCREEN_HEIGHT = 192;
			static const int VDP_SCANLINES_NTSC = 262;
			static const int VDP_SCANLINES_PAL = 313;

			//Palettes
			static const int VDP_PALETTE_SIZE = 16;
			static const int VDP_MAX_COLOURS = 64;
			static const int VDP_PALETTE_OFFS_BG = 0;
			static const int VDP_PALETTE_OFFS_SPRITE = 16;

			//Pattern table access
			static const int VDP_MAP_REG_ADDR_MASK = 0xE;
			static const int VDP_MAP_REG_ADDR_SHIFT = 0x1;
			static const int VDP_MAP_WORD_Y_SHIFT = 0x6;
			static const int VDP_MAP_WORD_X_SHIFT = 0x1;

			//Background plane
			static const int VDP_BG_PLANE_WIDTH_TILES = 32;
			static const int VDP_BG_PLANE_HEIGHT_TILES = 28;

			//Cell word
			static const int VDP_CELL_MASK_PALETTE = 0x800;
			static const int VDP_CELL_SHIFT_PALETTE = 0xB;

			//Tiles
			static const int VDP_TILE_WIDTH = 8;
			static const int VDP_TILE_HEIGHT = 8;
			static const int VDP_TILE_SIZE_BYTE = (VDP_TILE_WIDTH * VDP_TILE_HEIGHT) / 2;

			//Colour conversion
			static const int VDP_COLOUR_MASK_B = 0x30;
			static const int VDP_COLOUR_MASK_G = 0x0C;
			static const int VDP_COLOUR_MASK_R = 0x03;
			static const int VDP_COLOUR_SHIFT_B = 4;
			static const int VDP_COLOUR_SHIFT_G = 2;
			static const int VDP_COLOUR_SHIFT_R = 0;
		}
	}
}
#pragma once

#ifndef BLOCKS_H
#define BLOCKS_H

#include <string>

#include "globals.h"
#include "drawable.h"
#include "transform.h"

namespace blocks {
	class Block {
	public:
		unsigned int id;

		rsrc::BlockFaceDrawer* faces;

		Block(unsigned int id, std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom);
		~Block();

		void append(structs::Transform trans, unsigned int filter);
	};
}

#endif
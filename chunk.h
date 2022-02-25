#pragma once

#ifndef CHUNK_H
#define CHUNK_H

namespace chunk {
	struct Chunk {
	public:
		unsigned int* blockData;

		int xPos, zPos;

		Chunk(int xPos, int zPos);
		~Chunk();

		inline unsigned int blockAt(unsigned int x, unsigned int y, unsigned int z);
		void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int block);

		void draw();

		void populate();
	};
}

#endif
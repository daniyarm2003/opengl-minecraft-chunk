#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "chunk.h"
#include "globals.h"
#include "transform.h"

using namespace glm;
using namespace std;

namespace chunk {
	Chunk::Chunk(int xPos, int zPos) {
		this->xPos = xPos;
		this->zPos = zPos;

		this->blockData = new unsigned int[16 * 64 * 16];

		for (unsigned int i = 0; i < 16 * 64 * 16; i++) {
			this->blockData[i] = -1;
		}
	}

	Chunk::~Chunk() {
		delete[] this->blockData;
	}

	inline unsigned int Chunk::blockAt(unsigned int x, unsigned int y, unsigned int z) {
		return this->blockData[16 * 64 * z + 64 * x + y];
	}

	void Chunk::setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int block) {
		this->blockData[16 * 64 * z + 64 * x + y] = block;
	}

	void Chunk::draw() {
		for (unsigned int x = 0; x < 16; x++) {
			for (unsigned int z = 0; z < 16; z++) {
				for (unsigned int y = 0; y < 64; y++) {
					if (this->blockAt(x, y, z) == -1) continue;

					unsigned int filter = 0;

					if (z == 0) {
						bool chunkExists = false;

						for (vector<Chunk*>::iterator it = globals::chunks.begin(); it != globals::chunks.end(); it++) {
							if ((*it)->zPos == this->zPos - 1) {
								chunkExists = true;

								if((*it)->blockAt(x, y, 15) == -1)
									filter |= 2;
							}
						}

						filter |= (chunkExists ? 0 : 2);
					}
					else if (this->blockAt(x, y, z - 1) == -1) {
						filter |= 2;
					}

					if (z == 15) {
						bool chunkExists = false;

						for (vector<Chunk*>::iterator it = globals::chunks.begin(); it != globals::chunks.end(); it++) {
							if ((*it)->zPos == this->zPos + 1) {
								chunkExists = true;

								if((*it)->blockAt(x, y, 0) == -1)
									filter |= 1;
							}
						}

						filter |= (chunkExists ? 0 : 1);
					}
					else if (this->blockAt(x, y, z + 1) == -1) {
						filter |= 1;
					}


					if (x == 0) {
						bool chunkExists = false;

						for (vector<Chunk*>::iterator it = globals::chunks.begin(); it != globals::chunks.end(); it++) {
							if ((*it)->xPos == this->xPos - 1) {
								chunkExists = true;

								if((*it)->blockAt(15, y, z) == -1)
									filter |= 4;
							}
						}

						filter |= (chunkExists ? 0 : 4);
					}
					else if (this->blockAt(x - 1, y, z) == -1) {
						filter |= 4;
					}

					if (x == 15) {
						bool chunkExists = false;

						for (vector<Chunk*>::iterator it = globals::chunks.begin(); it != globals::chunks.end(); it++) {
							if ((*it)->xPos == this->xPos + 1) {
								chunkExists = true;

								if((*it)->blockAt(0, y, z) == -1)
									filter |= 8;
							}
						}

						filter |= (chunkExists ? 0 : 8);
					}
					else if (this->blockAt(x + 1, y, z) == -1) {
						filter |= 8;
					}


					if (y == 63 || this->blockAt(x, y + 1, z) == -1) {
						filter |= 16;
					}

					if (y == 0 || this->blockAt(x, y - 1, z) == -1) {
						filter |= 32;
					}

					structs::Transform blockPos;

					blockPos.pos = vec3(4.0f * static_cast<float>(this->xPos) + 0.25f * (float)x, 0.25f * (float)y, 4.0f * static_cast<float>(this->zPos) + 0.25f * (float)z);

					globals::blocklist.at(this->blockAt(x, y, z))->append(blockPos, filter);
				}
			}
		}
	}

	void Chunk::populate() {
		for (unsigned int x = 0; x < 16; x++) {
			for (unsigned int z = 0; z < 16; z++) {

				int topY = 10U + (int)(4.0f * sinf((float)(x + this->xPos * 16) / 2.0f) + 2.0f * sinf((float)(z + this->zPos * 16)));

				for (int y = topY; y >= 0; y--) {
					this->setBlock(x, (unsigned int)y, z, y == topY ? 0 : 1);
				}
			}
		}
	}
}
#include <string>

#include "drawable.h"
#include "globals.h"
#include "blocks.h"
#include "transform.h"

using namespace std;

namespace blocks {
	Block::Block(unsigned int id, string front, string back, string left, string right, string top, string bottom) {
		this->id = id;

		this->faces = new rsrc::BlockFaceDrawer[] {
			rsrc::BlockFaceDrawer(globals::faceverts::vertsFront, 48 * sizeof(float), "face_shader", front),
			rsrc::BlockFaceDrawer(globals::faceverts::vertsBack, 48 * sizeof(float), "face_shader", back),

			rsrc::BlockFaceDrawer(globals::faceverts::vertsLeft, 48 * sizeof(float), "face_shader", left),
			rsrc::BlockFaceDrawer(globals::faceverts::vertsRight, 48 * sizeof(float), "face_shader", right),

			rsrc::BlockFaceDrawer(globals::faceverts::vertsTop, 48 * sizeof(float), "face_shader", top),
			rsrc::BlockFaceDrawer(globals::faceverts::vertsBottom, 48 * sizeof(float), "face_shader", bottom),
		};
	}

	Block::~Block() {
		delete[] this->faces;
	}

	void Block::append(structs::Transform trans, unsigned int filter) {
		for (unsigned int i = 0; i < 6; i++) {
			if (filter & (1U << i)) {
				this->faces[i].iTransforms.push_back(trans.toMat4());
			}
		}
	}
}
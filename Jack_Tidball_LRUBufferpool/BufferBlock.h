#ifndef BUFFERBLOCK_H

#define BUFFERBLOCK_H

#include "BufferBlockADT.h"

class BufferBlock : public BufferBlockADT
{
private:
	int blockID;
	char* block;

public:
	BufferBlock(){
		block = new char[4096];
	}

	BufferBlock(char* data, int sz = 4096) {
		block = new char[sz];
		for (int i = 0; i < sz; i++) {
			block[i] = data[i];
		}
	}

	~BufferBlock() {

	}

	//read the block from pos to pos + sz-1 (or to the end of the block)
	void getData(int pos, int sz, char* data) {
		int lastPos = 0;

		if ((pos + sz) > BLOCKSIZE) {
			lastPos = BLOCKSIZE - 1;
		} else {
			lastPos = (pos + sz) - 1;
		}
		for (int i = 0; (pos + i) < lastPos; i++) {
			data[i] = block[pos + i];
		}
	}

	//setID
	void setID(int id) {
		blockID = id;
	}

	//getID
	int getID() const {
		return blockID;
	}

	//getBlocksize
	int getBlocksize() const {
		return strlen(block);
	}

	//return the block
	char* getBlock() const {
		return block;
	}

	//set the block
	void setBlock(char* blk) {
		for (int i = 0; i < 4096; i++)
			block[i] = blk[i];
	}
};

#endif // !BUFFERBLOCK_H

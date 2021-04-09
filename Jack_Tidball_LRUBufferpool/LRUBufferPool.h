
#ifndef LRUBUFFERPOOL_H
#define LRUBUFFERPOOL_H


#include "BufferPoolADT.h"
#include "fstream"
#include "constants.h"
#include "BufferBlock.h"

class LRUBufferPool : public BufferPoolADT {
private:

	BufferBlock* block;
	char* data = new char[BLOCKSIZE];
	fstream input;

public:
	//Default Constructor
	LRUBufferPool() {}

	LRUBufferPool(string filename, int poolSize = POOL_SIZE, int blockSize = BLOCKSIZE) {
		
		block = new BufferBlock[poolSize];
		data = new char[blockSize];
		// open the file 
		input.open(filename.c_str(), fstream::in | fstream::binary);
		// Set the Block data and the Block ID
		for (int i = 0; i < poolSize; i++) {
				input.seekg(i * blockSize);
				input.read(data, blockSize);
				block[i].setID(i);
				block[i].setBlock(data);
			
		}
	}
	
	//Destructor 
	~LRUBufferPool() {
		input.close();
		delete data;
	}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {

		bool isfound = false;
		int Id = pos / BLOCKSIZE;
		
		static int t;

		for (int i = 0; i < 5; i++) {
			if (block[i].getID() == Id) {
					isfound = true;
					block[i].getData((pos % BLOCKSIZE), sz+1, space); // THIS TOOK ME FOREVER TO FIGURE OUT sz = sz+1
					BufferBlock temp = block[i];
					do {
						block[i] = block[(i - 1)];
						i--;
					} while (i > 0);
					block[0] = temp;
					break;
				}
				t = i;
			}

		if (isfound == false) {
			
			input.seekg(4096 * Id);
			input.read(data, BLOCKSIZE);
			block[t].setBlock(data);
			block[t].setID(Id);
			block[t].getData((pos % BLOCKSIZE), sz, space);
			BufferBlock temp = block[t];
			do {
				block[t] = block[(t - 1)];
				t--;
			} while (t > 0);
			block[0] = temp;

		}
	}

	// Print the order of the buffer blocks using the block id
	//	numbers.
	void printBufferBlockOrder() {
		cout << "Buffer Block Order is: " << endl;
		for (int i = 0; i < 5; i++) {
			cout << block[i].getID() << ", ";
		}
		cout << "\n\n";
	}

	// Get the block id number of the least recently used 
	//	buffer block.
	int getLRUBlockID() {
		return block[4].getID();
	}
};

#endif // !LRUBUFFERPOOL_H
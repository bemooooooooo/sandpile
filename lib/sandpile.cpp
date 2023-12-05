#include "sandpile.hpp"


void setValues(uint64_t** &sandpile, Options& options) {
	//Create
	sandpile = new uint64_t* [options.x];
	for (uint64_t i = 0; i < options.x; ++i) {
		sandpile[i] = new uint64_t[options.y]{};
	}
	//Set
	std::ifstream in;
	in.open(options.tsv_filename);
	uint16_t  x, y;		
	uint64_t value;
	while (!in.eof()) { 
		in >> x >> y >> value;
		sandpile[x][y] = value;
	}
}

void resize(uint64_t** &arr, Options& options) {
	options.x += 2;
	options.y += 2;
	uint64_t** new_arr = new uint64_t* [options.x]{};
	new_arr[0] = new uint64_t[options.y]{};
	new_arr[options.x - 1] = new uint64_t[options.y]{};
	for (int i = 1; i < options.x-1; ++i) {
		new_arr[i] = new uint64_t [options.y]{};
		for (int j = 1; j < options.y-1; ++j) {
			new_arr[i][j] = arr[i - 1][j - 1];
		}
	}
	arr = new_arr;
}

bool checkForResize(uint64_t** arr, Options& options) {
	for (uint16_t i = 0; i < options.x; ++i) {
		if (arr[i][0] >= 4 || arr[i][options.y - 1] >= 4) {
			return true;
		}
	}
	for (uint16_t i = 0; i < options.y; ++i) {
		if (arr[0][i] >= 4 || arr[options.x -1 ][i] >= 4) {
			return true;
		}
	}
	return false;
}


void move(uint64_t** &sandpile, uint16_t i, uint16_t j) {
	sandpile[i][j] -= 4;
	++sandpile[i + 1][j];
	++sandpile[i - 1][j];
	++sandpile[i][j + 1];
	++sandpile[i][j - 1];
}

bool isCollapsePossible(uint64_t** &sandpile, Options& options) {
	bool isCollapsePossible = false;
	if (checkForResize(sandpile, options)) {
		resize(sandpile, options);
	}
	myQeque queue;
	for (uint16_t i = 0; i < options.x; ++i) {
		for (uint16_t j = 0; j < options.y; ++j) {
			if (sandpile[i][j] >= 4) {
				isCollapsePossible = true;
				MeshData data(i, j);
				queue.pushMyQueue(data);
			}
		}
	}
	while (!queue.isEmpty()){
		MeshData new_data = queue.popMyQueue();
		move(sandpile, new_data.x, new_data.y);
	}
	return isCollapsePossible;
}

void collapse(uint64_t** &sandpile, Options& options)
{
	uint64_t iter = 0;
	bool last_condition = options.frequency == 0;
	if (!last_condition) {
		std::string new_output_directory = options.output_directory + "\\0.bmp";
		toImage(sandpile, options.x, options.y, new_output_directory);
	}
	while ((iter < options.max_iterations) && !isCollapsePossible(sandpile, options)){
		++iter;
		if (!last_condition && iter % options.frequency == 0) {
			std::string new_output_directory = options.output_directory + "\\"+ std::to_string(iter / options.frequency) + ".bmp";
			toImage(sandpile, options.x, options.y, new_output_directory);
		}
	}

	if (last_condition) {
		std::string new_output_directory = options.output_directory + "\\" + std::to_string(iter) + ".bmp";
		toImage(sandpile, options.x, options.y, new_output_directory);
	}
}

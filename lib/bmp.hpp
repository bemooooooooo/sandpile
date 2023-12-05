#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>


struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color();
	Color(unsigned char r, unsigned char g, unsigned char b);
	~Color();
};

void toImage(uint64_t**& mesh, uint16_t height, uint16_t width, std::string path);

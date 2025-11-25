#include "dbgtool.h"

#include <fstream>

int dump(char* filename, void* from, int size){
	char newname[260];
	snprintf(newname,260,"%s.LR2dmp",filename);

	std::ofstream file{newname};
	if (!file.good()) {
		return -1;
	}

	// cast safety: you can always cast to char* to inspect values as bytes
	file.write(reinterpret_cast<const char*>(from), size);

	return 0;
}


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#include "Array3D.h"


using std::ostringstream;
using std::string;
using std::cout;
using std::endl;


template<typename T> void writeFile(Array3D<T> &volume, string path)
{
	std::ofstream file(path, std::ios::binary);

	//store the block in the file
	file.write((char *)volume.getDataPointer(), volume.getSize() * sizeof(T));

	file.close();
}

template<typename T> void downsample(Array3D<T> &data)
{
	//create just the following level
	Array3D<T> newVolume;

	//create an array of the new size
	newVolume.create(floor(data.getWidth() >> 1), floor(data.getHeight() >> 1), floor(data.getDepth() >> 1));

	//interpolate 8 cells
	for (unsigned int i = 0; i < newVolume.getWidth(); i++)
		for (unsigned int j = 0; j < newVolume.getHeight(); j++)
			for (unsigned int k = 0; k < newVolume.getDepth(); k++)
				newVolume(i, j, k) = (data(i * 2, j * 2, k * 2) + data(i * 2 + 1, j * 2, k * 2) + data(i * 2, j * 2 + 1, k * 2) + data(i * 2 + 1, j * 2 + 1, k * 2) +
				data(i * 2, j * 2, k * 2 + 1) + data(i * 2 + 1, j * 2, k * 2 + 1) + data(i * 2, j * 2 + 1, k * 2 + 1) + data(i * 2 + 1, j * 2 + 1, k * 2 + 1)) / 8;

	//resize the original data
	data.create(newVolume.getWidth(), newVolume.getHeight(), newVolume.getDepth());

	//copy the data
	memcpy((void *)data.getDataPointer(), (void *)newVolume.getDataPointer(), newVolume.getSize() * sizeof(T));
}




template<typename T> void Load(string filename, unsigned int  width, unsigned int height, unsigned int depth)
{
	//Read texture from file
	std::ifstream textureFile(filename, std::ios::binary);

	if (!textureFile.is_open()){
		cout << "Couldn't load file" << endl;
		exit(0);
	}

	int length = -1;
	textureFile.seekg(0, textureFile.end);
	length = int(textureFile.tellg());
	textureFile.seekg(0, textureFile.beg);

	if (length != width * height * depth * sizeof(T)){
		cout << "Bad volume size or wrong file!" << endl;
		exit(0);
	}

	cout << "Loading volume." << endl;


	//create data to store the volume
	Array3D<T>  volume;
	volume.create(width, height, depth);

	//read the volume from the file
	textureFile.read((char*)volume.getDataPointer(), length);
	textureFile.close();


	//while the volume can be downsampled
	while (volume.getWidth() >= 2 && volume.getHeight() >= 2 && volume.getDepth() >= 2){
		cout << "Creating volume with size "<<volume.getWidth()/2 << "x" << volume.getHeight()/2 << "x" << volume.getDepth()/2 << endl;

		//downsample the volume
		downsample(volume);


		ostringstream oss;
		oss<< "volume" <<volume.getWidth()<<"x"<<volume.getHeight()<<"x" <<volume.getDepth()<<".raw";
		
		string path = oss.str();
		//write the volume into a file
		writeFile(volume, path);
	}
		

}



int main(int argc, char** argv){
	
	if (argc != 6){
		cout << "You must indicate the path of the volume by console, the width, the height, the depth, and the number of bits per voxel" << endl;
		exit(0);
	}


	string file = argv[1];
	unsigned int width = atoi(argv[2]), height = atoi(argv[3]), depth = atoi(argv[4]);

	if (atoi(argv[5]) == 8) Load<unsigned char>(file, width, height, depth);
	else if (atoi(argv[5]) == 16) Load<unsigned short>(file, width, height, depth);
	else cout << "bits should be 8 or 16." << endl;


	return 0;
}
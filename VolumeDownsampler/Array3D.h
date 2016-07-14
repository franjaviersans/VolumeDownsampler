// $Id: $
//
// Author: Francisco Sans franjaviersans@gmail.com
//
// Complete history on bottom of file

#ifndef ARRAY3D_H
#define ARRAY3D_H


/**
* Class Volume.
* Class to load a volume from a file and store it in a 3D texture to display.
*/
template <class T>
class Array3D
{
	//Functions

public:

	///Default constructor
	Array3D() :m_iWidth(0), m_iHeight(0), m_iDepth(0), data(NULL){};

	//Copy constructor
	Array3D(Array3D<T> &c) :m_iWidth(c.m_iWidth), m_iHeight(c.m_iHeight), m_iDepth(c.m_iDepth){
		data = new T[c.getSize()];
		memcpy(data, c.data, c.getSize() * sizeof(T));
	};

	///
	Array3D(unsigned int width, unsigned int  height, unsigned int  depth) :m_iWidth(width), m_iHeight(height), m_iDepth(depth){ data = new T[getSize()]; }

	///Default destructor
	~Array3D(){ delete []data; }

	///
	void create(unsigned int width, unsigned int  height, unsigned int  depth){ 
		if (data != NULL) delete []data;
		m_iWidth = width;
		m_iHeight = height;
		m_iDepth = depth;
		data = new T[getSize()]; 
	}

	///
	unsigned int getWidth(){ return m_iWidth; }

	///
	unsigned int getHeight(){ return m_iHeight; }

	///
	unsigned int getDepth(){ return m_iDepth; }

	///
	unsigned int getSize() { return getWidth() * getHeight() * getDepth(); }
	
	///
	const T * getDataPointer(){ return data; }

	///
	void clear(){ memset(data, 0xFFFFFFF, getSize() * sizeof(T)); }

	T operator ()(unsigned int i, unsigned int j, unsigned int k) const{ return data[k * getWidth() * getHeight() + j * getWidth() + i]; }
	T & operator ()(unsigned int i, unsigned int j, unsigned int k){ return data[k * getWidth() * getHeight() + j * getWidth() + i]; }

	//Variables

private:
	unsigned int m_iWidth, m_iHeight, m_iDepth;
	T *data;
};


#endif //ARRAY3D_H
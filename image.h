#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    private:
        int  width, height;                      					/* Initialize width, height, and maxvalue */
        unsigned char *buffer;                          			/* Initialize the 1D array as buffer */

	public: 
		Image();													//Default constructor
    	Image(Image &);												//Copy constructor
    	Image(int, int);											//Parametertized  constructor
		Image(unsigned char *);   									//2nd parameterized constructor

		int GetWidth();												//Initalize the get and set methods
		int GetHeight();
		unsigned char *GetBuffer();
		void ResetSize(int, int);
		void SetBuffer(unsigned char *);
		void SetSize(int, int);
};

#endif 
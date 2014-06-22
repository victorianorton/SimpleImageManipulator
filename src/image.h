#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    private:
        int  width, height;                                         /* Initialize width, height, and maxvalue */
        unsigned char *buffer;                                      /* Initialize the 1D array as buffer */
    
    public:
        Image();                                                    //Default constructor
        Image(Image &img);                                          //Copy constructor
        Image(int w, int h);                                        //Parametertized  constructor

        int GetWidth();                                             //Initalize the get and set methods
        int GetHeight();
        unsigned char *GetBuffer();
        void ResetSize(int w, int h);
};

#endif
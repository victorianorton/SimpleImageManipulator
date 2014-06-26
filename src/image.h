
#ifndef IMAGE_H
#define IMAGE_H

class source;

class Image
{
    private:
        int  width, height;                                         /* Initialize width, height, and maxvalue */
        unsigned char *buffer;                                          /* Initialize the 1D array as buffer */
        source *src;

    public:
        Image();                                                    //Default constructor
        Image(Image &img);                                          //Copy constructor
        Image(int w, int h);                                         //Parametertized  constructor

        void Update() const;
        void SetSource(source *source);
        int GetWidth() const;                                             //Initalize the get and set methods
        int GetHeight() const;
        unsigned char *GetBuffer() const;
        void ResetSize(int w, int h);
};

#endif
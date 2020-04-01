#ifndef IMAGE_H
#define IMAGE_H

class Image
{

public:

    virtual ~Image() { }

    virtual int width() = 0;

    virtual int height() = 0;

};

#endif // IMAGE_H

#include "background.h"

Background::Background(Image *image) :
    _image(image)
{

}

Image * Background::image()
{
    return _image;
}

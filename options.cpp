#include "options.h"

Options::Options()
{
    resetDefaults();
}

void Options::setColour(int x)
{
    colour = x;
}

int Options::getColour()
{
    return colour;
}

void Options::setFileName(QString x)
{
    filename = x;
}

void Options::setFilters(int x)
{
    filters = x;
}

void Options::setGaussSize(int x)
{
    gaussSize = x;
}

void Options::setMedianSize(int x)
{
    medianSize = x;
}

void Options::setThreshold(int x)
{
    threshold = x;
}

void Options::setValue(int x)
{
    value = x;
}

int Options::getFilters()
{
    return filters;
}

int Options::getMedianSize()
{
    return medianSize;
}

int Options::getGaussSize()
{
    return gaussSize;
}

QString Options::getFileName()
{
    return filename;
}

int Options::getValue()
{
    return value;
}

int Options::getThreshold()
{
    return threshold;
}

void Options::resetDefaults()
{
    filters = 0;
    medianSize = 3;
    gaussSize = 5;
    filename = QDir::currentPath() + "/save.jpg";
    threshold = 75;
    value = 255;
    colour = COLOUR_GREEN;
}

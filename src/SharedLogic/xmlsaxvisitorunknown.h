#ifndef XMLSAXVISITORUNKNOWN_H
#define XMLSAXVISITORUNKNOWN_H

#include "xmlsaxvisitor.h"

class XmlSAXVisitorUnknown : public XmlSAXVisitor
{

public:

    XmlSAXVisitorUnknown(XmlSAXVisitor *parent) :
        XmlSAXVisitor(parent), _level(1) { }

    bool onStartElement(char *, char **, XmlSAXVisitor *&) {
        ++_level;
        return true;
    }

    bool onFinishElement(XmlSAXVisitor *& current) {
        if (--_level == 0) {
            XmlSAXVisitor *caller = parent();
            delete this;
            current = caller;
            return true;
        } else {
            return true;
        }
    }

    bool onText(char *, int, XmlSAXVisitor *&) {
        return true;
    }

private:

    int _level;

};

#endif // XMLSAXVISITORUNKNOWN_H

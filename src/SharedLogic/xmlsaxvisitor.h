#ifndef XMLSAXVISITOR_H
#define XMLSAXVISITOR_H

class XmlSAXVisitor
{

public:

    virtual bool onStartElement(char * name, char ** atts, XmlSAXVisitor *& current) = 0;

    virtual bool onFinishElement(XmlSAXVisitor *& current) = 0;

    virtual bool onText(char *text, int len, XmlSAXVisitor *& current) = 0;

protected:

    XmlSAXVisitor(XmlSAXVisitor *parent) : _parent(parent) { }

    XmlSAXVisitor * parent() { return _parent; }

    void setParent(XmlSAXVisitor *parent) { _parent = parent; }

private:

    XmlSAXVisitor *_parent;

};

#endif // XMLSAXVISITOR_H

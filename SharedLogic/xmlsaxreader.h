#ifndef XMLSAXREADER_H
#define XMLSAXREADER_H

#include "xmlsaxvisitor.h"
#include <libxml/parser.h>

class XmlSAXReader
{

public:

    XmlSAXReader();

    bool parseFile(const char *filePath, XmlSAXVisitor *visitor);

private:

    xmlSAXHandler _handler;

    XmlSAXVisitor *_visitor;

    bool _failed;


    static void
    on_start_element(void *ctx, const xmlChar * name, const xmlChar ** atts);

    static void
    on_finish_element(void *ctx, const xmlChar *);

    static void
    on_text(void *ctx, const xmlChar *ch, int len);

};

#endif // XMLSAXREADER_H

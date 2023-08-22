#include "xmlsaxreader.h"

XmlSAXReader::XmlSAXReader()
{
    _handler.internalSubset = NULL;
    _handler.isStandalone = NULL;
    _handler.hasInternalSubset = NULL;
    _handler.hasExternalSubset = NULL;
    _handler.resolveEntity = NULL;
    _handler.getEntity = NULL;
    _handler.entityDecl = NULL;
    _handler.notationDecl = NULL;
    _handler.attributeDecl = NULL;
    _handler.elementDecl = NULL;
    _handler.unparsedEntityDecl = NULL;
    _handler.setDocumentLocator = NULL;
    _handler.startDocument = NULL;
    _handler.endDocument = NULL;
    _handler.startElement = on_start_element;
    _handler.endElement = on_finish_element;
    _handler.reference = NULL;
    _handler.characters = on_text;
    _handler.ignorableWhitespace = NULL;
    _handler.processingInstruction = NULL;
    _handler.comment = NULL;
    _handler.warning = NULL;
    _handler.error = NULL;
    _handler.fatalError = NULL;
}

bool XmlSAXReader::parseFile(const char *filePath, XmlSAXVisitor *visitor)
{
    _failed = false;
    _visitor = visitor;
    xmlSAXUserParseFile(&_handler, this, filePath);
    return !_failed;
}

void XmlSAXReader::on_start_element(void *ctx, const xmlChar * name, const xmlChar ** atts)
{
    XmlSAXReader * reader = (XmlSAXReader*)ctx;
    if (reader->_visitor == NULL) return;

    reader->_failed = !reader->_visitor->onStartElement(
                (char*)name, (char**)atts, reader->_visitor);

    if (reader->_failed) reader->_visitor = NULL;
}

void XmlSAXReader::on_finish_element(void *ctx, const xmlChar *)
{
    XmlSAXReader * reader = (XmlSAXReader*)ctx;
    if (reader->_visitor == NULL) return;

    reader->_failed = !reader->_visitor->onFinishElement(
                reader->_visitor);

    if (reader->_failed) reader->_visitor = NULL;
}

void XmlSAXReader::on_text(void *ctx, const xmlChar *ch, int len)
{
    XmlSAXReader * reader = (XmlSAXReader*)ctx;
    if (reader->_visitor == NULL) return;

    reader->_failed = !reader->_visitor->onText(
                (char*) ch, len, reader->_visitor);

    if (reader->_failed) reader->_visitor = NULL;
}


#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <string>
#include <iostream>
#include <sstream>

namespace __XmlWriter {
    extern std::ostream *os;
    extern bool inHeader;

    class BuildException {
        public:
            BuildException(const char *msg) : msg(msg) { }
            const char *what() { return msg; }
        private:
            const char *msg;
    };
}

#define xmlStreamDoc(OSTREAM, BLOCK) {                                        \
    __XmlWriter::os = &(OSTREAM);                                             \
    __XmlWriter::inHeader = false;                                            \
    *(__XmlWriter::os) << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";      \
    BLOCK;                                                                    \
}

#define xmlNode(NAME, BLOCK) {                              \
    if (__XmlWriter::inHeader) *(__XmlWriter::os) << ">";   \
    else __XmlWriter::inHeader = true;                      \
    *(__XmlWriter::os) << "<" << NAME;                      \
    BLOCK;                                                  \
    if (__XmlWriter::inHeader) *(__XmlWriter::os) << " />"; \
    else *(__XmlWriter::os) << "</" << NAME << ">";         \
    __XmlWriter::inHeader = false;                          \
}

#define xmlAtt(NAME, VALUE) {                                                          \
    if (!__XmlWriter::inHeader)                                                        \
        throw __XmlWriter::BuildException("Trying to put attribute out of node head"); \
    *(__XmlWriter::os) << " " << NAME << "=\"" << VALUE << "\"";                       \
}

#define xmlText *({                    \
    if (__XmlWriter::inHeader) {       \
        *(__XmlWriter::os) << ">";     \
        __XmlWriter::inHeader = false; \
    }                                  \
    __XmlWriter::os;                   \
})

#define xmlStringDoc(BLOCK) ({                                          \
    std::string __XmlWriterTempString;                                  \
    std::ostringstream __XmlWriterOStringStream(__XmlWriterTempString); \
    xmlStreamDoc(__XmlWriterOStringStream, BLOCK);                      \
    __XmlWriterOStringStream.str();                                     \
})

#endif // XMLWRITER_H

#ifndef XMLREADER_H
#define XMLREADER_H
#include <fstream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include "Grupo.h"
#include "Camara.h"
#include <regex>

using namespace tinyxml2;

class XMLParser {
    public:
        XMLParser();
        XMLDocument doc;
        Camara camara;
        Grupo grupo;

        XMLError loadXML(std::string file);
        bool parse();
    private:    
        bool parseCameraXML(XMLNode* camera);
        Grupo parseGroupXML(XMLNode* group);
        std::vector<Transformacao*> getTransformations(XMLNode* transforms);
        std::vector<std::string> getModelos(XMLNode* parent);
        std::vector<GLuint> getModelIndex(XMLNode* models) ;
};

#endif
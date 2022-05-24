#ifndef XMLREADER_H
#define XMLREADER_H
#include <fstream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include "Grupo.h"
#include "Camara.h"
#include <regex>
#include "Luz/Luz.h"
#include "Luz/LuzPosicional.h"
#include "Luz/LuzDirecional.h"
#include "Luz/LuzSpot.h"

using namespace tinyxml2;

class XMLParser {
    public:
        XMLParser();
        XMLDocument doc;
        Camara camara;
        Grupo grupo;
        std::vector<Luz*> luzes;

        XMLError loadXML(std::string file);
        bool parse();
    private:    
        bool parseLightXML(XMLNode* light);
        bool parseCameraXML(XMLNode* camera);
        Grupo parseGroupXML(XMLNode* group);
        std::vector<Transformacao*> getTransformations(XMLNode* transforms);
        std::vector<Modelo> getModelos(XMLNode* parent);
        std::vector<GLuint> getModelIndex(XMLNode* models) ;
};

#endif
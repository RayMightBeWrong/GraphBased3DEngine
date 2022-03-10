#ifndef XMLREADER_H
#define XMLREADER_H
#include <fstream>
#include "parserXML/tinyxml2.h"
#include <vector>
#include <string>
using namespace tinyxml2;
class XMLParser {
    public:
        XMLParser();
        XMLDocument doc;
        float camPX,camPY,camPZ;
        float camLX,camLY,camLZ;
        float camUX,camUY,camUZ;
        float projFOV,projNEAR,projFAR;
        std::vector<std::string> modelos;

        XMLError loadXML(std::string file);
        bool parse();
    private:    
        bool parseCameraXML();
        bool parseModelsXML();
};

#endif
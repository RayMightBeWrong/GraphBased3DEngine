#include "XMLDocReader.h"

using namespace tinyxml2;
using namespace std;


XMLParser::XMLParser() {};

XMLError XMLParser::loadXML(string nameFile) {
    return doc.LoadFile(nameFile.c_str());
}

bool XMLParser::parseCameraXML() {
	XMLNode* root = doc.FirstChildElement("world"); if (!root) return false;
	XMLNode* camera = root->FirstChildElement("camera"); if (!camera) return false;
	XMLElement* position = camera->FirstChildElement("position"); if (!position) return false;
	XMLElement* lookAT = camera->FirstChildElement("lookAt"); if (!lookAT) return false;
	XMLElement* up = camera->FirstChildElement("up"); if (!up) return false;
	XMLElement* proj = camera->FirstChildElement("projection"); if (!proj) return false;
	camPX = stof(position->Attribute("x"));
	camPY = stof(position->Attribute("y"));
	camPZ = stof(position->Attribute("z"));
	camLX = stof(lookAT->Attribute("x"));
	camLY = stof(lookAT->Attribute("y"));
	camLZ = stof(lookAT->Attribute("z"));
	camUX = stof(up->Attribute("x"));
	camUY = stof(up->Attribute("y"));
	camUZ = stof(up->Attribute("z"));
	projFOV = stof(proj->Attribute("fov"));
	projNEAR = stof(proj->Attribute("near"));
	projNEAR= stof(proj->Attribute("far"));
	return true;
}

bool XMLParser::parseModelsXML() { 
	XMLNode* root = doc.FirstChildElement("world"); if (!root) return false;
	XMLNode* group = root->FirstChildElement("group"); if (!group) return false;
	XMLNode* models = group->FirstChildElement("models"); if (!models) return false;
	XMLElement* model = models->FirstChildElement("model"); if (!model) return false;
	while (model != nullptr) {
		if (!model->Attribute("file")) return false;
		else {
			string nameFile = model->Attribute("file"); 
			modelos.push_back(nameFile);
		}
		model = model->NextSiblingElement();
	}
	return true;
}

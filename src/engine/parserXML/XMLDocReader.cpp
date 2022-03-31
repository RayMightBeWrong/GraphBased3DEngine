#include "XMLDocReader.h"

using namespace tinyxml2;
using namespace std;


XMLParser::XMLParser() {};

XMLError XMLParser::loadXML(string nameFile) {
    return doc.LoadFile(nameFile.c_str());
}

bool XMLParser::parse() {
	XMLNode* root = doc.FirstChildElement("world");
	XMLNode* camara = root->FirstChildElement("camera");
	XMLNode* group = root->FirstChildElement("group");
	parseCameraXML(camara);
	grupo = parseGroupXML(group);
	return true;
}

bool XMLParser::parseCameraXML(XMLNode* cam) {
	XMLElement* position = cam->FirstChildElement("position"); if (!position) return false;
	XMLElement* lookAT = cam->FirstChildElement("lookAt"); if (!lookAT) return false;
	XMLElement* up = cam->FirstChildElement("up"); if (!up) return false;
	XMLElement* proj = cam->FirstChildElement("projection"); if (!proj) return false;
	camara.camPX = stof(position->Attribute("x"));
	camara.camPY = stof(position->Attribute("y"));
	camara.camPZ = stof(position->Attribute("z"));
	camara.camLX = stof(lookAT->Attribute("x"));
	camara.camLY = stof(lookAT->Attribute("y"));
	camara.camLZ = stof(lookAT->Attribute("z"));
	camara.camUX = stof(up->Attribute("x"));
	camara.camUY = stof(up->Attribute("y"));
	camara.camUZ = stof(up->Attribute("z"));
	camara.projFOV = stof(proj->Attribute("fov"));
	camara.projNEAR = stof(proj->Attribute("near"));
	camara.projFAR= stof(proj->Attribute("far"));
	return true;
}

// TODO: Adicionar exceptions para combater erros no parsing.
Grupo XMLParser::parseGroupXML(XMLNode* group){
	Grupo g;
	XMLNode* transforms = group->FirstChildElement("transform"); 
	if (transforms != nullptr) g.transformacoes = getTransformations(transforms);
	XMLNode* models = group->FirstChildElement("models");
	if (models != nullptr) {
		g.modelos = getModelos(models);
		g.modelsIndex = getModelIndex(models);
	}
	XMLNode* subGrupos = group->FirstChildElement("group");
	while (subGrupos != nullptr) {
		g.subgrupos.push_back(parseGroupXML(subGrupos));
		subGrupos = subGrupos->NextSiblingElement("group");
	}
	return g;
}

vector<Transformacao*> XMLParser::getTransformations(XMLNode* transforms) {
	vector<Transformacao*> transf;
	XMLElement* op = transforms->FirstChildElement();
	while (op != nullptr) {
		if (strcmp(op->Value(),"translate") == 0) {
			float x = stof(op->Attribute("x"));
			float y = stof(op->Attribute("y"));
			float z = stof(op->Attribute("z"));
			Translacao *t = new Translacao(x,y,z) ;
			transf.push_back(t);
		}
		if (strcmp(op->Value(),"rotate") == 0) {
			float angulo = stoi(op->Attribute("angle"));
			float x = stof(op->Attribute("x"));
			float y = stof(op->Attribute("y"));
			float z = stof(op->Attribute("z"));
			Rotacao *r = new Rotacao(angulo,x,y,z);
			transf.push_back(r);
		}
		if (strcmp(op->Value(),"scale") == 0) {
			float x = stof(op->Attribute("x"));
			float y = stof(op->Attribute("y"));
			float z = stof(op->Attribute("z"));
			Escala *s = new Escala(x,y,z);
			transf.push_back(s);
		}
		op = op->NextSiblingElement();
	}
	return transf; 
}

vector<string> XMLParser::getModelos(XMLNode* models){
	vector<string> modelos;
	XMLElement* model = models->FirstChildElement("model");
	while (model != nullptr) {
		string nameFile = model->Attribute("file"); 
		modelos.push_back(nameFile);
		model = model->NextSiblingElement("model");
	}
	return modelos;
}

vector<GLuint> XMLParser::getModelIndex(XMLNode* models) {
	vector<GLuint> index;
	XMLElement* model = models->FirstChildElement("model");
	while (model != nullptr) {
		model = model->NextSiblingElement("model");
	}
	return index;
}

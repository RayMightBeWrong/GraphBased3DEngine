#include "XMLDocReader.h"

using namespace tinyxml2;
using namespace std;

static char toLower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
} 

XMLParser::XMLParser() {};

XMLError XMLParser::loadXML(string nameFile) {
    return doc.LoadFile(nameFile.c_str());
}

bool XMLParser::parse() {
	XMLNode* root = doc.FirstChildElement("world");
	XMLNode* camara = root->FirstChildElement("camera");
	XMLNode* group = root->FirstChildElement("group");
	XMLNode* light = root->FirstChildElement("lights");
	parseCameraXML(camara);
	parseLightXML(light);
	grupo = parseGroupXML(group);
	return true;
}

bool XMLParser::parseLightXML(XMLNode* lights) {
	XMLElement *light = lights->FirstChildElement("light");
	while (light != nullptr) {
		const char* type = light->Attribute("type");

		if (strcmp(type,"point") == 0) {
			float x = stof(light->Attribute("posx"));
			float y = stof(light->Attribute("posy"));
			float z = stof(light->Attribute("posz"));

			Luz* point = new LuzPosicional(x,y,z);

			luzes.push_back(point);

		}

		if (strcmp(type,"directional") == 0) {
			float x = stof(light->Attribute("dirx"));
			float y = stof(light->Attribute("diry"));
			float z = stof(light->Attribute("dirz"));

			Luz* direc = new LuzDirecional(x,y,z);

			luzes.push_back(direc);
		}

		if (strcmp(type,"spot") == 0) {
			float x1 = stof(light->Attribute("posx"));
			float y1 = stof(light->Attribute("posy"));
			float z1 = stof(light->Attribute("posz"));
			float x2 = stof(light->Attribute("dirx"));
			float y2 = stof(light->Attribute("diry"));
			float z2 = stof(light->Attribute("dirz"));
			float cut = stof(light->Attribute("cutoff"));

			Luz* spot = new LuzSpot(x1,y1,z1,x2,y2,z2,cut);

			luzes.push_back(spot);
		}

		light = light->NextSiblingElement("light");
	}
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

Grupo XMLParser::parseGroupXML(XMLNode* group){
	Grupo g;
	XMLNode* transforms = group->FirstChildElement("transform"); 
	if (transforms != nullptr) g.transformacoes = getTransformations(transforms);
	XMLNode* models = group->FirstChildElement("models");
	if (models != nullptr) {
		g.modelos = getModelos(models);
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
			const char* x1 = op->Attribute("x");
			const char* y1 = op->Attribute("y");
			const char* z1 = op->Attribute("z");
			const char* timeTest = op->Attribute("time");
			const char* alignTest = op->Attribute("align");


			if (x1 != nullptr && y1 != nullptr && z1 != nullptr) {
				float x = stof(x1);
				float y = stof(y1);
				float z = stof(z1);
				TranslacaoEstatica *t = new TranslacaoEstatica(x,y,z) ;
				transf.push_back(t);
			}
			else if (timeTest != nullptr && alignTest != nullptr){
				bool align;
				std::vector<float> pontosCurva;
				float time = stof(timeTest);
				if (regex_match (alignTest,regex("[Tt][rR][uU][Ee]"))) {
					align = true; 
				}
				else {
					align = false;
				}
				XMLElement *nextPonto = op->FirstChildElement("point");
				while (nextPonto != nullptr) {
					float xPonto = stof(nextPonto->Attribute("x"));
					float yPonto = stof(nextPonto->Attribute("y"));
					float zPonto = stof(nextPonto->Attribute("z"));
					pontosCurva.push_back(xPonto);
					pontosCurva.push_back(yPonto);
					pontosCurva.push_back(zPonto);

					nextPonto = nextPonto->NextSiblingElement("point");
				}

				TranslacaoTemporizada *t = new TranslacaoTemporizada(time,align,pontosCurva);
				transf.push_back(t);
			}
			else {
				cerr << "Transformação inválida" << endl;
				exit(-1);
			}
		}
		if (strcmp(op->Value(),"rotate") == 0) {
			const char* angleTest = op->Attribute("angle");
			const char* timeTest = op->Attribute("time");

			if (angleTest != nullptr) {
				float angle = stof(angleTest);
				float x1 = stof(op->Attribute("x"));
				float y1 = stof(op->Attribute("y"));
				float z1 = stof(op->Attribute("z"));

				RotacaoEstatica *t = new RotacaoEstatica(angle,x1,y1,z1);
				transf.push_back(t);
			}
			else if (timeTest != nullptr) {
				float time = stof(timeTest);
				float x1 = stof(op->Attribute("x"));
				float y1 = stof(op->Attribute("y"));
				float z1 = stof(op->Attribute("z"));

				RotacaoTemporizada *t = new RotacaoTemporizada(time,x1,y1,z1);
				transf.push_back(t);
			}
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

Cor getColor(XMLElement *color) {
	float difusa[4],ambiente[4],especular[4],emissiva[4],shiny = 0;
	XMLElement* diffuse = color->FirstChildElement("diffuse");
	if (diffuse != nullptr) {
		difusa[0] = stof(diffuse->Attribute("R"));
		difusa[1] = stof(diffuse->Attribute("G"));
		difusa[2] = stof(diffuse->Attribute("B"));
	}
	else {
		difusa[0] = 200;
		difusa[1] = 200;
		difusa[2] = 200;
	}
	difusa[3] = 1;

	XMLElement* ambient = color->FirstChildElement("ambient");
	if (ambient != nullptr) {
		ambiente[0] = stof(ambient->Attribute("R"));
		ambiente[1] = stof(ambient->Attribute("G"));
		ambiente[2] = stof(ambient->Attribute("B"));
	}
	else {
		ambiente[0] = 50;
		ambiente[1] = 50;
		ambiente[2] = 50;
	}
	ambiente[3] = 1;

	XMLElement* specular = color->FirstChildElement("specular");
	if (specular != nullptr) {
		especular[0] = stof(specular->Attribute("R"));
		especular[1] = stof(specular->Attribute("G"));
		especular[2] = stof(specular->Attribute("B"));
	}
	else {
		especular[0] = 0;
		especular[1] = 0;
		especular[2] = 0;
	}
	especular[3] = 1;

	XMLElement* emissive = color->FirstChildElement("emissive");
	if (emissive != nullptr) {
		emissiva[0] = stof(emissive->Attribute("R"));
		emissiva[1] = stof(emissive->Attribute("G"));
		emissiva[2] = stof(emissive->Attribute("B"));
	}
	else {
		emissiva[0] = 0;
		emissiva[1] = 0;
		emissiva[2] = 0;
	}
	emissiva[3] = 1;

	XMLElement* shininess = color->FirstChildElement("shininess");
	if (shininess != nullptr) {
		shiny = stof(shininess->Attribute("value"));
	}
	else {
		shiny = 0;
	}

	return Cor(difusa,ambiente,especular,emissiva,shiny);
}

vector<Modelo> XMLParser::getModelos(XMLNode* models){
	vector<Modelo> modelos;
	XMLElement* model = models->FirstChildElement("model");
	while (model != nullptr) {
		string nameFile = model->Attribute("file"); 
		XMLElement* texture = model->FirstChildElement("texture");
		string textFile = "NO TEXTURE";
		if (texture != nullptr) textFile = texture->Attribute("file");
		XMLElement* cor = model->FirstChildElement("color");
		Cor c;
		if (cor == nullptr) c = Cor();
		else c = getColor(cor);
		Modelo m = Modelo(nameFile,textFile,c);
		modelos.push_back(m);
		model = model->NextSiblingElement("model");
	}
	return modelos;
}


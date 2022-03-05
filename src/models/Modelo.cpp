
class Modelo
{
    public:
    virtual void saveModel(std::ofstream &file) = 0;
    static void writeV(std::ofstream& myFile, float x, float y, float z){
	    myFile << x; myFile << " ";
	    myFile << y; myFile << " ";
	    myFile << z; myFile << "\n";
    }
};

#include "Camara.h"

Camara::Camara(float camX,float camY,float camZ,
                    float camLAX,float camLAY,float camLAZ,
                    float camUPX,float camUPY,float camUPZ,
                    float FOV,float NEAR,float FAR) 
    {
        camPX = camX;
        camPY = camY;
        camPZ = camZ;
        camLX = camLAX;
        camLY = camLAY;
        camLZ = camLAZ;
        camUX = camUPX;
        camUY = camUPY;
        camUZ = camUPZ;
        projFOV = FOV;
        projNEAR = NEAR;
        projFAR = FAR;
    }

Camara::Camara(){}
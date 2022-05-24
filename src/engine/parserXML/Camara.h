#ifndef CAMARA_H
#define CAMARA_H

class Camara {
    public:
        float camPX,camPY,camPZ;
        float camLX,camLY,camLZ;
        float camUX,camUY,camUZ;
        float projFOV,projNEAR,projFAR;
        Camara();
        Camara(float camPX,float camPY,float camPZ,
                float camLX,float camLY,float camLZ,
                float camUX,float camUY,float camUZ,
                float projFOV,float projNEAR,float projFAR);
};

#endif
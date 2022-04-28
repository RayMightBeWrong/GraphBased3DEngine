#ifndef PATCH_H
#define PATCH_H
#include <math.h>
#include <vector>

namespace Modelos
{
    class Patch
    {
        public:
            std::vector<float> pontosControlo;
            std::vector<float> vertices;
            std::vector<int> indices;
            float tesselation;
            Patch(std::vector<float> pontos,float tesselation);
            void buildPatch();

        private:
            void preCalcularMatrix(float res[4][4][3]);
    };

}

#endif
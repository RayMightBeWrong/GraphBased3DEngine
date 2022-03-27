#include <vector>
#include <string>
#include "Grupo.h"

void Grupo::aplicarTransformacoes() {
    for (int i = 0;i < transformacoes.size();i++) {
        (transformacoes[i])->apply();
    }
}

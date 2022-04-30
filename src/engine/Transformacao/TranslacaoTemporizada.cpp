#include "TranslacaoTemporizada.h"

TranslacaoTemporizada::TranslacaoTemporizada(float t, bool a, std::vector<float> pontos){
    tempo = t;
    alinhado = a;
    pontosCurva = pontos;
    nr_pontos = (int) pontosCurva.size() / 3;
    prevY = (float*) malloc(sizeof(float) * 3);
    prevY[0] = 0; prevY[1] = 1; prevY[2] = 0;
}

void TranslacaoTemporizada::apply(float time) {
    float pos[3], deriv[3];
    renderCatmullRomCurve();
    float gt = fmod(time, tempo) / tempo;
    getGlobalCatmullRomPoint(gt, pos, deriv);
    glTranslatef(pos[0], pos[1], pos[2]);

    if (alinhado){
        float x[3] = {deriv[0], deriv[1], deriv[2]};
        normalize(x);

        float z[3];
        cross(x, prevY, z);
        normalize(z);

        float y[3];
        cross(z, x, y);
        normalize(y);
        memcpy(prevY, y, 3 * sizeof(float));

        float m[16];
        buildRotMatrix(x, y, z, m);
        glMultMatrixf(m);
    }
}

void TranslacaoTemporizada::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
    // catmull-rom matrix
    float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
                     { 1.0f, -2.5f,  2.0f, -0.5f},
                     {-0.5f,  0.0f,  0.5f,  0.0f},
                     { 0.0f,  1.0f,  0.0f,  0.0f}};

    for(int i = 0; i < 3; i++){
        float a[4];
        float p[4] = {p0[i], p1[i], p2[i], p3[i]};

        // Compute A = M * P
        multMatrixVector(m, p, a);

        // Compute pos = T * A
        pos[i] = powf(t, 3.0) * a[0] + powf(t, 2.0) * a[1] + t * a[2] + a[3];

        // compute deriv = T' * A
        deriv[i] = 3 * powf(t, 2.0) * a[0] + 2 * t * a[1] + a[2];
    }
}

void TranslacaoTemporizada::renderCatmullRomCurve() {
    float pos[3];
    float deriv[3];

    // draw curve using line segments with GL_LINE_LOOP
    float gt = 0;
    glBegin(GL_LINE_LOOP);
    while(gt < 1){
        getGlobalCatmullRomPoint(gt, pos, deriv);
        glVertex3fv(pos);
        gt += 1.0/100;
    }
    glEnd();
}


void TranslacaoTemporizada::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {
    float t = gt * nr_pontos; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + nr_pontos-1) % nr_pontos;
    indices[1] = (indices[0]+1) % nr_pontos;
    indices[2] = (indices[1]+1) % nr_pontos;
    indices[3] = (indices[2]+1) % nr_pontos;

    float p[4][3] = {{pontosCurva[indices[0] * 3], pontosCurva[indices[0] * 3 + 1], pontosCurva[indices[0] * 3 + 2]},
                     {pontosCurva[indices[1] * 3], pontosCurva[indices[1] * 3 + 1], pontosCurva[indices[1] * 3 + 2]},
                     {pontosCurva[indices[2] * 3], pontosCurva[indices[2] * 3 + 1], pontosCurva[indices[2] * 3 + 2]},
                     {pontosCurva[indices[3] * 3], pontosCurva[indices[3] * 3 + 1], pontosCurva[indices[3] * 3 + 2]}};

    getCatmullRomPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
}


void TranslacaoTemporizada::buildRotMatrix(float *x, float *y, float *z, float *m) {
    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void TranslacaoTemporizada::cross(float *a, float *b, float *res) {
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void TranslacaoTemporizada::normalize(float *a) {
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

void TranslacaoTemporizada::multMatrixVector(float m[4][4], float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }
}

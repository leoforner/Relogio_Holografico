#include "LeituraPots.h"

double LeituraPots::getSetpointRPM() {
    int leitura = analogRead(PIN_SETPOINT);
    // Setpoint de 0 a 1000 RPM
    return map(leitura, 0, 1023, 0, 1000); 
}

void LeituraPots::getGanhosPID(double &kp, double &ki, double &kd) {
    
    // Leitura e Mapeamento dos Ganhos
    double novoKp = map(analogRead(PIN_KP), 0, 1023, 0, (int)(KP_MAX * 100.0)) / 100.0; 
    double novoKi = map(analogRead(PIN_KI), 0, 1023, 0, (int)(KI_MAX * 100.0)) / 100.0;  
    double novoKd = map(analogRead(PIN_KD), 0, 1023, 0, (int)(KD_MAX * 100.0)) / 100.0; 

    // Atualiza apenas se houver mudança significativa
    if (abs(novoKp - _kpAtual) > 0.01 || abs(novoKi - _kiAtual) > 0.01 || abs(novoKd - _kdAtual) > 0.01) {
        _kpAtual = novoKp;
        _kiAtual = novoKi;
        _kdAtual = novoKd;
    }

    // Retorna os valores atuais para o PID no main.cpp
    kp = _kpAtual;
    ki = _kiAtual;
    kd = _kdAtual;
}
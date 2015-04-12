#ifndef CLASSROBO_H
#define CLASSROBO_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "aria.h"
#include "RobotMap.h"
#include "Sonar.h"

#define GirarBase          1
#define ConexaoSerial      1
#define ConexaoRadio       2
#define ConexaoSimulacao   3

#define MATRIX_X_SIZE	100
#define MATRIX_Y_SIZE	100


class PioneerRobot {  
  public:
  ArRobot robot;
  ArSonarDevice sonarDev;
  ArSick   sick;

  ArLaserConnector *laserConnector;
  ArRobotConnector *robotConnector;
  ArArgumentParser *parser;
  ArSimpleConnector *simpleConnector;
  //ArAnalogGyro *gyro; //Not used
  ArSerialConnection con1;

  CRobotMap stMap;

  //int Sensores[8]; Substituido por Objeto CSonar
  CSonar aSonares[8];

  PioneerRobot(int tipoConexao,char* info,int *sucesso);
  
  void destroy();     
  void desconectar();
  void pararMovimento();   
  
  int  getSonar(int i);
  int  isConnected();  
    
  float getXPos();
  float getYPos();
  float getAngBase();
           
  void initMov();
  void Rotaciona(double degrees,int Sentido);
  void getAllSonar(int *sensores);  
  void Move(double vl,double vr);
  void getLaser();
};


#endif
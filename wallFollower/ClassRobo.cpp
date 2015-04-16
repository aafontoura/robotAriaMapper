#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "ClassRobo.h"
#include "aria.h"  
#include "RobotMap.h"

#define REAL 0
  int PioneerRobot::isConnected()
  { return(robot.isConnected());
  }

   
PioneerRobot::PioneerRobot(int tipoConexao,char* info,int *sucesso) {	      

	 int argc=0;char** argv;
	 Aria::init();
	 switch (tipoConexao) 
	 {
	 case ConexaoSerial:
		 {  char port1[4];
		    strcpy(port1,info);
		    
			int ret;	
			std::string str;

            *sucesso=((ret = con1.open(port1))== 0);
            if (*sucesso)
			{ robot.setDeviceConnection(&con1);}
              *sucesso=robot.blockingConnect();
	        break;
		 }
	 case ConexaoRadio:
         { argc=4;
		   argv =(char **) new char[4];
		   argv[0]=new char[4];
		   argv[1]=new char[20];
           argv[2]=new char[20];
		   argv[3]=new char[7];

		   strcpy(argv[0],"-rh");
		   strcpy(argv[1],info);
		   strcpy(argv[2],"-remoteLaserTcpPort");
		   strcpy(argv[3],"10002");

		   parser=new ArArgumentParser(&argc, argv);		   
		   robotConnector=new ArRobotConnector(parser,&robot); 
           *sucesso=robotConnector->connectRobot();
		   if (!(*sucesso))
		   {   Aria::shutdown();break;}
           robot.addRangeDevice(&sick);
           
		   laserConnector=new ArLaserConnector(parser, &robot, robotConnector);	
		   laserConnector->setupLaser(&sick);
           

           break;
		 }
   
     case ConexaoSimulacao:
		  
		 { argc=2;
		   argv =(char **) new char[2];
		  
		   argv[0]=new char[4];
		   argv[1]=new char[20];
          
		   strcpy(argv[0],"-rh");
		   strcpy(argv[1],"localhost");

		   parser=new ArArgumentParser(&argc, argv);
		   
		   robotConnector=new ArRobotConnector(parser,&robot); 
           *sucesso=robotConnector->connectRobot();
		   if (!(*sucesso))
		   {   Aria::shutdown();
			   break;}

		   robot.addRangeDevice(&sick);
		   
		   laserConnector=new ArLaserConnector(parser, &robot, robotConnector);
		   laserConnector->setupLaser(&sick);
           
		 }
	 }
     if (*sucesso)
	 {  robot.addRangeDevice(&sonarDev);
		if (*sucesso)
		{	
		    sick.runAsync();
		    robot.setHeading(0);
			robot.runAsync(true);
			robot.enableMotors();     
			robot.setRotVelMax(10);	
            printf("Connecting...\n");
			if (!laserConnector->connectLaser(&sick))
			{ printf("Could not connect to lasers... exiting\n");
              Aria::exit(2);
            }

			/* initialize sonars data attributes*/
			for (int i = 0; i < NUM_OF_SONARS; i++)
				aSonares[i] = new CSonar(30, i * 180 / 7 - 15 - 75, 5);
	
  
		}
		else Aria::shutdown();
	 }else 	Aria::shutdown();
  }
    
  void PioneerRobot::destroy() { desconectar();Aria::shutdown(); }
  void PioneerRobot::pararMovimento() {   robot.stop(); }
  void PioneerRobot::desconectar()    {  robot.stopRunning(true); }
 
  int PioneerRobot::getSonar(int i)
  { 
	 // Position OwnPos = { getXPos(), getYPos() };
	  //stMap.SetCone(OwnPos, 0, aSonares[i]->GetCone());
	  return(aSonares[i]->GetMeasure()); 

  }

  void PioneerRobot::getAllSonar() 
  { 
	  Position OwnPos = { getXPos() / 100 , getYPos() / 100 };
	  for (int i = 0; i < 8; i++)
	  {

		  aSonares[i]->SetMeasure((int)(robot.getSonarRange(i)));
		  stMap.SetCone(OwnPos, getAngBase(), aSonares[i]->GetCone(), aSonares[i]->GetMeasure()/1000);
	  }
  }

 
  float PioneerRobot::getXPos()     { return   (robot.getX()/10);}
  float PioneerRobot::getYPos()     { return   (robot.getY()/10);}
  float PioneerRobot::getAngBase () { return   (robot.getTh()); }   
  
  void PioneerRobot::initMov()      {  robot.setVel2(50,50);  }
  
  void PioneerRobot::getLaser()
  { sick.getRawReadings();
	std::vector < ArSensorReading > *readings;
    std::vector < ArSensorReading > ::iterator it;

	FILE* dataFile;
    dataFile = fopen("Laser_log.txt", "w");
	

    sick.lockDevice();

    readings = sick.getRawReadingsAsVector();
	if(sick.isConnected())
         fprintf (dataFile, "sim");//,readings->size());
	else fprintf (dataFile, "nao");//,readings->size());
	fprintf (dataFile, "%f 2 \n",readings->size());
    for (it = readings->begin(); it!=readings->end(); it++){
      fprintf( dataFile, " %f %f\n" , (*it).getX(), (*it).getY());//,(*it).get );
    }

 
   sick.unlockDevice();
   fclose ( dataFile );
   ArUtil::sleep(1000);

  

  }

  void PioneerRobot::Rotaciona(double degrees,int Sentido)    
    { robot.setDeltaHeading(degrees);
//	 while (!(robot.isHeadingDone(2))) {};	 	
	 if (Sentido==0)
	     robot.setVel(0);
	 else if (Sentido==1)
	     robot.setVel(50);
	 else if (Sentido==2)
	     robot.setVel(-50);
   }
  void PioneerRobot::Move(double vl,double vr)    
  { robot.setVel2(vl,vr);}
 

  void PioneerRobot::ProcessSonarReading(CSonar sonar)
  {
		Index stSweepSqStart_id, stSweepSqStop_id;
		Position stSweepSqStart_m, stSweepSqStop_m;
		Position GridOrigin;
		Position cellCenter;
		int i, j;
		Index ij;

		stSweepSqStart_m.fX_m = getXPos() - (sonar.Range_m + stMap.cellSize_m);
		stSweepSqStart_m.fY_m = getXPos() - (sonar.Range_m + stMap.cellSize_m);
		stSweepSqStop_m.fX_m = getXPos() + (sonar.Range_m + stMap.cellSize_m);
		stSweepSqStop_m.fY_m = getXPos() + (sonar.Range_m + stMap.cellSize_m);

		// Sweep a square with size 2R_sonar + cellSize around the robot
		stSweepSqStart_id = stMap.PositionToIndex(stSweepSqStart_m);
		stSweepSqStop_id = stMap.PositionToIndex(stSweepSqStop_m);

		// Region1
		for (i = stSweepSqStart_id.iX; stSweepSqStop_id.iX; i++)
		{
			for (j = stSweepSqStart_id.iY; stSweepSqStop_id.iY; j++)
			{
				ij.iX = i;
				ij.iY = j;
				cellCenter = stMap.IndexToPosition(ij);
				/* TODO FERNANDO: CONTINUE FROM HERE
				[bInside, dist, ang] = isInsideSector(robot.x, ...
					robot.y, ...
					sonar.Value - sonar.ToleranceRegion1_m, ...
					sonar.Value + sonar.ToleranceRegion1_m, ...
					robot.phi + sonar.InstallAng_deg + sonar.beta_deg, ...
					robot.phi + sonar.InstallAng_deg - sonar.beta_deg, ...
					cellCenterX, ...
					cellCenterY);

				if bInside
					region1Cells(k).iX = i;
				region1Cells(k).iY = j;
				region1Cells(k).r = dist;
				region1Cells(k).alpha = robot.phi + sonar.InstallAng_deg - ang;
				%region1Cells(k).alpha
					k = k + 1;
				%PlotCellById(i, j, Grid.cellSize);
				end
				*/
			}
		}
  }

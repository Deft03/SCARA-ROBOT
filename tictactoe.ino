int en = 8 ;
int dirPInX = 5 ;
int stepPInX = 2 ;

int dirPInY = 6 ;
int stepPInY = 3 ;

int dirPInZ = 7 ;
int stepPInZ = 4 ;

int sizechess=0, positionchess=0;
int pulseMax = 0; //print to monitor
int pulseMin = 0; //print to monitor
String input="      ";
String siz=" ";
String pos="  ";
char dau;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(en, OUTPUT); // Enable
  
  pinMode(stepPInX, OUTPUT); // Step
  pinMode(dirPInX, OUTPUT); // Dir
  
  pinMode(stepPInZ, OUTPUT); // Step
  pinMode(dirPInZ, OUTPUT); // Dir
  
  pinMode(stepPInY, OUTPUT); // Step
  pinMode(dirPInY, OUTPUT); // Dir

  digitalWrite(en,LOW);
 
 // digitalWrite(dirPInX, LOW); // Set Enable low
  //digitalWrite(dirPInZ, LOW);
}
void loop() {
  Serial.println(" NHAP : SIZ_POS_X(O) (EX: 3_04_X) ");
  while (Serial.available()==0);
  input=Serial.readString();
  siz[0]=input[0];
  pos[0]=input[2];
  pos[1]=input[3];
  dau=input[5];
  sizechess=siz.toInt();
  positionchess=pos.toInt();
  Serial.println(input);
  delay(500);
  if (dau=='X')
  {
    drawX(sizechess,positionchess);
  }
  if (dau=='O')
  {
    drawO(sizechess,positionchess);
  }
  delay(500);
}
///////////// CAC HAM CON
void moveXY(long nStepX, int stepPInX,int dirX, long nStepY, int stepPInY,int dirY)
{

  double nStepMax = nStepX;
  double nStepMin = nStepY;
  int stepPInMax = stepPInX;
  int stepPInMin =  stepPInY;

  double current_axis_min = 0;
  long steps_axis_min = 0;
  double ratio_max_min = 0;

  int pulseMax = 0; //print to monitor
  int pulseMin = 0; //print to monitor

  if (nStepY > nStepX) {
    nStepMax = nStepY;
    nStepMin = nStepX;
    stepPInMax = stepPInY;
    stepPInMin = stepPInX;
  }

  ratio_max_min = nStepMax / nStepMin;
  if( dirX==1)
  {
    digitalWrite(dirPInX, HIGH); 
  }
  else
  {
    digitalWrite(dirPInX, LOW); 
  }

 if( dirY==1)
  {
    digitalWrite(dirPInY, HIGH); 
  }
  else
  {
    digitalWrite(dirPInY, LOW); 
  }

 //    Serial.println("nStepMax");
 //     Serial.println(nStepMax);
 //     Serial.println("day la dpY" );
//     Serial.println(dpY);
     
  for (int i = 1 ; i <= nStepMax ; i=i+1 ) {
    current_axis_min = i / ratio_max_min;

    if (current_axis_min - steps_axis_min >= 1) {
      digitalWrite(stepPInMin, HIGH);
      pulseMin = 1;
      steps_axis_min++;
    }

    digitalWrite(stepPInMax, HIGH);
    pulseMax = 1;
    delay(1);

    digitalWrite(stepPInMax, LOW);
    digitalWrite(stepPInMin, LOW);
    pulseMax = 0;
    pulseMin = 0;
    delay(1);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void backhome(double t1,double t2)
{ 
      double dpX=0,dpY=0;
      int dirX=0,dirY=0;
      dpX=(abs(t1)*(180/PI))/(1.8/16);
      dpY=(abs(t2)*(180/PI))/(1.8/16);
      if (t1<0)
      {
           dirX=1;
      }
      else
      {
          dirX=0;
      }
      
       if (t2<0)
      {
           dirY=1;
      }
      else
      {
          dirY=0;
      }
     dpY=int(2*dpY);
     dpX=int(11*dpX);
     moveXYhome(dpX,stepPInX,dirX, dpY, stepPInY,dirY);
     delay(500);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawO(int siz,int pos)
{
   int hang = ceil(float(pos)/siz);
   int cot= pos%siz;
   if(cot==0)
   {
    cot=siz;
   }
   float tamX=cot*(30/float(siz))-(float(30/(2*siz)));
   float tamY=(siz+1-hang)*(30/float(siz))-30/(float(2*siz));
   float R= 0.65*float(30/(2*siz));

//    Serial.println("tamX");
//     Serial.println(tamX);
//     Serial.println("tamY");
//      Serial.println(tamY);
//       Serial.println("R");
//        Serial.println(R);

  int dirX=0,dirY=0;
  float l1=21;
  float l2=25;
  double temp1=0,temp2=0,px=0,py=0,c1=0,s1=0,c2=0,s2=0;
  double t1=0,t2=0,dpX=0,dpY=0;
  
  for (double t = 0 ; t <= 2*PI + 0.1; t = t + 0.5)
  {   

      if (t==0.5)
      {   
          lenxuongZ(hang,0);
      }
      px=tamX + R*cos(t)-15;
      py=tamY + R*sin(t)+12;
      c2=((px*px+py*py-l1*l1-l2*l2))/(2*l1*l2);
      s2=sqrt(abs(1-c2*c2));
      c1=px*(l1+l2*c2)+py*l2*s2;
      s1=py*(l1+l2*c2)-px*l2*s2;
      t1=atan(s1/c1);
      t2=atan(s2/c2);
       if (c2<0)
      {
        t2=PI+t2;
      }

      if (c1<0)
      {
        t1=PI+t1;
      }
      dpX=(abs(t1-temp1)*(180/PI))/(1.8/16);
      dpY=(abs(t2-temp2)*(180/PI))/(1.8/16);
      if ((t1-temp1)>0)
      {
           dirX=1;
      }
      else
      {
          dirX=0;
      }
      
       if ((t2-temp2)>0)
      {
           dirY=1;
      }
      else
      {
          dirY=0;
      }

     dpY=int(2*dpY);
     dpX=int(11*dpX);
     if(t<=0.5)
     {
        moveXYhome(dpX,stepPInX,dirX, dpY, stepPInY,dirY);
     }
     else
     {
       moveXY(dpX,stepPInX,dirX, dpY, stepPInY,dirY);
     }
     temp1=t1;
     temp2=t2;
  }
  delay(500);

   lenxuongZ(hang,1);
  
  backhome(temp1,temp2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawline(float XA,float YA,float XB,float YB)
{

      int dirX=0,dirY=0;
      float l1=21;
      float l2=25;
      double temp1=0,temp2=0,px=0,py=0,c1=0,s1=0,c2=0,s2=0;
      double t1=0,t2=0,dpX=0,dpY=0;

      px=XA-15 ;
      py=YA+12 ;
      c2=((px*px+py*py-l1*l1-l2*l2))/(2*l1*l2);
      s2=sqrt(abs(1-c2*c2));
      c1=px*(l1+l2*c2)+py*l2*s2;
      s1=py*(l1+l2*c2)-px*l2*s2;
      t1=atan(s1/c1);
      t2=atan(s2/c2);
       if (c2<0)
      {
        t2=PI+t2;
      }
        if (c1<0)
      {
        t1=PI+t1;
      }
      temp1=t1;
      temp2=t2;
    for (double t = 0 ; t <= 1 ; t = t + 0.1)
  {   
    
      px=XA + (XB-XA)*t-15;
      py=YA + (YB-YA)*t+12;
      c2=((px*px+py*py-l1*l1-l2*l2))/(2*l1*l2);
      s2=sqrt(abs(1-c2*c2));
      c1=px*(l1+l2*c2)+py*l2*s2;
      s1=py*(l1+l2*c2)-px*l2*s2;
      t1=atan(s1/c1);
      t2=atan(s2/c2);
       if (c2<0)
      {
        t2=PI+t2;
      }
      if (c1<0)
      {
        t1=PI+t1;
      }
      dpX=(abs(t1-temp1)*(180/PI))/(1.8/16);
      dpY=(abs(t2-temp2)*(180/PI))/(1.8/16);
      if ((t1-temp1)>0)
      {
           dirX=1;
      }
      else
      {
          dirX=0;
      }
      
       if ((t2-temp2)>0)
      {
           dirY=1;
      }
      else
      {
          dirY=0;
      }

     dpY=int(2*dpY); 
     dpX=int(11*dpX);
     moveXY(dpX,stepPInX,dirX, dpY, stepPInY,dirY);
     temp1=t1;
     temp2=t2;
  }  
  delay(500);     
}

void drawX(int siz,int pos)
{
 
   int hang = ceil(float(pos)/siz);
   int cot= pos%siz;
   if(cot==0)
   {
    cot=siz;
   }
   float tamX=cot*(30/float(siz))-(float(30/(2*siz)));
   float tamY=(siz+1-hang)*(30/float(siz))-30/(float(2*siz));
   float d= 0.6*float(30/(2*siz));

   float XA=tamX-d;
   float XB=tamX+d;
   float XC=tamX+d;
   float XD=tamX-d;
   
   float YA=tamY+d;
   float YB=tamY-d;
   float YC=tamY+d;
   float YD=tamY-d;


//////////////////////////////////////////////////////////////////////////
  int dirX=0,dirY=0;
  float l1=21;
  float l2=25;
  double temp1=0,temp2=0,px=0,py=0,c1=0,s1=0,c2=0,s2=0;
  double t1=0,t2=0,dpX=0,dpY=0;
  
  for (double t = 0 ; t <= 1 ; t = t + 0.1)
  {   

      if (t==0.1)
      {   
         lenxuongZ(hang,0);
      }
      px=XA + (XB-XA)*t-15;
      py=YA + (YB-YA)*t+12;
      c2=((px*px+py*py-l1*l1-l2*l2))/(2*l1*l2);
      s2=sqrt(abs(1-c2*c2));
      c1=px*(l1+l2*c2)+py*l2*s2;
      s1=py*(l1+l2*c2)-px*l2*s2;
      t1=atan(s1/c1);
      t2=atan(s2/c2);
       if (c2<0)
      {
        t2=PI+t2;
      }
       if (c1<0)
      {
        t1=PI+t1;
      }
      dpX=(abs(t1-temp1)*(180/PI))/(1.8/16);
      dpY=(abs(t2-temp2)*(180/PI))/(1.8/16);
      if ((t1-temp1)>0)
      {
           dirX=1;
      }
      else
      {
          dirX=0;
      }
      
       if ((t2-temp2)>0)
      {
           dirY=1;
      }
      else
      {
          dirY=0;
      }
       dpY=int(2*dpY);
       dpX=int(11*dpX);
     if(t<=0.1)
     {
        moveXYhome(dpX,stepPInX,dirX, dpY, stepPInY,dirY);
     }
     else
     {
       moveXY(dpX,stepPInX,dirX, dpY, stepPInY,dirY);
     }
     temp1=t1;
     temp2=t2;
  }
   delay(500); 
   lenxuongZ(hang,1);
   drawline(XB,YB,XC,YC);
   lenxuongZ(hang,0);
   drawline(XC,YC,XD,YD);
   digitalWrite(dirPInZ, LOW); 
   lenxuongZ(hang,1);
    
  //////////////////////////////////////////////////////////////
      px=XD-15 ;
      py=YD+12 ;
      c2=((px*px+py*py-l1*l1-l2*l2))/(2*l1*l2);
      s2=sqrt(abs(1-c2*c2));
      c1=px*(l1+l2*c2)+py*l2*s2;
      s1=py*(l1+l2*c2)-px*l2*s2;
      t1=atan(s1/c1);
      t2=atan(s2/c2);
       if (c2<0)
      {
        t2=PI+t2;
      }
      if (c1<0)
      {
        t1=PI+t1;
      }
      temp1=t1;
      temp2=t2;
    
 backhome(temp1,temp2);
  
}



////////////////////////////////////////////////////////////////////////////////////
void moveXYhome(long nStepX, int stepPInX,int dirX, long nStepY, int stepPInY,int dirY)
{

  double nStepMax = nStepX;
  double nStepMin = nStepY;
  int stepPInMax = stepPInX;
  int stepPInMin = stepPInY;

  double current_axis_min = 0;
  long steps_axis_min = 0;
  double ratio_max_min = 0;

  int pulseMax = 0; //print to monitor
  int pulseMin = 0; //print to monitor

  if (nStepY > nStepX) {
    nStepMax = nStepY;
    nStepMin = nStepX;
    stepPInMax = stepPInY;
    stepPInMin = stepPInX;
  }

  ratio_max_min = nStepMax / nStepMin;
  if( dirX==1)
  {
    digitalWrite(dirPInX, HIGH); 
  }
  else
  {
    digitalWrite(dirPInX, LOW); 
  }

 if( dirY==1)
  {
    digitalWrite(dirPInY, HIGH); 
  }
  else
  {
    digitalWrite(dirPInY, LOW); 
  }

   //  Serial.println("nStepMax");
  //    Serial.println(nStepMax);
//      Serial.println("day la dpY" );
//      Serial.println(dpY);
     
  for (int i = 1 ; i <= nStepMax ; i = i + 1) {
    current_axis_min = i / ratio_max_min;

    if (current_axis_min - steps_axis_min >= 1) {
      digitalWrite(stepPInMin, HIGH);
      pulseMin = 1;
      steps_axis_min++; 
    }

    digitalWrite(stepPInMax, HIGH);
    pulseMax = 1;
    delay(0.5);

    digitalWrite(stepPInMax, LOW);
    digitalWrite(stepPInMin, LOW);
    pulseMax = 0;
    pulseMin = 0;
    delay(1);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// chieu=0 la di z di xuong
void lenxuongZ(int vitrihang,int chieu)
  {
    int soxung = 3200;
  /*  int soxung;
    if (vitrihang==1)
      {3
        soxung=500;
      }
    
    if (vitrihang==2)
      {M
        soxung=500;
      }
    if (vitrihang==3)
      {
        soxung=500;
      }  */
  
    if(chieu==0)
    {
        digitalWrite(dirPInZ, HIGH); 
        for (int i=1;i<=soxung;i++)
       {
        digitalWrite(stepPInZ,HIGH);
        delay(0.1);
        digitalWrite(stepPInZ,LOW);
        delay(1);
       }        
    }
    else
    {
        digitalWrite(dirPInZ, LOW);
         for (int i=1;i<=soxung;i++)
       {
        digitalWrite(stepPInZ,HIGH);
        delay(0.1);
        digitalWrite(stepPInZ,LOW);
        delay(1);
       } 
    }
     
}

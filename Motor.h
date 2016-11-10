#ifndef Motor_H
#define Motor_H

class Motor
{
  public:
    Motor(byte pin1, byte pin2, byte pin3, byte pin4);
    void RunForward(int obor, int dl);
    void RunBack(int obor, int dl);
  private:
    byte in1; //in1 on drive
    byte in2; //in2 on drive
    byte in3; //in3 on drive
    byte in4; //in4 on drive
};


#endif

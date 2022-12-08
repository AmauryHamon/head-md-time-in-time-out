/*
 TouchWheel.pde
 MPR121 WhellPad Example Code
 
 by:Waiman Zhao
 Mail:Binpower@foxmail.com
 created on: 11/2/14
 license: CC-SA 3.0
 
 Hardware: 3.3V Arduino Pro Mini
           SDA -> A4
           SCL -> A5
           IRQ -> D2
*/


#include 
#include 

int key = 0;


// =========  setup  =========
void setup()
{ 
	//  initialize function
  Serial.begin(19200);
  Wire.begin();
  CapaTouch.begin();

  delay(500);
  Serial.println("START"); 
}


// =========  loop  =========
void loop()
{
   key=CapaTouch.keyPad();
 
  if (key==1)             
  { Serial.print("wheel:");
  Serial.println("0");
  }
   if (key==4)
  { Serial.print("wheel:");
  Serial.println("1");
  }
   if (key==7)
  { Serial.print("wheel:");
  Serial.println("2");
  }
   if (key==11)
  { Serial.print("wheel:");
  Serial.println("3");
  }
   if (key==2)
  { Serial.print("wheel:");
  Serial.println("4");
  }
   if (key==5)
  { Serial.print("wheel:");
  Serial.println("5");
  }
  
   if (key==8)
  { Serial.print("wheel:");
  Serial.println("6");
  }
   if (key==0)
  { Serial.print("wheel:");
  Serial.println("7");
  }
   if (key==3)
  { Serial.print("wheel:");
  Serial.println("8");
  }
	delay(200);
}
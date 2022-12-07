//ArrayList<Circle> circles = new ArrayList<Circle>();

void setup() {
  size(900, 900);
  background(0);

  float amount = 32;
  float step = 360 / amount;
  int elsize = 40;
  int dist = 300;

  translate(width/2, height/2);
  
  noStroke();
  
  for (int i = 0; i < amount; i++) {
    fill(#f1f1f1);
    pushMatrix();
    rotate(radians(i*step));
    ellipse(0, dist, elsize, elsize);
    popMatrix();
  }
  amount = 24;
  step = 360 / amount;
  dist -= 60;
  
  for (int i = 0; i < amount; i++) {
    fill(#f1f1f1);
    pushMatrix();
    rotate(radians(i*step));
    ellipse(0, dist, elsize, elsize);
    popMatrix();
  }
  amount = 16;
  step = 360 / amount;
  dist -= 60;

  for (int i = 0; i < amount; i++) {
    fill(#f1f1f1);
    pushMatrix();
    rotate(radians(i*step));
    ellipse(0, dist, elsize, elsize);
    popMatrix();
  }
  amount = 12;
  step = 360 / amount;
  dist -= 60;
  for (int i = 0; i < amount; i++) {
    fill(#f1f1f1);
    pushMatrix();
    rotate(radians(i*step));
    ellipse(0, dist, elsize, elsize);
    popMatrix();
  }
  amount = 8;
  step = 360 / amount;
  dist -= 60;
  position = 0;
  for (int i = 0; i < amount; i++) {
    fill(#f1f1f1);
    pushMatrix();
    rotate(radians(i*step));
    ellipse(0, dist, elsize, elsize);
    popMatrix();
  }
  dist -= 60;
  ellipse(0, dist, elsize, elsize);

  save("LED.png");  
}

void draw() {
  //if (frameCount%5==0){
  //  circles.add(new Circle());
  //}
  
}
  

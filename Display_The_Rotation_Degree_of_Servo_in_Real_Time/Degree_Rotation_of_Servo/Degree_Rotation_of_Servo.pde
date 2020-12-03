import processing.serial.*;
Serial myport;
PFont font_Text;


float a,b,h;
float size = 38.0;
int head, receiving_value,i  ;




void setup() {
size(700,400,OPENGL);

//myport= new Serial (this,Serial.list()[0],115200);
//println(Serial.list());
//myport.bufferUntil('\n');
  font_Text = createFont("Arial bold",15,false);


}
void draw() {
  
  background(5);
  



  stroke(255);
  a=radians(i);
  b=radians(180 + i);
  h=radians(head);


  fill(255,255,127);
  textFont(font_Text);
  noFill();
  rect(250,57, 190,30,7);
  text("Rotation Degree of Servo",255, 78);
  


   fill(255);
i = MAP(receiving_value, 30,125, 0, 200);
  text((int)i+"°", 335, 150);
    noFill();
  rect(495,125, 140,40,7);
  text("Pulse Width : "+receiving_value+"%", 500, 150);
 
   fill(255);
  translate(350,200);
  fill(0, 57, 230,63);
  stroke(255); // couleur bordure de ellipse
  ellipse(0,0,166,166);
  rotate(-b);
  fill(255,255,127);
  textFont(font_Text);
  strokeWeight(1.5);
  stroke(127,127,127);
  line(-30,1,30,1);
  stroke(255,255,255);
 line(-30,0,30,0);line(-30,0,-20-size/6 ,size/6);line(-30,0,-20-size/6 ,-size/6);  


}

void serialEvent (Serial myport){
String value = myport.readStringUntil ('\n');

if ( value != null){
    value = trim(value) ;

    String[] input =split(value,' ');
    
if (input.length >0 ){
    receiving_value = int (input[0]);
    
      println(receiving_value);
}
}
}

int MAP(int IN, int INmin, int INmax, int OUTmin, int OUTmax)
{
    return ((((IN - INmin)*(OUTmax - OUTmin))/(INmax -INmin)) + OUTmin);
}

import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import java.awt.event.KeyEvent; 
import java.io.IOException; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class ArduinoRadarProgram extends PApplet {

    /*   Arduino Radar Project
     */
     
    
    
    Serial myPort; 
  
    String angle="";
    String distance="";
    String data="";
    String noObject;
    float pixsDistance;
    int iAngle, iDistance;
    int index1=0;
    int index2=0;
    PFont orcFont;
    public void setup() {
      
      // **EKRAN \u00c7\u00d6Z\u00dcN\u00dcRL\u00dc\u011e\u00dcN\u00dcZ\u00dc BURADAN DE\u011e\u0130\u015eT\u0130R\u0130N !!!!!!! ***
     
     myPort = new Serial(this,"COM4", 9600); // Seri ileti\u015fimi ba\u015flat\u0131r
     myPort.bufferUntil('.'); 
     orcFont = loadFont("OCRAExtended-30.vlw");
    }
    public void draw() {
      
      fill(98,245,31);
      textFont(orcFont);
  
      noStroke();
      fill(0,4); 
      rect(0, 0, width, height-height*0.065f); 
      
      fill(98,245,31); 
  
      drawRadar(); 
      drawLine();
      drawObject();
      drawText();
    }
    public void serialEvent (Serial myPort) { 
      data = myPort.readStringUntil('.');
      data = data.substring(0,data.length()-1);
      
      index1 = data.indexOf(","); 
      angle= data.substring(0, index1); 
      distance= data.substring(index1+1, data.length()); 
      
     
      iAngle = PApplet.parseInt(angle);
      iDistance = PApplet.parseInt(distance);
    }
    public void drawRadar() {
      pushMatrix();
      translate(width/2,height-height*0.074f); 
      noFill();
      strokeWeight(2);
      stroke(98,245,31);
      // draws the arc lines
      arc(0,0,(width-width*0.0625f),(width-width*0.0625f),PI,TWO_PI);
      arc(0,0,(width-width*0.27f),(width-width*0.27f),PI,TWO_PI);
      arc(0,0,(width-width*0.479f),(width-width*0.479f),PI,TWO_PI);
      arc(0,0,(width-width*0.687f),(width-width*0.687f),PI,TWO_PI);
      // draws the angle lines
      line(-width/2,0,width/2,0);
      line(0,0,(-width/2)*cos(radians(30)),(-width/2)*sin(radians(30)));
      line(0,0,(-width/2)*cos(radians(60)),(-width/2)*sin(radians(60)));
      line(0,0,(-width/2)*cos(radians(90)),(-width/2)*sin(radians(90)));
      line(0,0,(-width/2)*cos(radians(120)),(-width/2)*sin(radians(120)));
      line(0,0,(-width/2)*cos(radians(150)),(-width/2)*sin(radians(150)));
      line((-width/2)*cos(radians(30)),0,width/2,0);
      popMatrix();
    }
    public void drawObject() {
      pushMatrix();
      translate(width/2,height-height*0.074f); 
      strokeWeight(9);
      stroke(255,10,10); 
      pixsDistance = iDistance*((height-height*0.1666f)*0.025f); 
    
      if(iDistance<40){
     
      line(pixsDistance*cos(radians(iAngle)),-pixsDistance*sin(radians(iAngle)),(width-width*0.505f)*cos(radians(iAngle)),-(width-width*0.505f)*sin(radians(iAngle)));
      }
      popMatrix();
    }
    public void drawLine() {
      pushMatrix();
      strokeWeight(9);
      stroke(30,250,60);
      translate(width/2,height-height*0.074f);
      line(0,0,(height-height*0.12f)*cos(radians(iAngle)),-(height-height*0.12f)*sin(radians(iAngle))); // draws the line according to the angle
      popMatrix();
    }
    public void drawText() {
      
      pushMatrix();
      if(iDistance>40) {
      noObject = "Out of Range";
      }
      else {
      noObject = "In Range";
      }
      fill(0,0,0);
      noStroke();
      rect(0, height-height*0.0648f, width, height);
      fill(98,245,31);
      textSize(25);
      
      text("10cm",width-width*0.3854f,height-height*0.0833f);
      text("20cm",width-width*0.281f,height-height*0.0833f);
      text("30cm",width-width*0.177f,height-height*0.0833f);
      text("40cm",width-width*0.0729f,height-height*0.0833f);
      textSize(40);
      text("Object: " + noObject, width-width*0.875f, height-height*0.0277f);
      text("Angle: " + iAngle +" \u00b0", width-width*0.48f, height-height*0.0277f);
      text("Distance: ", width-width*0.26f, height-height*0.0277f);
      if(iDistance<40) {
      text("        " + iDistance +" cm", width-width*0.225f, height-height*0.0277f);
      }
      textSize(25);
      fill(98,245,60);
      translate((width-width*0.4994f)+width/2*cos(radians(30)),(height-height*0.0907f)-width/2*sin(radians(30)));
      rotate(-radians(-60));
      text("30\u00b0",0,0);
      resetMatrix();
      translate((width-width*0.503f)+width/2*cos(radians(60)),(height-height*0.0888f)-width/2*sin(radians(60)));
      rotate(-radians(-30));
      text("60\u00b0",0,0);
      resetMatrix();
      translate((width-width*0.507f)+width/2*cos(radians(90)),(height-height*0.0833f)-width/2*sin(radians(90)));
      rotate(radians(0));
      text("90\u00b0",0,0);
      resetMatrix();
      translate(width-width*0.513f+width/2*cos(radians(120)),(height-height*0.07129f)-width/2*sin(radians(120)));
      rotate(radians(-30));
      text("120\u00b0",0,0);
      resetMatrix();
      translate((width-width*0.5104f)+width/2*cos(radians(150)),(height-height*0.0574f)-width/2*sin(radians(150)));
      rotate(radians(-60));
      text("150\u00b0",0,0);
      popMatrix(); 
    }
  public void settings() {  size (1920, 1080);  smooth(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "ArduinoRadarProgram" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}

size(640,480);
print(PFont.list());
PFont myFont=createFont("微軟正黑體",32);
//PFont font = loadFont("新細明體.TTF");
stroke(0);
textFont(myFont, 50);
fill(#FF5E00);
text("微軟正黑體", 10, 50);

noStroke();
circle(width/2,height/2,55);

PImage photo;
photo = loadImage("piano-r.jpg");
image(photo, 0,0,width, height);

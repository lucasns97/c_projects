# projects
Gnuplot assistant for C++

# author: Lucas Nunes Sequeira, Brasil

# date: October 15, 2018

This is a open source assitent file for C++ gnuplot graphics.
Usage:
  1. import library
    >> #include gnuplotassist.h
    
  2. declare a variable that has Graphic type:
    >> Graphic points;
    
  3. use the prototype functions to add curves, change labels, change title etc.\n
    >> points.title('Avaliation of market');\n
    >> points.xlabel('time (years)');\n
    >> points.ylabel('profit (dollars)');\n
    >> points.addcurve('dataset', dataVec);\n
    
    obs: in this case the parameters sent are a string witch contains the name of the curve
         'dataset' and a vactor of double pair, that has the (x,y) points to plot; for more
          types of headers access the gnuplotassist.h
          
  4. plot the graphic
    >> points.plot();

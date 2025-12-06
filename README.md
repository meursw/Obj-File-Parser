# Object File Parser for loading 3D models into a graphics engine.
Simple parser program that converts an .obj file  to the format used in this tutorial: https://www.rastertek.com/dx11win10tut07.html

Used blender 4.0 to export a 3D model and generate an .obj file.
The .obj should only use:  - UV Coordinates  - Normals be triangulated and have Z+.

Not the most efficient or robust parser but it gets the job done for these tutorials.
I may improve this program in the future.

Output example of parser:

```
Vertex Count: 5268

Data:

-0.0515 1.82012 -0.085943 0.074297 0.898303 -0.3295 -0.5072 -0.7964 
-0.305322 1.90229 -0.033242 0.12902 0.924799 -0.3295 -0.5072 -0.7964 
-0.058663 1.89443 -0.130303 0.072753 0.927554 -0.3295 -0.5072 -0.7964 
-0.489041 1.49934 0.190742 0.141898 0.815678 -0.9182 0.1335 -0.3731 
-0.3773 1.64829 -0.030973 0.089641 0.854422 -0.9182 0.1335 -0.3731 
-0.394228 1.49185 -0.045294 0.090524 0.814987 -0.9182 0.1335 -0.3731 
-0.271869 0.856991 0.146595 0.062327 0.748268 -0.8535 -0.5067 -0.1218 
-0.348805 1.03361 -0.049013 0.073543 0.771615 -0.8535 -0.5067 -0.1218 
-0.262774 0.883013 -0.025371 0.06183 0.767801 -0.8535 -0.5067 -0.1218
...
```

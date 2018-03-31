# raytra

Simple raytracing renderer that reads in a scene file and outputs a photorealistic image in OpenEXR format.

### Geometry supported:
* Sphere
* Triangle
* Plane
* .obj files
Input file format shown in test files.


### How to compile and run
On mac, compile using this command:

```g++ -g *.cc -I. -I/usr/local/include/OpenEXR -L/usr/local/lib -lIlmImf -lImath -lHalf -o raytra```

Run by typing in Terminal:
```./raytra [scenefile_name.txt] [output_file_name.exr]```


### Sample Images:
![Alt text](./cg_11.png?raw=true "Title")
![Alt text](./b33_.png?raw=true "Title")
![Alt text](./st33.png?raw=true "Title")

Note: Many parts of the code are starter code provided by the Computer Graphics Course at Columbia University. 

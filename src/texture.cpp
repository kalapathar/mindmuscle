// by Olaf Hall-Holt, 2009
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<cassert>
#include<string.h>  // for strcmp
#include<stdlib.h>  // for exit
#include<math.h>    // for cos, sin
#include"texture.h"

struct pixel {
  unsigned char red, green, blue, alpha;
};

class Image {
  unsigned width, height, depth;
  pixel *data;
  void assertInImage(unsigned x, unsigned y)
          { assert(x < width); assert(y < height); }

public:
  Image(unsigned w, unsigned h, unsigned d);
  Image(const char *fname);

  unsigned getWidth() { return width; }
  unsigned getHeight() { return height; }
  pixel *getData() { return data; }
  pixel getPixel(unsigned x, unsigned y)
            { assertInImage(x,y); return data[y*width+x]; }
  void setPixel(unsigned x, unsigned y, pixel col )
            { assertInImage(x,y);  data[y*width+x] = col; }
  void print();
};

Image::Image(unsigned w, unsigned h, unsigned d)
{
  width = w;
  height = h;
  depth = d;
  data = new pixel[width*height];
}

Image::Image(const char *fname)
{
  ifstream f(fname);
  if ( ! f.good() ) {
    cerr << "Error:  could not open file " << fname << endl;
    exit(-1);
  }
  string hdr;
  f >> hdr;
  if ( (hdr != "P6") && (hdr != "P7") ) {
    cerr << "Error:  invalid header type-- expecting P6 or P7, but got " << hdr << endl;
    exit(-1);
  }
  f >> ws;  // special function of istream to get rid of whitespace
  while ( f.peek() == '#' ) f.ignore(1024, '\n');
  int maxval = 0;
  if ( hdr == "P6" ) {
    depth = 3;
    f >> width >> height;
    f >> maxval;
    f.get();
  } else { // P7
/*  Example header:
	P7
	WIDTH 200
	HEIGHT 200
	DEPTH 2
	MAXVAL 255
	TUPLTYPE GRAYSCALE_ALPHA
	ENDHDR
*/
    string keyword, tupletype;
    f >> keyword;
    int counter = 0;
    while ( keyword != "ENDHDR" && ++counter < 100 ) {
      if ( keyword == "WIDTH" ) f >> width;
      else if ( keyword == "HEIGHT" ) f >> height;
      else if ( keyword == "DEPTH" ) f >> depth;
      else if ( keyword == "MAXVAL" ) f >> maxval;
      else if ( keyword == "TUPLTYPE" ) f >> tupletype; // ignored
      else {
        cerr << "Error:  unrecognized keyword in PAM image header: " << keyword << " exiting." << endl;
        exit(-1);
      }
      f >> keyword;
    }
    if ( "ENDHDR" != keyword ) {
      cerr << "Error reading image file, perhaps the header is not correctly formed?" << endl;
      exit(-1);
    }
    f.get();
  }
  if ( 255 != maxval ) {
    cerr << "Error:  invalid maxval of " << maxval << " for incoming image (expected 255).  To fix, use convert with -depth 8." << endl;
    exit(-1);
  }
  data = new pixel[width*height];
  if ( 1 == depth ) { // assume grey
    for ( unsigned i = 0; i < width*height; ++i ) {
      data[i].red = data[i].green = data[i].blue = f.get();
      data[i].alpha = 255;
    }
  } else if ( 2 == depth ) { // assume grey and alpha
    for ( unsigned i = 0; i < width*height; ++i ) {
      data[i].red = data[i].green = data[i].blue = f.get();
      data[i].alpha = f.get();
    }
  } else if ( 3 == depth ) { // assume RGB
    for ( unsigned i = 0; i < width*height; ++i ) {
      data[i].red = f.get();
      data[i].green = f.get();
      data[i].blue = f.get();
      data[i].alpha = 255;
    }
  } else if ( 4 == depth ) { // assume RGBA
    f.read( (char *) data, width*height*sizeof(pixel) );
  } else {
    cerr << "Error:  invalid depth of " << depth << " for incoming image (expected 1, 2, 3, or 4)." << endl;
    exit(-1);
  }
  if ( false ) {
    // assume the alpha is backwards, so invert it?  (prior version of convert)
    for ( unsigned i = 0; i < width*height; ++i )
      data[i].alpha = 255 - data[i].alpha;
  }
  f.close();
}

void Image::print()
{
  if ( 3 == depth ) { // assume it was a PPM
    cout << "P6" << endl;
    cout << width << " " << height << endl;
    cout << 255 << endl;
    for ( unsigned i = 0; i < width*height; ++i ) {
      cout.put( data[i].red );
      cout.put( data[i].green );
      cout.put( data[i].blue );
    }
  } else { // assume it was a PAM
    cout << "P7" << endl;
    cout << "WIDTH " << width << endl;
    cout << "HEIGHT " << height << endl;
    cout << "DEPTH " << depth << endl;
    cout << "MAXVAL 255" << endl;
    if ( 2 == depth ) cout << "TUPLTYPE GRAYSCALE_ALPHA" << endl;
    else cout << "TUPLTYPE RGB_ALPHA" << endl;
    cout << "ENDHDR" << endl;
    if ( 2 == depth ) {
      for ( unsigned i = 0; i < width*height; ++i ) {
        cout.put( data[i].green );
        cout.put( data[i].alpha );
      }
    } else cout.write( (char *) data, width*height*sizeof(pixel) );
  }
}

struct Texture {
  map<int, unsigned> win2id;  // id(s) of this texture, indexed by window id
  int TEX_WIDTH, TEX_HEIGHT; // actual size of the texture map (2^n)
  pixel *imgData; // pixels in the image
  float widthRatio, heightRatio; // how much of the actual size is used
  Texture(const char *filename); // read in an image file
  Texture(const Texture &t) : win2id(t.win2id),
                              TEX_WIDTH(t.TEX_WIDTH),
                              TEX_HEIGHT(t.TEX_HEIGHT),
                              widthRatio(t.widthRatio),
                              heightRatio(t.heightRatio) {
    imgData = new pixel[TEX_WIDTH*TEX_HEIGHT];
    for ( int i=0; i<TEX_WIDTH*TEX_HEIGHT; ++i )
      imgData[i] = t.imgData[i]; }
  Texture& operator=(const Texture &t) {
    delete [] imgData;
    win2id = t.win2id;
    widthRatio = t.widthRatio;
    heightRatio = t.heightRatio;
    imgData = new pixel[TEX_WIDTH*TEX_HEIGHT];
    for ( int i=0; i<TEX_WIDTH*TEX_HEIGHT; ++i )
      imgData[i] = t.imgData[i];
    return *this;
  }
  ~Texture() { 
    cout << "Free Texture" << endl;
    delete [] imgData; }
  int moveImgDataToGraphicsCard();
};

#if 0
struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};
#endif

vector<Texture> globalTexture;
map<const string, int> textureFileLookup;

pair<double, double> rotatePt(double x0, double y0, double x, double y, double theta)
{
  double dx = x - x0;
  double dy = y - y0;
  double xp = dx*cos(theta) + dy*sin(theta);
  double yp = -dx*sin(theta) + dy*cos(theta);
  return pair<double,double>( x0+xp, y0+yp );
}

void drawTexture(int texNum, double x, double y, double width, double height, double alpha, double rotationAngle)
{
  glEnable(GL_TEXTURE_2D);
  int windowID = glutGetWindow();
  glBindTexture(GL_TEXTURE_2D, globalTexture[texNum].win2id[windowID]);
  double widthRatio = globalTexture[texNum].widthRatio;
  double heightRatio = globalTexture[texNum].heightRatio;
  glColor4f(1.0, 1.0, 1.0, alpha);
  if ( 0 == rotationAngle ) {
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);                    glVertex2f(x, y);
      glTexCoord2f(widthRatio, 0);           glVertex2f(x + width, y);
      glTexCoord2f(widthRatio, heightRatio); glVertex2f(x + width, y + height);
      glTexCoord2f(0, heightRatio);          glVertex2f(x, y + height);
    glEnd();
  } else {
    // compute the result of rotating around the center of this box
    double x0 = x + 0.5*width, y0 = y + 0.5*height;
    pair<double,double> p0 = rotatePt(x0, y0, x, y, rotationAngle);
    pair<double,double> p1 = rotatePt(x0, y0, x+width, y, rotationAngle);
    pair<double,double> p2 = rotatePt(x0, y0, x+width, y+height, rotationAngle);
    pair<double,double> p3 = rotatePt(x0, y0, x, y+height, rotationAngle);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);                    glVertex2f(p0.first, p0.second);
      glTexCoord2f(widthRatio, 0);           glVertex2f(p1.first, p1.second);
      glTexCoord2f(widthRatio, heightRatio); glVertex2f(p2.first, p2.second);
      glTexCoord2f(0, heightRatio);          glVertex2f(p3.first, p3.second);
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}
void drawTexture(int texNum, double *arr, double alpha)
{
  drawTexture(texNum, arr[0], arr[1], arr[2], arr[3], alpha);
}

// find the first power of two greater than val
int power_of_two(int val)
{
  int pow = 1;
  while (pow < val) pow *= 2;
  return pow;
}

int Texture::moveImgDataToGraphicsCard()
{
  const bool useMipMaps = true;
  unsigned id;
  glGenTextures(1, &id);  // request and store one texture id

  glBindTexture(GL_TEXTURE_2D, id);
  // set various default parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if ( useMipMaps ) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
  } else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEX_WIDTH, TEX_HEIGHT, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, imgData);
  return id;
}

// load an image into the texture memory of the graphics card.
//   filename   the name of a ppm or pam file
Texture::Texture(const char *filename)
{
  // load the picture data into main memory
  Image img(filename);

  // compute next power of two above these two values, for the texture
  TEX_WIDTH = power_of_two(img.getWidth());
  TEX_HEIGHT = power_of_two(img.getHeight());

  // remap the pixels into an appropriate buffer size in main memory
  imgData = new pixel[ TEX_WIDTH*TEX_HEIGHT ];
  for ( unsigned y = 0; y < img.getHeight(); ++y )
    for ( unsigned x = 0; x < img.getWidth(); ++x )
      imgData[ y*TEX_WIDTH + x ] = img.getPixel(x,y);

  // compute the ratio of width and height
  widthRatio = 1.*img.getWidth()/TEX_WIDTH;
  heightRatio = 1.*img.getHeight()/TEX_HEIGHT;

  // move the data from main memory to the graphics card
  int id = moveImgDataToGraphicsCard();
  int windowID = glutGetWindow();
  win2id[windowID] = id;
}

int loadTexture(const char *filename)
{ 

  map<const string, int>::iterator iter = textureFileLookup.find(filename);
  if ( iter == textureFileLookup.end() ) {
    int currNum = globalTexture.size();
    globalTexture.push_back( Texture(filename) );  // create the texture
    textureFileLookup[filename] = currNum;
    return currNum;
  } else {
    int windowID = glutGetWindow();
    Texture &curr = globalTexture[iter->second];
    map<int, unsigned>::iterator iter2 = curr.win2id.find(windowID);
    if ( iter2 == curr.win2id.end() ) {
      int id = curr.moveImgDataToGraphicsCard();  // redo for current window
      curr.win2id[windowID] = id;
    }
    return iter->second;
  }
}

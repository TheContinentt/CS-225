#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include <iostream>
using namespace std;
using namespace cs225;

int main() {
	Image alma;
	Image &a = alma;
	(&a)->readFromFile("alma.png");
	StickerSheet *t = new StickerSheet(a, 2);
	t->changeMaxStickers(4);
	Image s;
	Image &ss = s;	
	(&ss)->readFromFile("i.png");
	t->addSticker(ss, 550, 200);
	(&ss)->readFromFile("IllinoisLogoReversedBlueRGB.png");
	t->addSticker(ss, 150, 100);
	(&ss)->readFromFile("part3-operator.png");
	t->addSticker(ss, 0, 400);
	//t->translate(0, 0, 0);
	//t->addSticker(ss, 450, 250);
	//(&ss)->readFromFile("i.png");
	//t->addSticker(ss, 160, 100);
	//t.removeSticker(2);
	Image out = t->render();
	out.writeToFile("myImage.png");
	delete t;
	//StickerSheet *tt = t;
	//Image outt = tt->render();
	//out.writeToFile("part3-1.png");
	//outt.writeToFile("part3-operator.png");
	/*Image almaa; almaa.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(almaa, 1);
  int m = sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(2);
  int mm = sheet.addSticker(i, 40, 200);
	//int mmm = sheet.addSticker(i, 400, 200);
	Image iii;
	iii = sheet.render();
	iii.writeToFile("test.png");*/
	//cout << m << mm << mmm << endl;
	//Image *m = t->getSticker(1);
	//m->writeToFile("part3-2.png");
	//delete mm;
	//delete t;
	/*Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected-3.png");
  
  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 120, 200);
  sheet.addSticker(i, 140, 200);
  sheet.removeSticker(3);
  sheet.translate(0, 0, 0);
Image iii;
	iii = sheet.render();
	iii.writeToFile("test.png");*/
	/*Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
	sheet.addSticker(i, -120, 200);
	sheet.addSticker(i, 100, 200);
  //sheet.changeMaxStickers(1);  
	Image iii;
	iii = sheet.render();
	iii.writeToFile("test.png");*/
	/*Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200); 
Image *iii;
	iii = sheet.getSticker(0);
	iii->writeToFile("test.png");*/
  return 0;
}

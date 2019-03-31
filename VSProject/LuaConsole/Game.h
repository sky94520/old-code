#define FALSE 0
#define TRUE 1

class Object;

enum { 
 POINT = 100, 
 LINE, 
 POLYGON
};
Object* createObejct (int type);
void drawObject(Object* obj, double red, double green, double blue);
int isSelected(Object* obj);
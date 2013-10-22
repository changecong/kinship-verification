#include <iostream>
#include"tinyxml2.h"
using namespace std;
using namespace tinyxml2;
void example1()
{
    XMLDocument doc;
    doc.LoadFile("dir.xml");
    const char* content= doc.FirstChildElement( "Hello" )->GetText();
    printf( "Hello,%s", content );
}

int main()
{
    example1();
    return 0;
}

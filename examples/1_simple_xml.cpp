#include "../tinybind.h"
//compile by g++ ../tinybind.cpp 1_simple_xml.cpp -o 1_simple_xml

const char* xml1=
"<bakery name='Janes'>"
"<intarray name='girlfriend'>"
"<item>1</item>"
"<item>2</item>"
"<item>3</item>"
"</intarray>"
"<boyfriend>11.1</boyfriend>"
"<boyfriend>22.2</boyfriend>"
"<boyfriend>33.3</boyfriend>"
"<cake name='New York Cheese'>"
"	<fruit name='blue berries' quantity='25'>freshness topping</fruit>"
"</cake>"
"<cake name='white forest'>"
"	<fruit name='blue berries' quantity='10' illegal='attribute'></fruit>"
"	<fruit name='strawberries' quantity='8'></fruit>"
"</cake>"
"</bakery>";

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "../tinybind_struct.h"
struct fruit
{
	string name;
	string text;
	int quantity;
};

struct intarray
{
  string name;
	vector<int> item;
};

struct cake
{
	string name;
	vector<fruit> fruits;
};
struct bakery
{
	string name;
	vector<intarray> girlfriend;
	vector<double>  boyfriend;
	vector<cake> cakes;
	int unbinded;
};
#include "../tinybind_xml.h"
STRUCT(fruit)
{
	ATTR( string, name);
	TEXT( string, text);
	ATTR( int, quantity);
};

STRUCT(intarray)
{
  ATTR( string, name);
	ARRAY(int, item);
};

STRUCT(cake)
{
	ATTR( string, name);
	CHILD( fruit, fruits);
};
STRUCT(bakery)
{
	ATTR( string, name);
	CHILD(intarray, girlfriend);
	ARRAY(double, boyfriend);
	CHILD( cake, cakes);
};
#include "../tinybind_clean.h"

int main()
{
	TiXmlDocument DOC;
	DOC.Parse( xml1);

	bakery bake;
	TXB_fromxmldoc(&bake, &DOC);

  bake.name += "AAA";
  for(int i = 0; i < bake.girlfriend[0].item.size(); i++)
  {
    bake.girlfriend[0].item[i] += 100;
  }
  
  for(int i = 0; i < bake.boyfriend.size(); i++)
  {
    bake.boyfriend[i] += 100;
  }
  
  
	TiXmlElement XBAKE("bakeryAAA");
	TXB_toxml(&bake, &XBAKE);
	XBAKE.Print( stdout, 0);

	cout << endl;
	cout << "The name of the bakery is " << bake.name << endl;
	cout << "There are " << bake.girlfriend.size() << " girlfriend array" << endl;
	cout << "There are " << bake.girlfriend[0].item.size() << " girlfriend item" << endl;
	cout << "There are " << bake.cakes.size() << " cakes" << endl;
	cout << "The first one is " << bake.cakes[0].name << ", ";
	cout << "which has " << bake.cakes[0].fruits.size() << " topping " << bake.cakes[0].fruits[0].name << "." << endl;
	cout << "The second one is " << bake.cakes[1].name << ", ";
	cout << "which has " << bake.cakes[1].fruits.size() << " toppings, including " << bake.cakes[1].fruits[0].name << " and " << bake.cakes[1].fruits[1].name << "." << endl;

	return 1;
}

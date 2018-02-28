#include "../tinybind.h"
//compile by g++ ../tinybind.cpp 2_svg_parser.cpp -o 2_svg_parser

#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

#include "../tinybind_struct.h"
#include "2_svg.h"
#include "../tinybind_xml.h"
#include "2_svg.h"
#include "../tinybind_clean.h"

int main()
{
	TiXmlDocument DOC;
	DOC.LoadFile("2_sample.svg");

	svg SVG;
	TXB_fromxmldoc( &SVG, &DOC);

	TiXmlElement XELE("svg");
	TXB_toxml( &SVG, &XELE);
	XELE.Print( stdout, 0);

	printf("\n");
	return 1;
}

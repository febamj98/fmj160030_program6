//Feba Jacob
//fmj160030
//cs 3377.501

//header files
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include "cdk.h"
#include <fstream>
#include <sstream>

//defintion
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"
const int maxRecordStringLength = 25;


using namespace std;

//BinaryFileHeader
class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

//BinaryFileRecord
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

//Main
int main()
{
  //declared variables
  WINDOW        *window;
  CDKSCREEN     *cdkscreen;
  CDKMATRIX     *myMatrix;

  const char   *rowTitles[] = {" ", "a", "b", "c", "d", "e"};
  const char   *columnTitles[] = {"", "a", "b", "c", "d", "e"};
  int           boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int           boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  window = initscr();
  cdkscreen = initCDKScreen(window);
  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
                          MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  drawCDKMatrix(myMatrix, true);

  //Binary File I/O
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  
  //BinaryFileHeader
  BinaryFileHeader *binaryHeader = new BinaryFileHeader();
  binInfile.read((char *) binaryHeader, sizeof(BinaryFileHeader));

  //BinaryFileRecord
  BinaryFileRecord *binaryRecord = new BinaryFileRecord();
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));

  //Required Variables
  string magicNum, versionNum, nRecords;
  string  strlenb,strlenc, strlend, strlene, strlenB, strlenC;
  string  strlenD, strlenE;
  
  //stringstream
  stringstream change;

  //Magic: 0xFEEDFACE
  magicNum = "Magic: 0x";
  change << hex << uppercase << binaryHeader->magicNumber;
  magicNum += change.str();
  change.str("");
  setCDKMatrixCell(myMatrix, 1, 1, magicNum.c_str());
  
  //Version: 16
  versionNum = "Version: ";
  change << dec << binaryHeader->versionNumber;
  versionNum += change.str();
  change.str("");
  setCDKMatrixCell(myMatrix, 1, 2, versionNum.c_str());
  
  //NumRecords: 4
  nRecords = "NumRecords: ";
  change << binaryHeader->numRecords;
  nRecords += change.str();
  change.str("");
  setCDKMatrixCell(myMatrix, 1, 3, nRecords.c_str());


  /***************************************************************************/
  
  //Actually print the given string
  strlenB = "strlen: ";
  strlenC = "strlen: ";
  strlenD = "strlen: ";
  strlenE = "strlen: ";
  
  //Anotherstring stream for binaryRecords
  stringstream convert;

  //strlen: 10     Seed Money
  convert << binaryRecord->stringBuffer;
  strlenb = convert.str();
  convert.str(""); //reset
  convert << strlenb.length();
  strlenB += convert.str();
  convert.str(""); //reset
  //display
  setCDKMatrixCell(myMatrix, 2, 1, strlenB.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, strlenb.c_str());

  //strlen: 10        Leadership
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  convert << binaryRecord->stringBuffer;
  strlenc = convert.str();
  convert.str(""); //reset
  convert << strlenc.length();
  strlenC += convert.str();
  convert.str(""); //reset
  //display
  setCDKMatrixCell(myMatrix, 3, 1, strlenC.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, strlenc.c_str());

  //strlen: 16        Entrepreneurship
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  convert << binaryRecord->stringBuffer;
  strlend = convert.str();
  convert.str(""); //reset
  convert << strlend.length();
  strlenD += convert.str();
  convert.str(""); //reset
  //display
  setCDKMatrixCell(myMatrix, 4, 1, strlenD.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, strlend.c_str());

  //strlen: 6         Skillz
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  convert << binaryRecord->stringBuffer;
  strlene = convert.str();
  convert.str(""); //reset
  convert << strlene.length();
  strlenE += convert.str();
  convert.str(""); //reset
  setCDKMatrixCell(myMatrix, 5, 1, strlenE.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, strlene.c_str());

  /**************************************************************************/

  //display messages
  drawCDKMatrix(myMatrix, true);

  unsigned char x;
  cin >> x;

  //end
  endCDK();
}

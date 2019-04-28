 #include <stdio.h>
 #include "BarcodeReadDemo_CPP.cpp file>/DynamsoftBarcodeReader.h"

 #ifdef _WIN64
 #pragma comment(lib, "<BarcodeReadDemo_CPP.cpp file>/DBRx64.lib")
 #else
 #pragma comment(lib, "<BarcodeReadDemo_CPP.cpp file>/DBRx86.lib")
 #endif
 
 
 int main()
 {
 // Define variables
 int iRet = -1;
 STextResultArray *paryResult = NULL;

 // Initialize license prior to any decoding
 CBarcodeReader reader;
 reader.InitLicense("<your license key here>");

 // Start decoding
 iRet = reader.DecodeFile("<your image file full path>", "");

 // If error occurs
 if (iRet != DBR_OK)
 {
     printf("Failed to read barcode: %d\r\n%s\r\n", iRet, DBR_GetErrorString(iRet));
     return iRet;
 }

 // If succeeds
 reader.GetAllTextResults(&paryResult);
 printf("%d total barcodes found. \r\n", paryResult->nResultsCount);
 for (int iIndex = 0; iIndex < paryResult->nResultsCount; iIndex++)
 {
     printf("Result %d\r\n", iIndex + 1);
     printf("BarcodeFormat: %s\r\n", paryResult->ppResults[iIndex]->pszBarcodeFormatString);
     printf("Text read: %s\r\n", paryResult->ppResults[iIndex]->pszBarcodeText);
 }

 // Finally release BarcodeResultArray
 CBarcodeReader::FreeTextResults(&paryResult);

 return 0;
 }

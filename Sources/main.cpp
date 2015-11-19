#include "VPDFDocument.h"
#include "VPDFPage.h"

using namespace XBOX;
int main()
{
	VPDFDocument pdf;
	VError error = VE_OK;
	VPDFPage* page = pdf.AddPage( error );
	
	page->SetWidth ( 500 );
	page->SetHeight ( 400 ) ;

	page->ShowText ( " This is a Test Text" );
	//pdf.SetPassword ( (uBYTE*)"123456" , (uBYTE*)"1230456" );
	pdf.Save ((uBYTE*)"file.pdf");

	
	return 0;
}
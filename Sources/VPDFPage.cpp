#include "VPDFPage.h"
using namespace XBOX;
VPDFPage::VPDFPage(){}

VPDFPage* VPDFPage::CreatePage(HPDF_Page inPageHandle)
{
	VPDFPage* vPage = new VPDFPage();
	vPage->fPageHandle = inPageHandle ;
	
	return vPage;
}



VError VPDFPage::SetWidth( REAL inWidthValue )
{
  return HPDF_Page_SetWidth ( fPageHandle , inWidthValue );
}

VError VPDFPage::SetHeight(REAL inHeightValue)
{
  return HPDF_Page_SetHeight ( fPageHandle , inHeightValue );
}

VError VPDFPage::ShowText (const char* Text )
{
	//HPDF_Page_Stroke(fPageHandle );
	VError err = HPDF_Page_BeginText (fPageHandle );
	
	//HPDF_Page_MoveTextPos (fPageHandle, 0, 0);
	
	HPDF_Font font = HPDF_GetFont (fDocParent, "Courier-Bold", NULL);
	HPDF_Page_SetFontAndSize( fPageHandle,font,10);
	if (!err )
	{
		err = HPDF_Page_MoveTextPos2(fPageHandle, 15, 20);
		if ( !err )
		{
			err = HPDF_Page_ShowText ( fPageHandle , Text );
			
		}
		if (!err) 
			HPDF_Page_EndText(fPageHandle );

		}
	return err;
}
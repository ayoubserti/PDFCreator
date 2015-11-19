
#ifndef _VPDF_PAGE_
#define _VPDF_PAGE_

#include "VPDFDocument.h"

class VPDFPage
{
	friend class VPDFDocument;
public:
	XBOX::VError SetWidth ( REAL inWidthValue);
	XBOX::VError SetHeight ( REAL inHeightValue );

	XBOX::VError ShowText ( const char* inText );
private:
	VPDFPage(); //prevent explicit creation
	static VPDFPage* CreatePage( HPDF_Page inPageHandle );
	
	
	HPDF_Page fPageHandle;
	HPDF_Doc  fDocParent;
	

	
};
#endif
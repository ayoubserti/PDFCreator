
#ifndef _VPDF_OUTLINE_
#define _VPDF_OUTLINE_
#include "hpdf.h"

class VPDFDocument;

class VPDFOutline
{
	friend class VPDFDocument;
private:
	VPDFOutline(){}; //prevent explicit creation
	
	
	HPDF_Outline fOutlineHandle;
};
#endif
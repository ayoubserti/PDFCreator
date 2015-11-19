
#ifndef _VPDF_DOCUMENT_
#define _VPDF_DOCUMENT_

#include "hpdf.h"
#include "ToolBox.h"
#include "xboxTypes.h"

typedef HPDF_PageMode ePDFPageMode;

typedef HPDF_PageLayout ePDFPageLayout;

typedef HPDF_PageNumStyle ePDFPageNumStyle;

typedef HPDF_ColorSpace   ePDFColorSpace;

class VPDFPage;

class VPDFDestination;

class VPDFFont;

class VPDFEncoder;

class VPDFImage;

class VPDFOutline;

class VPDFDocument
{
public:
	VPDFDocument();
	
	VPDFPage* CreatePage(  XBOX::VError& outError );

	XBOX::VError Save( uBYTE* inFileName );
	
	XBOX::VError SaveToStream ();

	XBOX::VError SetPageConfiguration( uLONG inPagePerPages );
	
	XBOX::VError SetPageLayout ( ePDFPageLayout inPageLayout );

	XBOX::VError SetPageMode( ePDFPageMode inPageMode );

	XBOX::VError SetOpenAction ( const VPDFDestination& inOpenAction) ;

	VPDFPage*  GetCurrentPage ();

	VPDFPage*  AddPage (  XBOX::VError& outError );

	VPDFPage* InsertPage ( const VPDFPage& inTargetPage );

	VPDFFont* GetFont( const uBYTE* inFontName, const uBYTE* inEncondingName, XBOX::VError& outError);
	
	const uBYTE* LoadType1Font (const uBYTE* inAfmFileName, const uBYTE* inPfmFileName, XBOX::VError& outError );

	const uBYTE* LoadTTFont (const uBYTE* inFileName, bool inEmbedding, XBOX::VError& outError );

	XBOX::VError AddPageLabel ( uLONG inPageNumber, ePDFPageNumStyle inPageNumStyle, uLONG inFirstPage , const uBYTE* inPrefix );

	XBOX::VError UseJPFonts ();

	XBOX::VError UseKRFonts ();

	XBOX::VError UseCNSFonts ();

	XBOX::VError UseCNTFonts ();

	VPDFOutline* CreateOutline( VPDFOutline* inParent, const uBYTE* inTitle, VPDFEncoder* inEncoder, XBOX::VError& outError );

	VPDFEncoder* GetEncoder ( const uBYTE* inEncodingName, XBOX::VError& outError );

	VPDFEncoder* GetCurrentEncoder ( XBOX::VError& outError ) ;

	VPDFEncoder* SetCurrentEncoder ( const uBYTE* inEncodingName, XBOX::VError& outError  ) ;

	VPDFImage*   LoadPngImage ( const uBYTE* inImgFileName , XBOX::VError& outError );

	VPDFImage*   LoadRawImage ( const uBYTE* inImgFileName ,uLONG inWidth, uLONG inHeight,ePDFColorSpace inColorSpace , XBOX::VError& outError );

	XBOX::VError SetPassword ( const uBYTE* inOwnerPwd, const uBYTE* inUserPwd );

	
	~VPDFDocument();

private:
	HPDF_Doc fDocHandle;
	VPDFPage* fCurrentPage;
};


#endif
/**
 * @file 
 * 
 * Scripts to draw energy loss fits from correction object file 
 *
 * @ingroup pwglf_forward_scripts_corr
 */
/** 
 * Draw energy loss fits to a multi-page PDF. 
 *
 * @par Input: 
 * The input file is expected to contain a AliFMDCorrELossFit object
 * named @c elossfits in the top level directory.
 * 
 * @par Output: 
 * A multi-page PDF.  Note, that the PDF generated by ROOT in this way
 * is broken (cannot be read by Acrobat Reader on Windows and MacOSX)
 * and one should pass it through a filter to correct these problems.
 * 
 * @param runNo   Run number
 * @param sys     Collision system 
 * @param sNN     Collision energy in GeV
 * @param fname   File name 
 * @param details Drawing options 
 *
 * @ingroup pwglf_forward_scripts_corr
 */
void
DrawCorrAcc(ULong_t runNo, UShort_t sys, UShort_t sNN, 
	    const char* fname=0, Bool_t details=true)
{
  //__________________________________________________________________
  // Load libraries and object 
  // const char* fwd = "$ALICE_PHYSICS/PWGLF/FORWARD/analysis2";
  const char* fwd = "$ALICE_PHYSICS/PWGLF/FORWARD/analysis2";
  gROOT->Macro(Form("%s/scripts/LoadLibs.C", fwd));
  gROOT->LoadMacro(Form("%s/scripts/SummaryDrawer.C", fwd));
  gROOT->LoadMacro(Form("%s/corrs/CorrDrawer.C", fwd));

  CorrDrawer d;
  d.Run(AliForwardCorrectionManager::kAcceptance, runNo, sys, sNN, 0, 
	false, false, "", fname);
	
}
//
// EOF
//

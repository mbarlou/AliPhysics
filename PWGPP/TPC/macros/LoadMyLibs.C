void LoadMyLibs() {

  // Load some ROOT libraries
  CheckLoadLibrary("libEG");
  CheckLoadLibrary("libGeom");
  CheckLoadLibrary("libVMC");
  CheckLoadLibrary("libTree");
  CheckLoadLibrary("libGui");
  CheckLoadLibrary("libMinuit");
  CheckLoadLibrary("libSTAT");
  
  // Load AliRoot libraries
  
  CheckLoadLibrary("libSTEERBase");
  CheckLoadLibrary("libESD");
  CheckLoadLibrary("libCDB");
  CheckLoadLibrary("libRAWDatabase");
  CheckLoadLibrary("libRAWDatarec");
  CheckLoadLibrary("libSTEER");
  CheckLoadLibrary("libRAWDatasim");


  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");

  gSystem->Load("libPWG0base");
  gSystem->Load("libPWG0dep");
  gSystem->Load("libPWG0selectors");

  gSystem->Load("libTPCcalib");
  gSystem->Load("libTender");
  gSystem->Load("libPWGPP");
  
  gSystem->Load("libPHOSUtils");
  gSystem->Load("libEMCALUtils");
  gSystem->Load("libPWG4PartCorrBase");
  gSystem->Load("libPWG4PartCorrDep");

  /*
  CheckLoadLibrary("libANALYSIS");
  CheckLoadLibrary("libAOD");
  CheckLoadLibrary("libANALYSISalice");
  CheckLoadLibrary("libTender");
  CheckLoadLibrary("libSTAT");
  */

  CheckLoadLibrary("libTPCbase");
  CheckLoadLibrary("libTPCsim");
  CheckLoadLibrary("libTPCrec");
  CheckLoadLibrary("libTPCcalib");
  CheckLoadLibrary("libITSbase");
  CheckLoadLibrary("libITSsim");
  CheckLoadLibrary("libITSrec");
  CheckLoadLibrary("libTRDcalib");
  CheckLoadLibrary("libTRDbase");
  CheckLoadLibrary("libTRDrec");
  CheckLoadLibrary("libTRDsim");
  CheckLoadLibrary("libTOFbase");
  CheckLoadLibrary("libTOFrec");
  CheckLoadLibrary("libTOFsim");
  CheckLoadLibrary("libMFTbase");
  CheckLoadLibrary("libMFTrec");
  CheckLoadLibrary("libMFTsim");
  CheckLoadLibrary("libPWGPP");
}

Int_t CheckLoadLibrary(const char* library) {
  // checks if a library is already loaded, if not loads the library
  if (strlen(gSystem->GetLibraries(library, "", kFALSE)) > 0)
    return 1;
  return gSystem->Load(library);
}

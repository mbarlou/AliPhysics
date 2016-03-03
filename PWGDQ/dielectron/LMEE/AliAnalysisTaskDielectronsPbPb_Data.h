#ifndef AliAnalysisTaskDielectronsPbPb_Data_cxx
#define AliAnalysisTaskDielectronsPbPb_Data_cxx


//==================== DIELECTRON ANALYSIS (DATA) ===================//
//                                                                   //
//    Dielectron analysis in Pb-Pb collisions at 2.76 TeV (Run1).    //
//    Invariant mass spectra for US & LS pairs including event       //
//    mixing for R factor calculation.                               //
//                                                                   //
//===================================================================//


#include "AliDielectronReducedTrack.h"
#include "AliEventPoolManager.h"
#include "AliAnalysisTaskSE.h"
#include "AliESDtrackCuts.h"
#include "AliAnalysisTask.h"
#include "AliPIDResponse.h"
#include "AliEventplane.h"
#include "AliCentrality.h"
#include "AliESDVertex.h"
#include "AliESDEvent.h"
#include "AliESDtrack.h"
#include "TVector3.h"
#include "TList.h"
#include "TH1F.h"
#include "TH2F.h"

class AliAnalysisTaskDielectronsPbPb_Data : public AliAnalysisTaskSE {
    
public:
    AliAnalysisTaskDielectronsPbPb_Data();
    AliAnalysisTaskDielectronsPbPb_Data(const char *name);
    virtual ~AliAnalysisTaskDielectronsPbPb_Data();
    
    void SetCentralityRange (Double_t CentralityMin, Double_t CentralityMax)  {
        
        fCentralityMin = CentralityMin;
        fCentralityMax = CentralityMax;
    }
   
    void SetDCAparameters (Double_t DCAxy_param0, Double_t DCAxy_param1, Double_t DCAxy_param2, Double_t DCAz_max)  {
        
        fDCAxy_param0 = DCAxy_param0;
        fDCAxy_param1 = DCAxy_param1;
        fDCAxy_param2 = DCAxy_param2;
        fDCAz_max =     DCAz_max;
    }
    
    void SetTrackCuts (Int_t ITS_minNcls, Int_t TPC_minNcls, Int_t TPC_nClsdEdx, Int_t TPC_minCr, Double_t MinCrOverFindableCls, Double_t MaxGoldenChi2, Double_t MaxTPCchi2, Double_t MaxITSchi2, Double_t MaxFracSharedCls)  {
    
        fITS_minNcls =          ITS_minNcls;
        fTPC_minNcls =          TPC_minNcls;
        fTPC_nClsdEdx =         TPC_nClsdEdx;
        fTPC_minCr =            TPC_minCr;
        fMinCrOverFindableCls = MinCrOverFindableCls;
        fMaxGoldenChi2 =        MaxGoldenChi2;
        fMaxTPCchi2 =           MaxTPCchi2;
        fMaxITSchi2 =           MaxITSchi2;
        fMaxFracSharedCls =     MaxFracSharedCls;
    }
    
    void SetPIDCuts (Double_t nsigmaTOF_max, Double_t nsigmaITS_max, Double_t nsigmaTPC_min, Double_t nsigmaTPC_max)  {
    
        fnsigmaTOF_max = nsigmaTOF_max;
        fnsigmaITS_max = nsigmaITS_max;
        fnsigmaTPC_min = nsigmaTPC_min;
        fnsigmaTPC_max = nsigmaTPC_max;
    }
    
    void SetPrefilterCuts (Double_t MassLim, Double_t PhivLim)  {
        
        fMassLim = MassLim;
        fPhivLim = PhivLim;
    }
    
    void EventMixingSettings (Int_t MaxNumberEvts, Int_t MaxNumberTrks, Int_t NumberEvtsToMix, Int_t NcentralityBins, Int_t NvertexBins, Int_t NeventPlaneBins)  {
        
        fMaxNumberEvts =   MaxNumberEvts;
        fMaxNumberTrks =   MaxNumberTrks;
        fNumberEvtsToMix = NumberEvtsToMix;
        fNcentralityBins = NcentralityBins;
        fNvertexBins =     NvertexBins;
        fNeventPlaneBins = NeventPlaneBins;
    }
   
    void SetMixingPools();
    virtual void   UserCreateOutputObjects();
    virtual void   UserExec(Option_t *option);
    
    Bool_t   GetEvent();
    Double_t Centrality();
    Double_t EventPlane();
    Double_t ZVertex();
    Double_t GetEventMultiplicity();
    
    Bool_t   PassedTrackQualityCutsMultiplicity (AliESDtrack *track);
    Bool_t   PassedTrackQualityCuts             (AliESDtrack *track);
    Bool_t   PassedLooseTrackQualityCuts        (AliESDtrack *track);
    Double_t FractionSharedClsITS               (AliESDtrack *track);
    Bool_t   PassedPIDcuts                      (AliESDtrack *track, Double_t Ntrk);
    Double_t GetCorrectedTPCResponse            (AliESDtrack *track, Double_t Ntrk);
    Double_t GetMeanTPCnsigma                   (Double_t eta, Double_t Ntrk);
    Double_t GetWidthTPCnsigma                  (Double_t eta, Double_t Ntrk);
    
    Bool_t   TaggedByPrefilter (AliESDtrack *track_before, AliESDtrack *track_after[], Int_t Nelec_After);
    
    Double_t GetMass (AliESDtrack *track1, AliESDtrack *track2);
    Double_t GetMass (AliESDtrack *track1, AliDielectronReducedTrack *track2);
    Double_t GetPtee (AliESDtrack *track1, AliESDtrack *track2);
    Double_t GetPtee (AliESDtrack *track1, AliDielectronReducedTrack *track2);
    Double_t GetPhiV (AliESDtrack *track1, AliESDtrack *track2);

    virtual void   Terminate(Option_t *);
    
private:
    AliESDEvent         *fESDevent;//!
    AliEventPoolManager *fPoolMgr;//!
    AliESDtrackCuts     *fESDTrackCuts;//!
    AliPIDResponse      *fPIDResponse;//!
    TList               *fOutputList;//!
    
    Double_t fCentralityMin;//
    Double_t fCentralityMax;//
    Double_t fDCAxy_param0;//
    Double_t fDCAxy_param1;//
    Double_t fDCAxy_param2;//
    Double_t fDCAz_max;//
    Int_t    fITS_minNcls;//
    Int_t    fTPC_minNcls;//
    Int_t    fTPC_nClsdEdx;//
    Int_t    fTPC_minCr;//
    Double_t fMinCrOverFindableCls;//
    Double_t fMaxGoldenChi2;//
    Double_t fMaxTPCchi2;//
    Double_t fMaxITSchi2;//
    Double_t fMaxFracSharedCls;//
    Double_t fnsigmaTOF_max;//
    Double_t fnsigmaITS_max;//
    Double_t fnsigmaTPC_min;//
    Double_t fnsigmaTPC_max;//
    Double_t fMassLim;//
    Double_t fPhivLim;//
    Int_t    fNcentralityBins;//
    Int_t    fNvertexBins;//
    Int_t    fNeventPlaneBins;//
    Int_t    fMaxNumberEvts;//
    Int_t    fMaxNumberTrks;//
    Int_t    fNumberEvtsToMix;//
    
    
    //Event Statistics
    TH1F *fHistoEvents;//!
    
    //Eta Bins
    TH1F *fHistoEtaBins;//!
    
    //Invariant Mass Spectra (Same Event)
    TH2F *fHistoInvariantMass_ULS;//!
    TH2F *fHistoInvariantMass_ULS_Pref;//!
    TH2F *fHistoInvariantMass_PLS;//!
    TH2F *fHistoInvariantMass_PLS_Pref;//!
    TH2F *fHistoInvariantMass_NLS;//!
    TH2F *fHistoInvariantMass_NLS_Pref;//!
    
    //Invariant Mass Spectra (Mixed Event)
    TH2F *fHistoInvariantMass_EvtMixing_ULS;//!
    TH2F *fHistoInvariantMass_EvtMixing_ULS_Pref;//!
    TH2F *fHistoInvariantMass_EvtMixing_PLS;//!
    TH2F *fHistoInvariantMass_EvtMixing_PLS_Pref;//!
    TH2F *fHistoInvariantMass_EvtMixing_NLS;//!
    TH2F *fHistoInvariantMass_EvtMixing_NLS_Pref;//!
    
    
    AliAnalysisTaskDielectronsPbPb_Data(const AliAnalysisTaskDielectronsPbPb_Data&);
    AliAnalysisTaskDielectronsPbPb_Data& operator=(const AliAnalysisTaskDielectronsPbPb_Data&);
    
    ClassDef(AliAnalysisTaskDielectronsPbPb_Data, 1);
};
#endif

#include "AliAnalysisTaskTransverseEnergy.h"
#include "AliAnalysisEtSelectionHandler.h"
#include "AliAnalysisManager.h"
#include "AliInputEventHandler.h"
#include "AliPhysicsSelectionTask.h"
#include "AliPhysicsSelection.h"
#include "AliESDCentrality.h"
#include "AliESDEvent.h"
#include "AliLog.h"
#include <iostream>

ClassImp(AliAnalysisTaskTransverseEnergy)

AliAnalysisTaskTransverseEnergy::AliAnalysisTaskTransverseEnergy(const char* name, Bool_t isMc) :
        AliAnalysisTaskSE(name)
	,fESDEvent(0)
        ,fMCConfigFile("ConfigEtMonteCarlo.C")
        ,fRecoConfigFile("ConfigEtReconstructed.C")
        ,fHistEtRecvsEtMC(0)
        ,fEsdtrackCutsITSTPC(0)
        ,fEsdtrackCutsTPC(0)
        ,fEsdtrackCutsITS(0)
        ,fOutputList(0)
        ,fPhysSelTaskName("selctionTask")
        ,fCentSelTaskName("centralityTask")
	,fIsMc(isMc)
	,fUsingDefaultSelection(true)
	,fCurrentRunNumber(-1)
	,fSelectionHandler(0)
{
  // Constructor
    LoadPhysicsSelection("physicsSelections.root");
}

AliAnalysisTaskTransverseEnergy::~AliAnalysisTaskTransverseEnergy()
{
    // destructor
}

Int_t AliAnalysisTaskTransverseEnergy::CheckPhysicsSelection(Int_t runNumber)
{
  // Check if the physics selection is valid, if not load a new one
    if (runNumber == fCurrentRunNumber || fIsMc)
    {
        return 0;
    }
    else
    {
        AliPhysicsSelection *selection = 0;
        AliPhysicsSelectionTask *physSelTask = dynamic_cast<AliPhysicsSelectionTask*>(AliAnalysisManager::GetAnalysisManager()->GetTasks()->At(0));
        if (physSelTask)
        {

            if ((selection = fSelectionHandler->GetPhysicsSelection(runNumber)))
            {
            }
            else if ((selection = fSelectionHandler->GetDefaultPhysicsSelection()))
            {
	      fUsingDefaultSelection = true;
            }
            else if ((selection = new AliPhysicsSelection()))
            {
	      fUsingDefaultSelection = true;
            }
            else
            {
                AliError("Something went very wrong, not able to load/create new physics selection");
                return -1;
            }
        }
        else
        {
            AliError("Could not get physics selection task from manager, undefined or no selection will be used");
            return -1;
        }
        AliInfo("Changing the physics selection");
        // The physics selection task has a bit weird implementation, setting the the physics selection will not update the handler, so we do it manually
        AliInputEventHandler* handler = dynamic_cast<AliInputEventHandler*> (AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
        physSelTask->SetPhysicsSelection(selection);
        handler->SetEventSelection(selection);
        fCurrentRunNumber = runNumber;

    }

    return 1;
}

Bool_t AliAnalysisTaskTransverseEnergy::IsPhysicsSelected() const
{
  // See header file for class documentation
    if(fIsMc) return true;
    if(!fUsingDefaultSelection) return (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected() & AliVEvent::kUserDefined);
    return (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected() & AliVEvent::kMB);
}

Int_t AliAnalysisTaskTransverseEnergy::LoadPhysicsSelection(TString name)
{	
  // See header file for class documentation
    if(fIsMc) return 0;
    fSelectionHandler = new AliAnalysisEtSelectionHandler(name);
    if (!fSelectionHandler) return -1;
    return 0;
}

AliESDCentrality* AliAnalysisTaskTransverseEnergy::GetCentralityObject()
{
  // See header file for class documentation
    if (fESDEvent)return fESDEvent->GetCentrality();
    else return 0;
}



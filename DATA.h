//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May 24 14:33:36 2022 by ROOT version 6.24/06
// from TTree DATA/CAEN VME LaBr3 DATA
// found on file: LaBr_152Eu_PRD_0.root
//////////////////////////////////////////////////////////

#ifndef DATA_h
#define DATA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class DATA {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UShort_t        Ch;
   ULong64_t       TS;
   UShort_t        Energy;
   UShort_t        E_Short;

   // List of branches
   TBranch        *b_Ch;   //!
   TBranch        *b_TS;   //!
   TBranch        *b_Energy;   //!
   TBranch        *b_E_Short;   //!

   DATA(TTree *tree=0);
   virtual ~DATA();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DATA_cxx
DATA::DATA(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("LaBr_152Eu_PRD_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("LaBr_152Eu_PRD_0.root");
      }
      f->GetObject("DATA",tree);

   }
   Init(tree);
}

DATA::~DATA()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DATA::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DATA::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void DATA::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Ch", &Ch, &b_Ch);
   fChain->SetBranchAddress("TS", &TS, &b_TS);
   fChain->SetBranchAddress("Energy", &Energy, &b_Energy);
   fChain->SetBranchAddress("E_Short", &E_Short, &b_E_Short);
   Notify();
}

Bool_t DATA::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DATA::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DATA::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DATA_cxx

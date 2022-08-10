//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul  1 09:39:58 2022 by ROOT version 6.22/08
// from TTree PartInfo/Particle information
// found on file: ../XS_Pi+_G4_lAr_1GeV_10b_0.root
//////////////////////////////////////////////////////////

#ifndef qeana_h
#define qeana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class qeana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventID;
   vector<int>     *PDGcode;
   vector<int>     *interType;
   vector<int>     *targetZ;
   vector<double>  *massPart;
   vector<double>  *X;
   vector<double>  *Y;
   vector<double>  *Z;
   vector<double>  *Px;
   vector<double>  *Py;
   vector<double>  *Pz;
   vector<double>  *E;

   // List of branches
   TBranch        *b_EventID;   //!
   TBranch        *b_PDGcode;   //!
   TBranch        *b_interType;   //!
   TBranch        *b_targetZ;   //!
   TBranch        *b_massPart;   //!
   TBranch        *b_X;   //!
   TBranch        *b_Y;   //!
   TBranch        *b_Z;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_E;   //!

   qeana(TTree *tree=0);
   virtual ~qeana();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef qeana_cxx
qeana::qeana(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("XS_Pi+_G4_lAr_1GeV_10b_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("XS_Pi+_G4_lAr_1GeV_10b_0.root");
      }
      f->GetObject("PartInfo",tree);

   }
   Init(tree);
}

qeana::~qeana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t qeana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t qeana::LoadTree(Long64_t entry)
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

void qeana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   PDGcode = 0;
   interType = 0;
   targetZ = 0;
   massPart = 0;
   X = 0;
   Y = 0;
   Z = 0;
   Px = 0;
   Py = 0;
   Pz = 0;
   E = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventID", &EventID, &b_EventID);
   fChain->SetBranchAddress("PDGcode", &PDGcode, &b_PDGcode);
   fChain->SetBranchAddress("interType", &interType, &b_interType);
   fChain->SetBranchAddress("targetZ", &targetZ, &b_targetZ);
   fChain->SetBranchAddress("massPart", &massPart, &b_massPart);
   fChain->SetBranchAddress("X", &X, &b_X);
   fChain->SetBranchAddress("Y", &Y, &b_Y);
   fChain->SetBranchAddress("Z", &Z, &b_Z);
   fChain->SetBranchAddress("Px", &Px, &b_Px);
   fChain->SetBranchAddress("Py", &Py, &b_Py);
   fChain->SetBranchAddress("Pz", &Pz, &b_Pz);
   fChain->SetBranchAddress("E", &E, &b_E);
   Notify();
}

Bool_t qeana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void qeana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t qeana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef qeana_cxx

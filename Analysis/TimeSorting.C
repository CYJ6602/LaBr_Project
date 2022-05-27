#include "Defines.h"

void TimeSorting(TString infname = "/data3/LaBr_DATA/run_PRD/LaBr_152Eu_PRD_0.root", Float_t CoinWidth = 100, Float_t CoinOffset = -600)
{
   // gSystem->AddIncludePath(LaBr_DATA_PATH) ;

   Float_t CoinWidth_TS = CoinWidth / 2;   // in TimeStamp unit (1/2ns)
   Float_t CoinOffset_TS = CoinOffset / 2; // in TimeStamp unit (1/2ns)

   std::cout << "Input : " << infname << std::endl;

   // Open unsorted file and set branch address
   TFile *fin = new TFile(infname, "read");
   TTree *tin = (TTree *)fin->Get("DATA");
   Int_t Nentries = tin->GetEntries();
   // Nentries = 1e3;

   UShort_t Ch;
   ULong64_t TS;
   UShort_t Energy;
   UShort_t E_Short;

   tin->SetBranchAddress("Ch", &Ch);
   tin->SetBranchAddress("TS", &TS);
   tin->SetBranchAddress("Energy", &Energy);
   tin->SetBranchAddress("E_Short", &E_Short);

   // Open output file and make new branches with multiplicity
   TString outfname = infname.Replace(infname.Length() - 5, 5, "_TSSorted.root");
   std::cout << outfname << std::endl;

   TFile *fout = new TFile(outfname, "recreate");
   TTree *tout = new TTree("DATA", "DATA");

   UShort_t Mult;
   UShort_t TAC;
   UShort_t ChArr[20];
   ULong64_t TSArr[20];
   UShort_t EnergyArr[20];
   UShort_t E_ShortArr[20];
   tout->Branch("Mult", &Mult, "Mult/s");
   tout->Branch("Ch", ChArr, "Ch[Mult]/s");
   tout->Branch("TS", TSArr, "TS[Mult]/l");
   tout->Branch("Energy", EnergyArr, "Energy[Mult]/s");
   tout->Branch("E_Short", E_ShortArr, "E_Short[Mult]/s");
   tout->Branch("TAC", &TAC, "TAC/s");

   Int_t CoinCheckStartEnt = 0;
   Bool_t fCoin0 = false;
   Bool_t fCoin1 = false;
   Bool_t fCh2 = false;
   Long64_t RefTS = 0;

   for (Int_t i = 0; i < Nentries; i++)
   {
      if (i % 1000 == 0)
         std::cout << "\rSorting : " << 1. * i / Nentries * 100 << "%" << std::flush;

      tin->GetEntry(i);

      // Fine crossing point of Ch 2 -> Ch 0 or 1
      if (Ch == 2)
      {
         fCh2 = true;
      }
      else if ((Ch == 0 || Ch == 1) && fCh2)
      {
         fCh2 = false;
         CoinCheckStartEnt = i;
         // std::cout << "Set the Start Ent to : " << i << std::endl;
      }

      Mult = 0;
      fCoin0 = false;
      fCoin1 = false;
      RefTS = TS + CoinOffset_TS;

      if (Ch == 2)
      {
         TAC = Energy; // Energy of TAC channel
         for (Int_t j = CoinCheckStartEnt; j < i; j++)
         {
            tin->GetEntry(j);
            Long64_t TSdiff = (Long64_t)TS - RefTS;
            // std::cout << "TSdiff : " << TSdiff << std::endl;
            if (TMath::Abs(TSdiff) < CoinWidth_TS)
            {
               if (Ch == 0)
               {
                  fCoin0 = true;
                  ChArr[Mult] = Ch;
                  EnergyArr[Mult] = Energy;
                  Mult++;
               }
               else if (Ch == 1)
               {
                  fCoin1 = true;
                  ChArr[Mult] = Ch;
                  EnergyArr[Mult] = Energy;
                  Mult++;
               }
            }
         }

         if (fCoin0 && fCoin1)
         {
            tout->Fill();
         }
      }
   }
   tout->Write();
   fout->Close();
   fin->Close();

   std::cout << "Output : " << outfname << std::endl;
}
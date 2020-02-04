///////////////////////////////////////////////////////////////////////////////
// read data file : data/neutrons_119.txt  (nuclei with 119 neutrons)
// format (the file pre-parsed manually) 
// N/I:Z/I:A/I:Name/C:dm/F:sig_dm/F:ebind/F:sig_ebind/F:ma/F:sig_ma/F
//
// M(nucleus) + Z*me = xu*A + MASS_EXCESS*1.e-3 [MeV]
// 196 : 195.9649515
///////////////////////////////////////////////////////////////////////////////

struct nudata_t {
  int   fN;
  int   fZ;
  int   fA;
  char  fName[100];
  float fDm;               // mass defect
  float fSigDm;            // uncertainty on fDm
  float fEb;
  float fSigEb;
  float fMa;               // atomic mass, atomic units
  float fSigMa;
} Nudata;


const double kXu        = 931.4940954;   // atomic mass unit, in MeV
const double kMNeutron  = 939.5654133;   // neutron mass, MeV
const double kMProton   = 938.272046 ;   // proton  mass, MeV
const double kMElectron = 0.510999;


const double kMPt197    = 196.96735;     // M(Pt-197) atom, atomic units

void neutrons_119_ana(const char* Fn) {
  TTree* t = new TTree("isotope_tree","Pt isotope tree");

  // read Pt isotope data
  // format (the file pre-parsed manually) 
  // N/I:Z/I:A/I:Name/C:dm/F:sig_dm/F:ebind/F:sig_ebind/F:ma/F:sig_ma/F

  t->ReadFile(Fn,"N/I:Z/I:A/I:Name/C:dm/F:sig_dm/F:ebind/F:sig_ebind/F:ma/F:sig_ma/F");


  t->SetBranchAddress("N"        ,&Nudata.fN);
  t->SetBranchAddress("Z"        ,&Nudata.fZ);
  t->SetBranchAddress("A"        ,&Nudata.fA);
  t->SetBranchAddress("Name"     ,Nudata.fName);
  t->SetBranchAddress("dm"       ,&Nudata.fDm);
  t->SetBranchAddress("sig_dm"   ,&Nudata.fSigDm);
  t->SetBranchAddress("ebind"    ,&Nudata.fEb);
  t->SetBranchAddress("sig_ebind",&Nudata.fSigEb);
  t->SetBranchAddress("ma"       ,&Nudata.fMa);
  t->SetBranchAddress("sig_ma"   ,&Nudata.fSigMa);

  int nent = t->GetEntries();

  for (int i=0; i<nent; i++) {
    t->GetEntry(i);

    double ma_isotope = kXu*Nudata.fA + Nudata.fDm*1.e-3;   // atomic mass of the isotope
    double mn_isotope = ma_isotope-Nudata.fZ*kMElectron;

    // mx: add protons, to see whether the total mass could be less than that of ^197 isotope
    
    double mx        = (ma_isotope + kMProton*(78-Nudata.fZ))/kXu;

    printf("N,Z,A,m_isotope, mx, my = %3i %3i %3i %12.5lf %12.5lf %12.5lf %10.5lf\n",
	   Nudata.fN,Nudata.fZ,Nudata.fA,ma_isotope/kXu,mn_isotope,Nudata.fMa,(mx-kMPt197)*kXu);
    
  }

  printf("nent = %3i\n",nent);

}

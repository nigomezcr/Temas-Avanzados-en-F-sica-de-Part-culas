#import AnalysisHelpers as AH
import ROOT
#import Analysis

from Analysis import Analysis
from Analysis import AnalysisHelpers as AH
from Analysis import Constants
#======================================================================
        
class TTbarAnalysis(Analysis.Analysis):
  """Semileptonic TTbarAnalysis loosely based on the ATLAS analyses of top pair events where 
  one W boson decays to leptons and one decays to hadrons.
  """
  def __init__(self, store):
    super(TTbarAnalysis, self).__init__(store)
  
  def initialize(self):
      self.hist_WtMass      =  self.addStandardHistogram("WtMass")

      self.hist_leptn       =  self.addStandardHistogram("lep_n")
      self.hist_leptpt      =  self.addStandardHistogram("lep_pt")
      self.hist_lepteta     =  self.addStandardHistogram("lep_eta")
      self.hist_leptE       =  self.addStandardHistogram("lep_E")
      self.hist_leptphi     =  self.addStandardHistogram("lep_phi")
      self.hist_leptch      =  self.addStandardHistogram("lep_charge")
      self.hist_leptID      =  self.addStandardHistogram("lep_type")
      self.hist_leptptc     =  self.addStandardHistogram("lep_ptconerel30")
      self.hist_leptetc     =  self.addStandardHistogram("lep_etconerel20")
      self.hist_lepz0       =  self.addStandardHistogram("lep_z0")
      self.hist_lepd0       =  self.addStandardHistogram("lep_d0")

      self.hist_njets       =  self.addStandardHistogram("n_jets")       
      self.hist_jetspt      =  self.addStandardHistogram("jet_pt")       
      self.hist_jetm        =  self.addStandardHistogram("jet_m")        
      self.hist_jetJVF      =  self.addStandardHistogram("jet_jvf")      
      self.hist_jeteta      =  self.addStandardHistogram("jet_eta")      
      self.hist_jetmv1      =  self.addStandardHistogram("jet_MV1")      

      self.hist_etmiss      = self.addStandardHistogram("etmiss")
      self.hist_vxp_z       = self.addStandardHistogram("vxp_z")
      self.hist_pvxp_n      = self.addStandardHistogram("pvxp_n")
  
      self.hist_W_mass      = self.assStandardHistogram("W_mass")
      self.hist_T_mass      = self.assStandardHistogram("T_mass")
      self.hist_Zp_mass     = self.assStandardHistogram("Zp_mass")

    

  
  def analyze(self):
      # retrieving objects
      eventinfo = self.Store.getEventInfo()
      weight = eventinfo.scalefactor()*eventinfo.eventWeight() if not self.getIsData() else 1
      self.countEvent("all", weight)

      # apply standard event based selection
      if not AH.StandardEventCuts(eventinfo): return False
      self.countEvent("EventCuts", weight)

      # neutrinos are expected, so cut on missing transverse momentum
      etmiss = self.Store.getEtMiss()
      if not (etmiss.et() > 30.0): return False
      self.countEvent("MET", weight)
      
      # one good lepton from one of the W boson decays is expected, so require exactly one good lepton
      goodLeptons = AH.selectAndSortContainer(self.Store.getLeptons(), AH.isGoodLepton, lambda p: p.pt())
      if not (len(goodLeptons) == 1): return False
      self.countEvent("1 Lepton", weight)

      leadlepton = goodLeptons[0]
      
      # two jets from one of the W boson decays as well as two b-jets from the top pair decays are expected
      goodJets = AH.selectAndSortContainer(self.Store.getJets(), AH.isGoodJet, lambda p: p.pt())
      if not len(goodJets) >= 4: return False
      self.countEvent("Jets", weight)

      # apply the b-tagging requirement using the MV1 algorithm at 80% efficiency
      btags = sum([1 for jet in goodJets if jet.mv1() > 0.7892])
      if not (btags >= 2): return False
      self.countEvent("btags", weight)

      # apply a cut on the transverse mass of the W boson decaying to leptons
      if not (AH.WTransverseMass(leadlepton, etmiss) > 30.0): return False
        
        
      #cuts for W, T and Z masses  
    
        sum_pt = 0
        Wmass  = 0
        Tmass  = 0
        Zmass  = 0
        
      for i in goodJets
          for j in goodJets
              for k in goodJets
                  for l in goodJets
                
                    jet1 = ROOT.TLorentzVector()
                    jet2 = ROOT.TLorentzVector()
                    jet3 = ROOT.TLorentzVector()
                    jet4 = ROOT.TLorentzVector()
                    
                    jet1.SetPtEtaPhiM(jet.pt(),jet.eta(),jet.phi(),jet.M())
                    jet2.SetPtEtaPhiM(jet.pt(),jet.eta(),jet.phi(),jet.M())
                    jet3.SetPtEtaPhiM(jet.pt(),jet.eta(),jet.phi(),jet.M())
                    jet4.SetPtEtaPhiM(jet.pt(),jet.eta(),jet.phi(),jet.M())
                    
                    
                    if (jet1 + jet2 + jet3).Pt()/1000 > sum_pt:
                        sum_pt = (jet1 + jet2 + jet3).Pt()/1000 
                        Wmass = (jet1 + jet2 + jet3).M()/1000 
                        
                        jet12 = (jet1 + jet2).Pt()/1000
                        jet23 = (jet2 + jet3).Pt()/1000
                        jet13 = (jet1 + jet3).Pt()/1000
                        
                        if jet12 > jet23 & jet12 > jet23:
                            j1, j2, j3 = jet12, jet23, jet13
                        if jet23 > jet12 & jet23 > jet13:
                            j1, j2, j3 = jet23, jet13, jet12
                        if jet13 > jet23 & jet13 > jet12:
                            j1, j2, j3 = jet23, jet13, jet12
                        

      Jet1 = ROOT.TLorentzVector()
      Jet2 = ROOT.TLorentzVector()
      Jet3 = ROOT.TLorentzVector()
      Jet4 = ROOT.TLorentzVector()
                    
      Jet1.SetPtEtaPhiM(j1.pt(),j1.eta(),j1.phi(),j1.M())
      Jet2.SetPtEtaPhiM(j2.pt(),j2.eta(),j2.phi(),j2.M())
      Jet3.SetPtEtaPhiM(j3.pt(),j3.eta(),j3.phi(),j3.M())
      Jet4.SetPtEtaPhiM(jet4.pt(),jet4.eta(),jet4.phi(),jet4.M())
        
      Tmass = (Jet1 + Jet2).Pt()/1000  
      
      Zmass = (Jet1.Pt + Jet2.Pt + Jet3.Pt + Jet4.Pt + etmiss.et + leadlepton.Pt)/1000  
        
        
    
      # Histograms detailing event information
      self.hist_vxp_z.Fill(eventinfo.primaryVertexPosition(), weight)
      self.hist_pvxp_n.Fill(eventinfo.numberOfVertices(), weight)

      # histograms for the W boson properties
      self.hist_WtMass.Fill(AH.WTransverseMass(leadlepton, etmiss), weight)

      # histograms for missing et
      self.hist_etmiss.Fill(etmiss.et(),weight)  

      # histograms detailing lepton information
      self.hist_leptn.Fill(len(goodLeptons), weight)
      self.hist_leptpt.Fill(leadlepton.pt(), weight)
      self.hist_lepteta.Fill(leadlepton.eta(), weight)
      self.hist_leptE.Fill(leadlepton.e(), weight)
      self.hist_leptphi.Fill(leadlepton.phi(), weight)
      self.hist_leptch.Fill(leadlepton.charge(), weight)
      self.hist_leptID.Fill(leadlepton.pdgId(), weight)
      self.hist_lepz0.Fill(leadlepton.z0(), weight)
      self.hist_lepd0.Fill(leadlepton.d0(), weight)      
      self.hist_leptptc.Fill(leadlepton.isoptconerel30(), weight)
      self.hist_leptetc.Fill(leadlepton.isoetconerel20(), weight)
      
      # histograms detailing jet information
      self.hist_njets.Fill(len(goodJets), weight)
      [self.hist_jetm.Fill(jet.m(), weight) for jet in goodJets]
      [self.hist_jetspt.Fill(jet.pt(), weight) for jet in goodJets]
      [self.hist_jetJVF.Fill(jet.jvf(), weight) for jet in goodJets]
      [self.hist_jeteta.Fill(jet.eta(), weight) for jet in goodJets]
      [self.hist_jetmv1.Fill(jet.mv1(), weight) for jet in goodJets]
      return True

      # histograms for W, t and Z masses
      [self.hist_W_mass.Fill(Wmass, weight) for jet in goodJets]
      [self.hist_T_mass.Fill(Tmass, weight) for jet in goodJets]
      [self.hist_Z_mass.Fill(Zmass, weight) for jet in goodJets]    
    
    
  def finalize(self):
      pass

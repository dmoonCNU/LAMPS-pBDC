void drawplot(){
  TFile *f = new TFile("data.root","READ");
  TTree *event = (TTree*)f->Get("event");
  event->Draw("edep1>>h");
  //h->Draw();
}


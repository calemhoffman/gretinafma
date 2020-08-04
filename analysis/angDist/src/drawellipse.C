void drawellipse()
{

double ellipse1[5];
double ellipse2[5];
double ellipse3[5];

ellipse1[0]=0.0867347;
ellipse1[1]=0.163265;
ellipse1[2]=0.407056;
ellipse1[3]=0.146783;
ellipse1[4]=-10.8527;


ellipse2[0]=-0.0357142;
ellipse2[1]=-0.380952;
ellipse2[2]=0.621349;
ellipse2[3]=0.342736;
ellipse2[4]=-18.7161;


ellipse3[0]=-0.137755;
ellipse3[1]=-0.0408163;
ellipse3[2]=0.396871;
ellipse3[3]=0.0402361;
ellipse3[4]=0.995226;




	const Int_t n1=39;
	Double_t xx1[n1], yy1[n1];
	Int_t i=0;
	ifstream in1;
	in1.open("1-2-0.dat",ios::in);
	while (in1.good())
	{
		in1>>xx1[i]>>yy1[i];
		i++;

	}

	in1.close();

	TGraph *g1 = new TGraph(n1,xx1,yy1);
        g1->GetYaxis()->SetRangeUser(-1.0,0.7);
        g1->GetXaxis()->SetRangeUser(-5.0,1.0);

   g1->GetXaxis()->SetTitle("A_{2}");
//   g1->GetXaxis()->SetRange(0,101);
   g1->GetXaxis()->CenterTitle(true);
   g1->GetXaxis()->SetLabelFont(42);
   g1->GetXaxis()->SetLabelSize(0.05);
   g1->GetXaxis()->SetTitleSize(0.06);
   g1->GetXaxis()->SetTitleOffset(0.67);
   g1->GetXaxis()->SetTitleFont(42);
   g1->GetYaxis()->SetTitle("A_{4}");
   g1->GetYaxis()->CenterTitle(true);
   g1->GetYaxis()->SetLabelFont(42);
   g1->GetYaxis()->SetLabelSize(0.05);
   g1->GetYaxis()->SetTitleSize(0.06);
   g1->GetYaxis()->SetTitleOffset(0.78);
   g1->GetYaxis()->SetTitleFont(42);

        g1->SetMarkerSize(0);        

        TCanvas *c = new TCanvas("c","c",800,600);
        g1->Draw("A*"); 
   //     c->SetGrid(1, 1);
                TEllipse *e1 = new TEllipse(ellipse1[0], ellipse1[1], // "x0", "y0"
                                ellipse1[2], ellipse1[3], // "a", "b"
                                0, 360,
                                ellipse1[4]); // "theta" (in degrees)
                e1->SetFillStyle(0); // hollow
                e1->SetLineColor(2);
                e1->SetLineWidth(2);
                e1->SetLineStyle(7);
                e1->Draw();

                TEllipse *e2 = new TEllipse(ellipse2[0], ellipse2[1], // "x0", "y0"
                                ellipse2[2], ellipse2[3], // "a", "b"
                                0, 360,
                                ellipse2[4]); // "theta" (in degrees)
                e2->SetFillStyle(0); // hollow
                e2->SetLineColor(4);
                e2->SetLineWidth(2);
                e2->SetLineStyle(7);
                e2->Draw();

                TEllipse *e3 = new TEllipse(ellipse3[0], ellipse3[1], // "x0", "y0"
                                ellipse3[2], ellipse3[3], // "a", "b"
                                0, 360,
                                ellipse3[4]); // "theta" (in degrees)
                e3->SetFillStyle(0); // hollow
                e3->SetLineColor(8);
                e3->SetLineWidth(2);
                e3->SetLineStyle(7);
                e3->Draw();


	const Int_t n2=1;
	Double_t xx2[n2], yy2[n2];
        xx2[0]=0.102;
        yy2[0]=0.009;
	TGraph *g2 = new TGraph(n2,xx2,yy2);
        g2->SetMarkerStyle(8);
        g2->SetMarkerSize(1.5);
        g2->Draw("P"); 



//
  double xx10[1], yy10[1];
  double exx10[1], eyy10[1];
      const int n10=1;
        xx10[0]=0.135;
        yy10[0]=0.416; 

        exx10[0]=0.118;
        eyy10[0]=0.154; 

	TGraphErrors *g10 = new TGraphErrors(n10,xx10,yy10,exx10,eyy10);
        g10->SetMarkerStyle(20);
        g10->SetMarkerSize(1);
        g10->Draw("LP");

   TPaveText *pt = new TPaveText(0.4372362,0.9343728,0.5627638,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   pt->Draw();
   TLine *line = new TLine(-0.7139404,0.6296296,-0.5920849,0.6296296);
   line->SetLineColor(2);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(-0.5853151,0.5962963,"2-2-0");
   tex->SetTextColor(2);
   tex->SetTextFont(42);
   tex->SetTextSize(0.05226481);
   tex->SetLineWidth(2);
   tex->Draw();
   line = new TLine(-0.7139404,0.5333333,-0.596598,0.5333333);
   line->SetLineColor(8);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(-0.716197,0.4444444,-0.5943415,0.4444444);
   line->SetLineColor(4);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(-0.5875717,0.5074074,"3-2-0");
   tex->SetTextColor(8);
   tex->SetTextFont(42);
   tex->SetTextSize(0.05226481);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-0.5898283,0.4185185,"1-2-0");
   tex->SetTextColor(4);
   tex->SetTextFont(42);
   tex->SetTextSize(0.05226481);
   tex->SetLineWidth(2);
   tex->Draw();
   
      tex = new TLatex(-0.5920849,0.3296296,"4-2-0");
   tex->SetTextFont(42);
   tex->SetTextSize(0.05226481);
   tex->SetLineWidth(2);
   tex->Draw();

   graph1 = new TGraph(1);
   graph1->SetName("Graph1");
   graph1->SetTitle("Graph1");
   graph1->SetFillColor(1);
   graph1->SetMarkerStyle(8);
   graph1->SetMarkerSize(1.5);
   graph1->SetPoint(0,-0.6642955294,0.36);

   graph1->Draw("p");
        c->Modified(); c->Update(); // make sure it's really drawn


}

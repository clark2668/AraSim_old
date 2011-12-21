////////////////////////////////////////////////////////////////////////////////////////////////
//class Primaries:
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PRIMARIES_H_
#define PRIMARIES_H_

#include "TRandom3.h" 
#include <iostream>
#include "TObject.h"

#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TF3.h"
#include "TH2D.h"
#include "Vector.h"
#include <vector>
#include "Position.h"

//--------------------------------------------------
// class Interaction;
// class Primaries;
//-------------------------------------------------- 
class IceModel;
class Counting;
class Settings;
class Detector;
class Ray;
class Primaries;
class Spectra;

//using namespace std;
using std::string;
//
using std::cout;




class Y {
	//Code from Connolly Calc 2011.
	private:
		TF1* ffrac; // fraction of events in the low y region.
		TF1* fC1_high[2][2]; // parameterization of C1 in high y region
  	
		TF1 *fC1_low; // parameterization of C1 in the low y region.

		TF1 *fC2; // parameterization of C2 in the low y region.

		TF3* fy0_low; // for picking y0. 
		TF2* fy0_high;  // for picking y0.
		TRandom3 Rand3;

	public:
		Y();
		double pickY(int NU,int CURRENT,double e); // pick an inelasticity
		// NU=0: nubar, NU=1: nu
		// CURRENT=0: CC, CURRENT-1: NC

/*
		const static double miny_low=0.00002;//2.E-5
		const static double maxy_low=0.001;
		const static double miny_high=0.001;
		const static double maxy_high=1.;
*/
		static const double miny_low;//2.E-5
		static const double maxy_low;
		static const double miny_high;
		static const double maxy_high;


                ClassDef(Y,1);

};//Y

class Primaries {

 private:
  TRandom3 Rand3;

	TH2D *m_hsigma;
	TCanvas *m_csigma;
	Y *m_myY;
	int run_old_code;

public:
	double ymin_low, ymax_low, ymin_high, ymax_high;
	double A_low[4];//same for any nu_nubar and current type.
	double A0_high[2][2];
	double A1_high[2][2];
	double A2_high[2][2];
	double A3_high[2][2];
	double b0, b1; 

	TF1* m_fy[2][2];
	TF1* m_fsigma[2][2];

	double c0[2][2];
	double c1[2][2];
	double c2[2][2];
	double c3[2][2];
	double c4[2][2];

	static const int NSIGMAS=2;// number of possible cross section models
	// 0=Gandhi et al.
	// 1=Connolly et al. 2011
	double mine[NSIGMAS];// minimum energy for cross section parametrizations, in eV
	double maxe[NSIGMAS]; //max

	Primaries();//constructor //default
	~Primaries();//destructor //default
	//*primary1 must be manually deleted in icemc for deconstructor to actually be called.

	int GetSigma(double pnu,double& sigma,double &len_int_kgm2,Settings *settings1,int nu_nubar,int currentint);//not static
	double Gety(Settings *settings1,double pnu,int nu_nubar,int currentint);
	double Getyweight(double pnu,double y,int nu_nubar,int currentint);
	string GetCurrent();
	string GetNuFlavor();


        ClassDef(Primaries,1);

};//Primaries

class Interaction  {

 private:



  Vector tmp_banana; //Intermediate vector

  //For banana plot
 
 // static const double RADDEG_TMP=3.14159/180.;
 static const double nu_banana_theta_angle;// don't let me use RADDEG which is annoying 
 

 static const double altitude_nu_banana;//Depth of interaction of banana neutrino
 

 static const double lat_nu_banana; 
 static const double lon_nu_banana;
 

 static const double banana_slopey;//Turn slopyness off for banana plots (SLOPEY)
 static const double nu_banana_phi_angle; 
 


 public:

 static const double phi_nu_banana; //Location in phi

 static const double banana_observation_distance;//How far from the surface above the interaction are we when we measure the voltages? (meters) Note: Should be at least 100000 for best results.
 static const double theta_nu_banana;//Location of banana neutrino in theta
 double banana_phi_obs;
 Vector banana_obs; //Vector from the neutrino interaction to the observation point
 Interaction(); // default constructor
 Interaction(string inttype,Primaries *primary1,Settings *settings1,int whichray,Counting *count1);

 Interaction (IceModel *antarctica, Detector *detector, Settings *settings1, int whichray, Counting *count1, Primaries *primary1, Spectra *spectra); // constructor for setting posnu, nnu, etc
//--------------------------------------------------
//  Interaction (int mode, Ray *ray, Interaction *interaction1, IceModel *antarctica, Detector *detector); // constructor for setting posnu, nnu, etc
//-------------------------------------------------- 

 void PickAnyDirection();

  int noway;
  int wheredoesitleave_err;
  int neverseesice;
  int wheredoesitenterice_err;
  int toohigh;
  int toolow;

  // Eugene added PickUnbiased result
//--------------------------------------------------
//   int pickunbiased;
//-------------------------------------------------- 
        
  int pickposnu;    // : 0 for fail picking posnu, nnu  : 1 sucess picking posnu, nnu
  
  // Eugene added for test ray solver result store
  //
  int ray_solver_toggle;    // : 0 no solution, : 1 solution exists
  std::vector < std::vector <double> > ray_outputs; // array of results. path length, view angle, receipt angle

  //
  //
  // calculating posnu part moved from IceModel
  int PickUnbiased (IceModel *antarctica);
  int WhereDoesItLeave( const Position &posnu, const Vector &ntemp, IceModel *antarctica, Position &r_out);
  int WhereDoesItEnterIce ( const Position &posnu, const Vector &nnu, double stepsize, Position &r_enterice, IceModel *antarctica);
  int WhereDoesItExitIce ( const Position &posnu, const Vector &nnu, double stepsize, Position &r_enterice, IceModel *antarctica);
  void FlattoEarth ( IceModel *antarctica, double X, double Y, double D);
  void PickNear(IceModel *antarctica, Detector *detector, Settings *settings1);
  // end move from IceModel
  //


  double pathlength_inice;

 Vector nnu;  // direction of neutrino (+z in south pole direction)
 double costheta_nutraject; //theta of nnu with earth center to balloon as z axis 
 double phi_nutraject; //phi of nnu with earth center to balloon as z axis

  Position r_in; // position where neutrino enters the earth
  Position r_enterice; // position where neutrino enters the ice
  Position nuexit; // place where neutrino would have left the earth
Position nuexitice; // place where neutrino would have left the ice
  double chord;  // chord in m from earth entrance to rock-ice boundary
  double logchord; // log_10 of chord length earth entrance to where it enters ice
  double weight_bestcase; // what weight1 would be if whole earth had density of crust - for quick and dirty calculation of best case scenario
  double chord_kgm2_bestcase; // the chord the neutrino would traverse if it all was crust density
  double chord_kgm2_ice; // from ice entrance to interaction point
  double d1;  //same as chord in m (earth entrance to rock-ice boundary)
  double d2;  // ice-rock boundary to interaction point in m


static const double pnu_banana;
static const double banana_y;//Elasticity.  0.2 is an average number.
double banana_weight;//Weight measurement locations to account for phase space
 double banana_theta_obs;
 double banana_volts;//Total voltage measured at a spot on the sky
static const double banana_signal_fluct;//Turn off noise for banana plots (settings1->SIGNAL_FLUCT) (shouldn't matter)
 static const double banana_sigma;//NSIGMA in the case of a banana plot
 
 double pnu;    // energy of neutrino

  void  setNuFlavor(Primaries *primary1,Settings *settings1,int whichray,Counting *count1);
 void setCurrent(Primaries *primary1);
  Position posnu;
  Position posnu_down;
string  nuflavor;                   // neutrino flavor
  string  current;                    //  CC or NC?
int nuflavorint;                // Added by Stephen for output purposes
  int currentint;                 // Ditto - Stephen
  

  double surface_over_banana_nu;
 
 
   string banana_current;  //Force interaction to be a neutral current

string banana_flavor; //Force interaction to be a muon neutrino
Vector nnu_banana; //Forced neutrino direction 

  Position nu_banana;  //The forced interaction point of the neutrino for the banana plots
Position nu_banana_surface; //The location of the surface above the forced neutrino interaction point  

// phase space weighting
double dtryingdirection; //weighting factor: how many equivalent tries each neutrino counts for after having reduced angular phase space for possibly detectable events
double dnutries; //product of dtryingdirection and dtryingposition

 double altitude_int;// depth of interaction
 double altitude_int_mirror;//depth of the mirror point of interaction.

 double r_fromballoon[2]; // distance from interaction to balloon for each ray

 double r_fromballoon_db; // same, for double bangs
 double r_exit2bn; // exit to balloon
 double r_exit2bn_measured; // exit to balloon deduced from measured theta
 int iceinteraction;// whether or not there is an interaction in the ice

 ClassDef(Interaction,1);


};//Interaction
#endif

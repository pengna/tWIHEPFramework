/******************************************************************************
 * MCTop.cpp                                                                  *
 *                                                                            *
 * Container for a MCTop                                                      *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of MCTop class                                     *
 *    MCTop()                           -- Default Constructor                *
 *    MCTop()                           -- Parameterized Constructor          *
 *    MCTop()                           -- Constructor with Particle          *
 *    ~MCTop()                          -- Destructor                         *
 *    Clear()                            -- Set contents to default           *
 *    Fill()                             -- Fill top from event tree          *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const MCTop            *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of MCTop class                                        *
 *                                                                            *
 * History                                                                    *
 *      15 May 2007 - Created by J. Holzbauer                                 *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Particles/Truth/MCTop.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCW.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

// Integrate classes into the Root system
ClassImp(MCTop)

/******************************************************************************
 * MCTop::MCTop()                                                             *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  MCTop::MCTop()
{

} //MCTop()

/******************************************************************************
 * MCTop::~MCTop()                                                            *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
MCTop::~MCTop()
{

} //~MCTop()


/******************************************************************************
 * MCTop::MCTop(const MCTop& other)                                           *
 *                                                                            *
 * Copy constructor MCTop const                                               *
 *                                                                            *
 * Input:  MCTop                                                              *
 * Output: None                                                               *
 ******************************************************************************/
MCTop::MCTop(const MCTop& other): MCParticle(other)
{

} //MCTop()

/******************************************************************************
 * MCTop::MCTop(const MCTop& other)                                           *
 *                                                                            *
 * Copy constructor MCParticle const                                          *
 *                                                                            *
 * Input:  MCTop                                                              *
 * Output: None                                                               *
 ******************************************************************************/
MCTop::MCTop(const MCParticle& other): MCParticle(other)
{ 

} //MCTop

/******************************************************************************
 * MCTop& MCTop::operator+=(const MCTop& other)                               *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  MCTop                                                              *
 * Output: MCTop                                                              *
 ******************************************************************************/
MCTop& MCTop::operator+=(const MCTop& other)
{
  
  MCParticle::operator+=(other);
   return *this;
} //+=

/******************************************************************************
 * MCTop& MCTop::operator+(const MCTop& other)                                *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  MCTop                                                              *
 * Output: MCTop                                                              *
 ******************************************************************************/
MCTop MCTop::operator+(const MCTop& other)
{

  MCParticle::operator+(other);
  return *this;
} //+

/******************************************************************************
 * MCTop& MCTop::operator=(const Top& other)                                  *
 *                                                                            *
 * Overload = MCParticle                                                      *
 *                                                                            *
 * Input:  MCParticleicle::Clear();                                           *
 * Output: MCTop                                                              *
 ******************************************************************************/
MCTop& MCTop::operator=(const MCParticle& other)
{
  
  MCParticle::operator=(other);
  return *this;
} // MCParticle

/******************************************************************************
 * MCTop& MCTop::operator=(const MCTop& other)                                *
 *                                                                            *
 * Overload = const MCTop                                                     *
 *                                                                            *
 * Input:  MCTop                                                              *
 * Output: MCTop                                                              *
 ******************************************************************************/
MCTop& MCTop::operator=(const MCTop& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCTop

/******************************************************************************
 * MCTop& MCTop::operator=(MCTop& other)                                      *
 *                                                                            *
 * Overload = non-const MCTop                                                 *
 *                                                                            *
 * Input:  MCTop                                                              *
 * Output: MCTop                                                              *
 ******************************************************************************/
MCTop& MCTop::operator=(MCTop& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCTop()

/******************************************************************************
 * void MCTop::Fill(TruthTree *truthTree, Int_t iE)                           *
 *                                                                            *
 * Fill MCTop vector from tree                                                *
 *                                                                            *
 * Input:  Event Tree                                                         *
 * Output: None                                                               *
 ******************************************************************************/
void MCTop::FillTop(TruthTree *trtr, int iE)
{

  MCParticle::Fill(trtr, iE);

} //Fill()


Bool_t MCTop::TopIsHadronicDecay(const MCTop Ptemp, std::vector<MCParticle>& MCParticles) const
{
	//cout<<"Ptemp.Status() = "<<Ptemp.Status()<<endl;
	//if(Ptemp.Status()==2){
		for(int d_index=0; d_index< Ptemp.BdaughtIndices().size(); d_index++){
			const MCParticle daught = MCParticles.at(Ptemp.BdaughtIndices().at(d_index));
			int daughtid = daught.AbsPdgId();
		//	cout<<"daughtid ="<<daughtid<<endl;
			if ( daughtid == 24 && IsHadronicDecay(daught,MCParticles) )return true;
		}
		return false;

//}
// return false;

}


//Find bquark from  gen top particle decay final states
const MCParticle MCTop::bquark(const MCTop Ptemp, std::vector<MCParticle>& MCParticles) const
{


	 for(int d_index=0; d_index< Ptemp.BdaughtIndices().size(); d_index++){
                        const MCParticle daught = MCParticles.at(Ptemp.BdaughtIndices().at(d_index));
                        int daughtid = daught.AbsPdgId();
			if(daughtid==5) return daught;
}

return Ptemp;

}

const MCParticle MCTop::WBoson(const MCTop Ptemp, std::vector<MCParticle>& MCParticles) const
{


         for(int d_index=0; d_index< Ptemp.BdaughtIndices().size(); d_index++){
                        const MCParticle daught = MCParticles.at(Ptemp.BdaughtIndices().at(d_index));
                        int daughtid = daught.AbsPdgId();
                        if(daughtid==24 ) return daught;
}

return Ptemp;

}

//Find jets from W 

const std::vector<MCParticle>  MCTop::Wjets(const MCTop Ptemp, std::vector<MCParticle>& MCParticles) const
{
std::vector<MCParticle> Wdecayjets;
Wdecayjets.clear();
 const MCW WfromTop= WBoson(Ptemp,MCParticles);       
 const MCW W= GetGenPartcileNoFsr(WfromTop,MCParticles);       
         for(int d_index=0; d_index< W.BdaughtIndices().size(); d_index++){
                        const MCParticle daught = MCParticles.at(W.BdaughtIndices().at(d_index));
			Wdecayjets.push_back(daught);
}
return Wdecayjets;

}








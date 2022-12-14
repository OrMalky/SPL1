#include <iostream>
#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) , mCoalitions()
{
    for(Agent a: agents)
    {
        Coalition c(a.getId());
        Party* p = &getParty(a.getPartyId());
        p->setState(Joined);
        c.addParty(p);
        c.addPartyOffer(p->getGetId());
        mCoalitions.push_back(c);
    }
}

void Simulation::step()
{
    //Parties Step
    for(int i = 0; i < mGraph.getNumVertices(); i++)
    {
        mGraph.getParty(i).step(*this);
    }
    std::cout << "Parties step successful" << std::endl;

    //Agents Step
    for(int unsigned i=0; i < mAgents.size(); i++)
    {
        mAgents[i].step(*this);
    }
    std::cout << "Agents step successful" << std::endl;
}

bool Simulation::shouldTerminate() const
{
    //Is there a Coalition with 61 mandates or more?
    for(int unsigned i=0; i<mCoalitions.size(); i++)
    {
        if(mCoalitions[i].getTotalMandates() >= 61)
            return true;
    }

    //Are all parties already Joined?
    for(int i=0; i<mGraph.getNumVertices(); i++)
    {
        if(mGraph.getParty(i).getState() != Joined)
            return false;
    }
    return true;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party& Simulation::getParty(int partyId)
{
    return mGraph.getParty(partyId);
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraph()
{
    return mGraph;
}

Coalition& Simulation::getCoalition(int id)
{
    return mCoalitions[id];
}

void Simulation::cloneAgent(int agentId, int partyId)
{
    Agent newAgent(mAgents[agentId], mAgents.size(), partyId);
    mAgents.push_back(newAgent);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalition;
    for(int unsigned c = 0; c < mCoalitions.size(); c++)
    {
        vector<int> coalition;
        for(int unsigned p = 0; p < mCoalitions[c].getParties().size(); p++)
        {
            coalition.push_back(mCoalitions[c].getParties()[p]->getGetId());
        }
        partiesByCoalition.push_back(coalition);
    }
    return partiesByCoalition;
}

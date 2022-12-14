#include "../include/Agent.h"
#include "../include/Simulation.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) :
    mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCoalitionId(agentId)
{
    std::cout << "agent created " << mAgentId  << " " << this << " SP: " << mSelectionPolicy << "coalition" << mCoalitionId << std::endl;
}

Agent::Agent(const Agent& toClone, int newId, int partyId) :
    mAgentId(newId), mPartyId(partyId), mSelectionPolicy(toClone.getSelectionPolicy()->clone()), mCoalitionId(toClone.getCoalitionId())
{
    std::cout << "agent created " << mAgentId  << " " << this << "coalition" << mCoalitionId << std::endl;
}

Agent::Agent(const Agent& toClone) : mAgentId(toClone.getId()), mPartyId(toClone.getPartyId()), mSelectionPolicy(toClone.getSelectionPolicy()->clone()) ,mCoalitionId(toClone.getCoalitionId())
{
    std::cout << "agent copied " << mAgentId  << " " << this << " SP: " << mSelectionPolicy << "coalition" << mCoalitionId << std::endl;
}

Agent& Agent::operator=(const Agent& other)
{
    mAgentId = other.getId();
    mPartyId = other.getPartyId();
    mSelectionPolicy = other.getSelectionPolicy();
    mCoalitionId = other.getCoalitionId();
    return *this;
}

Agent::~Agent()
{
    
    std::cout << "deleteding sp " << mSelectionPolicy << std::endl;
    delete mSelectionPolicy;
    std::cout << "agent deleted " << mAgentId  << " " << this << std::endl;
    
}

Agent::Agent(Agent&& a) : mAgentId(a.getId()), mPartyId(a.getPartyId()), mSelectionPolicy(a.getSelectionPolicy()) ,mCoalitionId(a.getCoalitionId())
{
    a.nullify();
}

Agent& Agent::operator=(Agent&& a)
{
    if(this != &a)
    {
        mAgentId = a.getId();
        mPartyId = a.getPartyId();
        mSelectionPolicy = a.getSelectionPolicy();
        mCoalitionId = a.getCoalitionId();
        a.nullify();
    }
    return *this;
}

void Agent::nullify()
{
    mAgentId = -1;
    mPartyId = -1;
    mSelectionPolicy = nullptr;
    mCoalitionId = -1;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalitionId() const
{
    return mCoalitionId;
}

SelectionPolicy* Agent::getSelectionPolicy() const
{
    return mSelectionPolicy;
}

void Agent::step(Simulation &sim)
{
    int toOffer = mSelectionPolicy -> select(sim, *this);
    if(toOffer > -1)
    {
        std::cout << &sim.getParty(toOffer) << std::endl;
        Offer newOffer(mCoalitionId, mAgentId);
        sim.getParty(toOffer).takeOffer(newOffer, sim.getCoalition(mCoalitionId));
        sim.getCoalition(mCoalitionId).addPartyOffer(toOffer);
    }
}



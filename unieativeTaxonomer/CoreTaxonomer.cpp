//
//  CorseTaxonomer.cpp
//  unieativeTaxonomer
//
//  Created by Younies Mahmoud on 8/8/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "CoreTaxonomer.hpp"


CoreTaxonomer::CoreTaxonomer(vector<YRJUnieative *> & yrjUnieativeVector , string hash)
{
    //setting up the hash
    updateHashValue(hash);
    
    this->yrjUnieativeVector = yrjUnieativeVector;
    //to calculate the size of the whole database hashed kmers
    this->coreHashNodesSize = 0;
    for(YRJUnieative* node : yrjUnieativeVector)
        this->coreHashNodesSize += node->hashedKmersSize;
    
    //to build the hashed database
    this->coreHashedNodes.resize(this->coreHashNodesSize);
    
    //compy files in the coreHahsdNodes
    this->fillAllTheCoreData();
    
    
    //sort all the core data
   // sort(this->coreHashedNodes.begin(), this->coreHashedNodes.end());
}



CoreTaxonomer::~CoreTaxonomer()
{
    
    
}




//merge yrjUnieative inside the the core data

void CoreTaxonomer::copyYRJUnieativeInside(YRJUnieative & yrjUnieative)
{
    yrjUnieative.fillTheHashedNodesVector();
    for(LONGS i = 0  , n = yrjUnieative.hashedKmers.size() ; i < n ; ++ i)
        this->coreHashedNodes[this->startIndex++] = yrjUnieative.hashedKmers[i];
    yrjUnieative.clearAllTheData();
}



void CoreTaxonomer::fillAllTheCoreData()
{
    this->startIndex = 0;
    for (LONGS i = 0 , n = this->yrjUnieativeVector.size(); i < n ; ++i)
    {
        this->copyYRJUnieativeInside(*(this->yrjUnieativeVector[i]));
    }
    
    this->startIndex = 0;
    
}


pair<LONGS, LONGS>  CoreTaxonomer::getThePlaceOfKmer(INT rawKmer)
{
    LONGS start = 0 , end = this->coreHashNodesSize - 1 , mid  = (start + end)/2;
    
    while (end >= start)
    {
        mid  = (start + end)/2;
        if(this->coreHashedNodes[mid].rawKmer == rawKmer)
            break;
        else if (this->coreHashedNodes[mid].rawKmer > rawKmer)
            end = mid - 1;
        else
            start = mid + 1;
    }
    
    
    LONGS newEndStart =  mid ,  newEndEnd  = mid;
    
    //for setting the start
    while ( this->coreHashedNodes[start].rawKmer  != rawKmer)
    {
        ++start; // take a step to the goal
        mid = (start + newEndStart) / 2;
        
        if(this->coreHashedNodes[mid].rawKmer == rawKmer)
            newEndStart = mid;
        else
            start = mid + 1;
    }
    
    
    
    //for setting the end
    
    while (this->coreHashedNodes[end].rawKmer != rawKmer)
    {
        --end; //take one step to the goal and prevent the infinity loop!
        mid = (end + newEndEnd)/2;
        if(this->coreHashedNodes[mid].rawKmer == rawKmer)
            newEndEnd = mid;
        else
            end = mid  - 1;
    }
    
    return make_pair(start, end);
    
}




/**
 Implementing the function that convert the kmer from LONGS kmer to the corresponding rawKmer and hashedPart which is the hidden part
 */

pair<INT, INT> CoreTaxonomer::getTheHashedKmer(LONG kmer)
{
    pair<INT, INT> ret;
    ret.first = 0 ;
    ret.second = 0;
    
    LONG tempHash = this->reverseHashBits;
    kmer = reverseKmer(kmer);
    
    while(tempHash > 0)
    {
        int indicator = tempHash % 2; // take the last bit from the temp reversed hash
        int kmerBit = kmer%2; // take the last bit from the reversed kmer
        tempHash /= 2;
        kmer /= 2;
        if (indicator == 1)
        {
            ret.first <<= 1;
            ret.first |= kmerBit;
        }
        else
        {
            ret.second <<= 1;
            ret.second |= kmerBit;
        }
    }
    
    return ret;
}



void CoreTaxonomer::updateHashValue(string hash)
{
    vector<char> charHash;
    for(LONGS i = 0 , n = hash.size() ; i < n ; ++ i)
    {
        charHash.push_back(hash[i]);
        charHash.push_back(hash[i]);
    }
    string newHash(charHash.begin() , charHash.end());
        this->hash = newHash;
    
    this->reverseHashBits = 0;
    
    string reverseHash = newHash;
    reverse(reverseHash.begin(), reverseHash.end());
    
    
    for(LONGS i = 0 , n = reverseHash.size() ; i < n  ; ++i)
    {
        this->reverseHashBits <<= 1;
        if(reverseHash[i] == '#')
            this->reverseHashBits |= 1;
    }
}





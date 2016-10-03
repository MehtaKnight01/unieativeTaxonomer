//
//  Kraken.cpp
//  unieativeTaxonomer
//
//  Created by Younies Mahmoud on 10/3/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "Kraken.hpp"



SHORT Unieative::getLCA(LONG kmer , int & differences)
{
    
    
    unordered_set<short> hits;
    for(auto hash: this->Hashes)
    {
        auto tempHits = getNumberOfDifference(hash->getIndexStream(), hash->getDataStream(), hash, kmer);
        
        for(auto pair : tempHits)
            if(pair.second <= differences)
                hits.insert(pair.first);
        
    }
    
    vector<short> uniqueHits(hits.size());
    
    copy( hits.begin() , hits.end() , uniqueHits.begin() );
    
    return this->tree->getGlobalLCA(uniqueHits);
    
    
}
















INT Unieative::getFinalUID(YRJObject * yrjObject , int differnces)
{
    unordered_set<SHORT , int> LCAs;
    
    for(auto kmer : yrjObject->kmersVector)
    {
        auto  lca  = this->getLCA(kmer, differnces);
        if(LCAs.count(lca))
            ++LCAs[lca];
        else
            LCAs[lca] = 1;
    }
}












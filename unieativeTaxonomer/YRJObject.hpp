//
//  YRJObject.hpp
//  unieativeTaxonomer
//
//  Created by Younies Mahmoud on 8/8/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef YRJObject_hpp
#define YRJObject_hpp

#include "headers.h"


class YRJObject
{
    LONGS kmerLength;
    LONGS numOfKmers;
    string path_to_file;
    short index;
    

    ifstream * fileStream;
    
    const int kmerStandardLength = 31;
    const LONG maxLONG = ULONG_MAX;
    const LONG maxOnes31 = (maxLONG << 2) >> 2;
    
public:
    
    
    short speciesParent = -2;
    short genusParent = -2;

    YRJObject(string path , short index);
    
    YRJObject(string &shortRead );

    YRJObject(vector<string> &shortReads  );
    
    ~YRJObject();
    
    vector<LONG>  kmersVector;
    short getIndex();
    LONGS getNumOfKmers();
    
    void fillTheKmersVector();
    
    void  clearTheCompleteKmers();
    
    bool openFileStream();
    LONG readAKmer();
    void closeFileStream();
    
    string getMeThePath();
    
    LONG getLeastCanonicalKmer(LONG kmer);
    
    void fillKmersFromShortRead(vector<string> &shortRead);
    
    int getCorrespondingCode(char c);
    
    LONGS uid;
    short shorName;

    void fillTheHashKmer(vector<string> & shortReads ,  unordered_set<LONG> & hashKmers);


    
};

#endif /* YRJObject_hpp */

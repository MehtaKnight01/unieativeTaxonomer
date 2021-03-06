//
//  main.cpp
//  unieativeTaxonomer
//
//  Created by Younies Mahmoud on 8/8/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "headers.h"
#include "YRJObject.hpp"
#include "helpers.hpp"
#include "CoreTaxonomer.hpp"
#include "Tree.hpp"
#include "Configurations.h"
#include "TestingKrakenInDifferenceLevels.hpp"



#include "testingTheDatabase.hpp"
#include "countingTheHistogramDifferences.hpp"

#include "testingYRJ.hpp"



vector<short> getIndiciesesAtDifferences(vector<pair< short , short> > & shortWithDifferences ,int maxDifferences);


void buildingHashDatabase(string pattern);

void testTheDatabaseMillionKmer();

int main(int argc, const char * argv[])
{
    
    string path_to_output = "/export1/project/hondius/testingUnieative/results/firstTrial.txt";
    //databaseTesting();
    
    
   // calulateTheDifferences(path_to_the_tree, path_to_the_hashed_databases, argv[1], path_to_the_yrj_databases, path_to_million_random, path_to_output + argv[2]);
    
    vector<string> patterns;
    patterns.emplace_back(pattern1);
    patterns.emplace_back(pattern11);
    patterns.emplace_back(pattern2);
    patterns.emplace_back(pattern3);
    patterns.emplace_back(pattern4);
    patterns.emplace_back(pattern5);
    //patterns.emplace_back(pattern66);
    
    
    
    //buildingHashDatabase(pattern66);
    
   //CalculateDifferencesDistributions(path_to_the_hashed_databases, patterns, path_to_the_yrj_databases, path_to_million_random, path_to_output);
    
    string s = "/Users/youniesmahmoud/Desktop/";
    string name_path =  s + "names.txt";
    string node_path = s + "nodes.txt";
    string gi_path = s + "gi_taxid_nucl.dmp";
    
    
    //BigTree * bigtree = new  BigTree(name_path  ,node_path, gi_path );

    
   //testEntiresimBA5(path_to_simBA5, path_to_simBA5_headers, path_to_the_names_dmp_file, path_to_the_nodes_dmp_file, path_Gi_File, path_to_output, path_to_the_hashed_databases, patterns, path_to_pruined_tree, 4);
    
    
    
 //testing new investigation
   /*
    for(int deep  = 0   ; deep < 5 ; deep++ )
    {
        //testing the tester
        Tester *tester = new Tester();
        tester->testYRJvector(deep);
        delete tester;
    }
*/
    
    /*BigTree * bigTree = new BigTree(path_to_the_names_dmp_file, path_to_the_nodes_dmp_file);
    
    
    LONGS uid = 6907;
    
    if(argc == 2)
    {
        uid = stol(argv[1]);
    }
    
    
    Tree * pruned = new Tree(path_to_pruined_tree);
    
    uid = pruned->getTheUIDFromShort(uid);
    
    while(uid > 1)
    {
        auto position = bigTree->uid_to_index(uid);
        auto level =  bigTree->getLevel(position);\
        
        cout << uid << "   " << position << "    " << level << endl;
        
        auto node = bigTree->getNodeFromIndex(position);
        
        uid = node.parentUID;
    }
    
    */
    
    buildingHashDatabase(pattern1R);
    
    return 0;
}



vector<short> getIndiciesesAtDifferences(vector<pair< short , short> > & shortWithDifferences ,int maxDifferences)
{
    vector<short> ret;
    
    for (LONGS i = 0 , n = shortWithDifferences.size() ; i < n ; ++i)
    {
        if(shortWithDifferences[i].second <= maxDifferences)
            ret.push_back(shortWithDifferences[i].first);
    }
    
    return ret;
}



void buildingHashDatabase(string pattern)
{
    
    //YRJObject * randomMillionKmers = new YRJObject(path_to_million_random , -1);
    //randomMillionKmers->fillTheKmersVector();
    
    //creating a tree object
    Tree * tree = new Tree(path_to_the_tree);
    
    //creating the hash
    Hash * hash = new Hash( pattern , path_to_the_hashed_databases );
    
    
    //creating the core data object
    CoreTaxonomer * core = new CoreTaxonomer( tree->getYRJobjects(path_to_the_yrj_databases) ,  hash);
    
    //write the core data
    core->writeTheCoreData();
}



void testTheDatabaseMillionKmer()
{
    /*
     ofstream final_output("/export1/project/hondius/unieative/trialOutput.txt" );
     
     final_output << "kmerIndex  kmer    Number_hits LCA    number_of_leaves    number_of_hitted_leaves GX_dem  GX  Uids_up_to_5\n";;
    
     
     //testing each kmer
     for (LONGS i = 0 , n = randomMillionKmers->kmersVector.size();  i < n ; ++i)
     {
         LONG kmer = randomMillionKmers->kmersVector[i];
     
         vector<pair< short , short> > shortWithDifferences = core->getShortNameFromKmer(kmer);
     
     
         vector<short> hittedShorts = getIndiciesesAtDifferences(shortWithDifferences, 31);
     
         if(!is_sorted( hittedShorts.begin(), hittedShorts.end()  ))
             sort(hittedShorts.begin(), hittedShorts.end());
     
         G_Statistics gStat = tree->calculateG_Statistics(kmer, tree->getGlobalLCA(hittedShorts), hittedShorts);
     
     
     
         LONGS number_Of_Hits = hittedShorts.size();
         final_output << i << "\t";
         final_output << randomMillionKmers->kmersVector[i] << "\t";
         final_output << number_Of_Hits << "\t";
     
         if(number_Of_Hits == 0)
         {
            final_output << "\n";
            continue;
         }
     
     
     
     
     final_output << gStat.LCA_global_Uid  << "\t";
     //final_output << tree->get_level(gStat.LCA_global) << "\t" ;
     final_output << gStat.number_of_leaves << "\t" ;
     final_output << gStat.number_of_hitted_leaves << "\t";
     final_output << gStat.demoneratorGX << "\t";
     final_output << gStat.GX << "\t";
     
     for(LONGS k = 0 , nnk = hittedShorts.size() ; k < nnk && k < 5 ; ++k)
     {
         final_output << tree->getTheUIDFromShort( hittedShorts[k] ) << "\t";
     }
     
     
     final_output << endl;
     
     final_output.flush();
     
     }
     
     final_output.close();
     
   */

}

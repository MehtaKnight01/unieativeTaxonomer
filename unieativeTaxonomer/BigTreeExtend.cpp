//
//  BigTreeExtend.cpp
//  unieativeTaxonomer
//
//  Created by Younies Mahmoud on 10/10/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//



#include "BigTree.hpp"

bool BigTree::isBothInGenusLevel(LONGS uid_first , LONGS uid_second){

    auto firstGenus = getGenusUID(uid_first);
    if(firstGenus == -1)
        return false;
    
    auto secondGenus = getGenusUID(uid_second);
    if(secondGenus == firstGenus)
        return true;
    else
        return false;

}




LONGS BigTree::getGenusUID(LONGS uid){
    
    if(uid < 2)
        return -1;
    
    while (uid != 1) {
        auto index = this->uid_to_index(uid);
        auto node  = this->getNodeFromIndex(index);
        auto level = get_level(node);
        if(level == "genus")// we should check this
            return uid;
        uid = node.parentUID;
    }
    
    return -1;
    
}

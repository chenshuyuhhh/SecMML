/*
 * @Author: Xinyu Tu
 * @Date: 2021-12-07 10:04:24
 * @LastEditors: Xinyu Tu
 * @LastEditTime: 2021-12-16 21:56:17
 */

#include <cstdio>
#include <fstream>
#include "json/json.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include "../util/SocketManager.h"
#include "../core/Player.h"
#include "../util/IOManager.h"
#include "../machine_learning/BPGraph.h"
#include <typeinfo>
// #include "../machine_learning/LSTMGraph.h"
using namespace std;

int main(int argc, char** argv)
{
    Config::config = Config::init("../config/parameter/constant.json");
    cout<<Config::config->B<<endl;
    cout<<Config::config->SQRTINV<<endl;
    cout<<Config::config->INV2<<endl;
    cout<<Config::config->LOCAL_TEST<<endl;
    DBGtest=0;
    if (argc < 2) {
        DBGprint("Please enter party index:\n");
        scanf("%d", &node_type);
    }
    else {
        node_type = argv[1][0] - '0';
    }
    DBGprint("party index: %d\n", node_type);

    Player::init();
    IOManager::init();
    SocketManager::SMMLF tel;
    if (!Config::config->LOCAL_TEST) {
        cout<<node_type<<endl;
        tel.init(Config::config->IP,Config::config->PORT);
    } else {
        tel.init();
    }
    BPGraph::LR *bp = new BPGraph::LR(&IOManager::train_data, &IOManager::train_label, &IOManager::test_data, &IOManager::test_label);

    if(Config::config->GRAPH_TYPE == Config::config->LOGISTIC){
        bp->logistic_graph();
    }
    else if(Config::config->GRAPH_TYPE == Config::config->LINEAR){
        bp->linear_graph();
    }
    bp->train();
    return 0;
}   
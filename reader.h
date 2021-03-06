//
// Created by Артем Аросланкин on 09.12.2019.
//

#ifndef BRIDGES_READER_H
#define BRIDGES_READER_H


#include "graph.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class weight_type = float>
class reader
{
public:
    vector<set<unsigned  int>> adj_list;
    unsigned int maxID = 0;
    CSRgraph graph;
    vector<unsigned int> source;
    vector<unsigned int> dest;
    vector<weight_type> weights;


    reader(const string& filename, bool is_weighted = false)
    {

        FILE *fp;
        char str[256];
        fp = fopen(filename.c_str(), "r");
        if (fp == NULL){
            exit(1);
        }


        if ( is_weighted == true) {
            while (fgets(str, 256, fp) != NULL) {
                string str2(str);
                istringstream str_stream(str2);
                string number;
                getline(str_stream, number, ' ');
                unsigned int src_ = stol(number);
                getline(str_stream, number, ' ');
                unsigned int dst_ = stol(number);
                getline(str_stream, number, ' ');
                weight_type weight = stod(number);
                source.push_back(src_);
                dest.push_back(dst_);
                weights.push_back(weight);
            }
        }
        else {
            int total = 0;
            while (fgets(str, 256, fp) != NULL) {
                string str2(str);
                istringstream str_stream(str2);
                string number;
                getline(str_stream, number, ' ');
                unsigned int src_ = stol(number);
                getline(str_stream, number, ' ');
                unsigned int dst_ = stol(number);
                source.push_back(src_);
                dest.push_back(dst_);
                total++;
            }
            maxID =0;
            for(unsigned int i = 0; i < source.size(); ++i) {
                if(source[i] > maxID) maxID = source[i];
                if(dest[i] > maxID) maxID = dest[i];
            }
            adj_list.clear();
            adj_list.resize(maxID + 1);

            for(unsigned int i = 0; i < source.size(); ++i) {
                adj_list[source[i]].insert(dest[i]);
                adj_list[dest[i]].insert(source[i]);
            }
        }
        fclose(fp);
    }


    CSRgraph get_graph() const
    {
        return graph;
    }

    vector<set<unsigned  int >> get_adj_list() const {
        return adj_list;
    }
};


#endif //BRIDGES_READER_H

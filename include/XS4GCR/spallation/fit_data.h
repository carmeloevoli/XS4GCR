// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_SPALLATION_FIT_DATA_H_
#define INCLUDE_XS4GCR_SPALLATION_FIT_DATA_H_

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "XS4GCR/mks.h"
#include "XS4GCR/pid.h"

namespace XS4GCR {

class FitData {
   public:
    FitData() {}

    explicit FitData(const std::string& fname) : filename(fname) { read_data(); }

    virtual ~FitData() {}

    struct data_struct {
        channel ch;
        double T;
        double sigma;
        double sigma_err;
    };

    void read_data() {
        int Z_proj;
        int A_proj;
        int Z_frag;
        int A_frag;
        double T;
        double s;
        double serr;
        std::string label;
        std::ifstream datafile(filename.c_str());
        datafile.ignore(512, '\n');
        while (datafile >> Z_proj >> A_proj >> Z_frag >> A_frag >> T >> s >> serr >> label) {
            auto ch = std::make_pair(PID(Z_proj, A_proj), PID(Z_frag, A_frag));
            data_struct data{ch, T * MKS::GeV, s * MKS::mbarn, serr * MKS::mbarn};
            Data.push_back(data);
        }
        datafile.close();
        std::cout << " - read " << Data.size() << " data points\n";
    }

    bool channel_exists(const channel& ch) {
        size_t counter = 0;
        for (auto& data : Data)
            if (data.ch == ch) counter++;
        return counter > 0;
    }

    std::vector<data_struct> get_data(const channel& ch) {
        std::vector<data_struct> v;
        for (auto data : Data)
            if (data.ch == ch) v.push_back(data);
        assert(v.size() > 0);
        return v;
    }

   protected:
    std::string filename;
    std::vector<data_struct> Data;
};

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_SPALLATION_FIT_DATA_H_

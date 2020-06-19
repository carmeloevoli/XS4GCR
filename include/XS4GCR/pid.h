// Copyright (c) 2017 Carmelo Evoli - MIT License
#ifndef INCLUDE_XS4GCR_PID_H_
#define INCLUDE_XS4GCR_PID_H_

#include <cassert>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include "XS4GCR/utilities.h"

namespace XS4GCR {

class PID {
   public:
    PID() { set(0, 0); }

    PID(const int &Z, const int &A) { set(Z, A); }

    PID(const std::string &Z_name, const int &A) {
        auto Z = str_to_Z(Z_name);
        set(Z, A);
    }

    virtual ~PID() {}

    void set(const int &Z, const int &A) {
        assert(A >= 0);
        assert(A >= Z);
        m_Z = Z;
        m_A = A;
        m_id = A * 1000 + Z;
        if (Z > 0)
            m_name = Z_to_str(Z);
        else
            m_name = "empty";
    }

    int get_A() const { return m_A; }

    int get_Z() const { return m_Z; }

    bool operator==(const PID &other) const { return m_id == other.m_id; }

    bool operator!=(const PID &other) const { return m_id != other.m_id; }

    bool operator<(const PID &other) const { return m_id < other.m_id; }

    bool with_Z(const int &Z) const { return m_Z == Z; }

    bool with_A(const int &A) const { return m_A == A; }

    bool is_lepton() const { return m_A == 0; }

    bool is_electron() const { return m_A == 0 && m_Z == -1; }

    bool is_positron() const { return m_A == 0 && m_Z == 1; }

    bool is_H() const { return (m_Z == 1); }

    bool is_He() const { return (m_Z == 2); }

    friend std::ostream &operator<<(std::ostream &stream, const PID &pid) {
        stream << "(" << pid.m_Z << "," << pid.m_A << ")";
        return stream;
    }

    std::string to_string() const {
        std::string ss;
        ss = "(" + std::to_string(m_Z) + "," + std::to_string(m_A) + ")";
        return ss;
    }

   protected:
    int m_Z;
    int m_A;
    int m_id;
    std::string m_name;
};

class TARGET : public PID {
   public:
    explicit TARGET(const int &Z) { set(Z); }

    void set(const int &Z) {
        assert(Z == 1 || Z == 2);
        m_Z = Z;
        m_A = (Z == 1) ? Z : 2 * Z;
        m_id = m_A * 1000 + m_Z;
    }
};

using channel = std::pair<PID, PID>;

}  // namespace XS4GCR

#endif  // INCLUDE_XS4GCR_PID_H_

#ifndef D2XSECS_PID_H
#define D2XSECS_PID_H

#include <cassert>
#include <map>
#include <strstream>

class PID {
public:
    PID() {
        set(0, 0);
    }

    PID(const int &Z_, const int &A_) {
        assert(A_ >= 0);
        set(Z_, A_);
    }

    virtual ~PID() {
    }

    void set(const int &Z_, const int &A_) {
        Z = Z_;
        A = A_;
        id = A * 1000 + Z;
    }

    int get_Z() const {
        return Z;
    }

    int get_A() const {
        return A;
    }

    int get_id() const {
        return id;
    }

    bool operator==(const PID &other) const {
        return id == other.id;
    }

    bool operator!=(const PID &other) const {
        return id != other.id;
    }

    bool operator<(const PID &other) const {
        return id < other.id;
    }

    bool with_Z(const int &Z_) const {
        return Z == Z_;
    }

    bool with_A(const int &A_) const {
        return A == A_;
    }

    bool is_lepton() const {
        return A == 0;
    }

    bool is_electron() const {
        return A == 0 && Z == -1;
    }

    bool is_positron() const {
        return A == 0 && Z == 1;
    }

    bool is_H() const {
        return (Z == 1);
    }

    bool is_He() const {
        return (Z == 2);
    }

    friend std::ostream &operator<<(std::ostream &stream, const PID &pid) {
        stream << "(" << pid.get_A() << "," << pid.get_Z() << ")";
        return stream;
    }

    std::string to_string() const {
        std::string ss;
        ss = "(" + std::to_string(Z) + "," + std::to_string(A) + ")";
        return ss;
    }

protected:
    int Z;
    int A;
    int id;
};

class TARGET : public PID {
public:
    TARGET(const int &Z_) {
        assert(Z_ == 1 || Z_ == 2);
        set(Z_);
    }

    void set(const int &Z_) {
        Z = Z_;
        A = (Z_ == 1) ? Z_ : 2 * Z_;
        id = A * 1000 + Z;
    }

    bool is_H() const {
        return Z == 1;
    }

    bool is_He() const {
        return Z == 2;
    }
};

typedef std::pair<PID, PID> channel;

static const PID He4 = PID(2, 4);
static const PID He3 = PID(2, 3);
static const PID Li6 = PID(3, 6);
static const PID Li7 = PID(3, 7);
static const PID Be7 = PID(4, 7);
static const PID Be9 = PID(4, 9);
static const PID Be10 = PID(4, 10);
static const PID B10 = PID(5, 10);
static const PID B11 = PID(5, 11);
static const PID C12 = PID(6, 12);
static const PID C13 = PID(6, 13);
static const PID C14 = PID(6, 14);
static const PID N14 = PID(7, 14);
static const PID N15 = PID(7, 15);
static const PID O16 = PID(8, 16);
static const PID O17 = PID(8, 17);
static const PID O18 = PID(8, 18);
static const PID F19 = PID(9, 19);
static const PID Ne20 = PID(10, 20);
static const PID Ne21 = PID(10, 21);
static const PID Ne22 = PID(10, 22);
static const PID Na23 = PID(11, 23);
static const PID Mg24 = PID(12, 24);
static const PID Mg25 = PID(12, 25);
static const PID Mg26 = PID(12, 26);
static const PID Al26 = PID(13, 26);
static const PID Al27 = PID(13, 27);
static const PID Si28 = PID(14, 28);
static const PID Si29 = PID(14, 29);
static const PID Si30 = PID(14, 30);
static const PID Si32 = PID(14, 32);
static const PID P31 = PID(15, 31);
static const PID S32 = PID(16, 32);
static const PID S33 = PID(16, 33);
static const PID S34 = PID(16, 34);
static const PID S36 = PID(16, 36);
static const PID Cl35 = PID(17, 35);
static const PID Cl37 = PID(17, 37);

#endif

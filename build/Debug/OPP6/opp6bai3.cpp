#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>      
#include <stdexcept>
#include <cmath>

using namespace std;
class MauSoBangKhong : public runtime_error {
public:
    MauSoBangKhong() : runtime_error("Mẫu số không được bằng 0") {}
};
class PhanSo {
private:
    int tu_, mau_;

    // Chuẩn hóa: đưa dấu lên tử
    void chuanHoa() {
        if (mau_ < 0) { tu_ = -tu_; mau_ = -mau_; }
    }
public:
    PhanSo(int tu = 0, int mau = 1) : tu_(tu) {
        setMau(mau);
    }
    int getTu()  const { return tu_; }
    int getMau() const { return mau_; }
    void setTu(int tu)   { tu_ = tu; }
    void setMau(int mau) {
        if (mau == 0) throw MauSoBangKhong();
        mau_ = mau;
        chuanHoa();
    }
    PhanSo toiGian() const {
        int g = gcd(abs(tu_), abs(mau_));
        return PhanSo(tu_ / g, mau_ / g);
    }

    bool isToiGian() const {
        return gcd(abs(tu_), abs(mau_)) == 1;
    }
    PhanSo operator+(const PhanSo& o) const {
        return PhanSo(tu_ * o.mau_ + o.tu_ * mau_,
                       mau_ * o.mau_).toiGian();
    }

    PhanSo operator-(const PhanSo& o) const {
        return PhanSo(tu_ * o.mau_ - o.tu_ * mau_,
                       mau_ * o.mau_).toiGian();
    }

    PhanSo operator*(const PhanSo& o) const {
        return PhanSo(tu_ * o.tu_, mau_ * o.mau_).toiGian();
    }

    PhanSo operator/(const PhanSo& o) const {
        if (o.tu_ == 0) throw runtime_error("Chia cho 0");
        return PhanSo(tu_ * o.mau_, mau_ * o.tu_).toiGian();
    }
    bool operator==(const PhanSo& o) const {
        PhanSo a = toiGian(), b = o.toiGian();
        return a.tu_ == b.tu_ && a.mau_ == b.mau_;
    }

    bool operator<(const PhanSo& o) const {
        return tu_ * o.mau_ < o.tu_ * mau_;    // Tích chéo
    }

    bool operator>(const PhanSo& o) const {
        return o < *this;
    }
    friend ostream& operator<<(ostream& os, const PhanSo& ps) {
        PhanSo tg = ps.toiGian();
        if (tg.mau_ == 1) return os << tg.tu_;
        return os << tg.tu_ << "/" << tg.mau_;
    }
};
int main() {
    vector<PhanSo> ds = {
        PhanSo(2, 4), PhanSo(3, 6),
        PhanSo(1, 3), PhanSo(5, 7)
    };
    cout << "── Dãy phân số & tối giản ──" << endl;
    for (const auto& ps : ds) {
        cout << "  " << ps.getTu() << "/" << ps.getMau()
             << " → tối giản: " << ps.toiGian()
             << "  (đã TG? " << (ps.isToiGian() ? "true" : "false")
             << ")" << endl;
    }
    PhanSo a(1, 3), b(5, 7);
    cout << "\n── Phép toán ──" << endl;
    cout << "  1/3 + 5/7 = " << (a + b) << endl;
    cout << "  1/3 - 5/7 = " << (a - b) << endl;
    cout << "  1/3 * 5/7 = " << (a * b) << endl;
    cout << "  1/3 / 5/7 = " << (a / b) << endl;
    sort(ds.begin(), ds.end());
    cout << "\n── Sắp xếp tăng dần ──" << endl;
    for (const auto& ps : ds)
        cout << "  " << ps.toiGian() << endl;
    cout << "\n── So sánh ──" << endl;
    cout << "  2/4 == 3/6 ? "
         << (PhanSo(2,4) == PhanSo(3,6) ? "true" : "false") << endl;
    cout << "  1/3 < 5/7  ? "
         << (a < b ? "true" : "false") << endl;
    cout << "\n── Validation ──" << endl;
    try {
        PhanSo loi(5, 0);
    } catch (const MauSoBangKhong& e) {
        cout << "  Bắt lỗi: " << e.what() << endl;
    }
    return 0;
}
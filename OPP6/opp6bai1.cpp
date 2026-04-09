#include <iostream>
#include <string>
#include <vector> 
#include <algorithm> 
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include <memory>

using namespace std;

class GiaKhongHopLe : public runtime_error {
    double gia;
public:
    GiaKhongHopLe(double gia) : runtime_error("Gía" + to_string(gia) + " không hợp lệ!"), gia(gia) {}
    double getGia() const { return gia; }
};

class HangHoa {
private:
    string maHang_, tenHang_, nhaSX_;
    double gia_;

public:
    HangHoa(const string& ma, const string& ten,
            const string& nsx, double gia)
        : maHang_(ma), tenHang_(ten), nhaSX_(nsx) {
        setGia(gia);                  // Validate
    }
virtual ~HangHoa() = default;
const string& getMaHang() const { return maHang_; }
const string& getTenHang() const { return tenHang_; }
const string& getNhaSX() const { return nhaSX_; }
double        getGia() const { return gia_; }
void setGia(double gia) {
    if (gia < 0) {
        throw GiaKhongHopLe(gia);
    }
    gia_ = gia;
}

virtual string loaiHang() const = 0; 
virtual string inTTin() const {
    return "[" + loaiHang() + "] " + maHang_ + " | " + tenHang_ + " | " + nhaSX_ + " |Gía: " + to_string((long long)gia_) + "đ";
}
bool operator==(const HangHoa& o) const {
        return maHang_ == o.maHang_;
    }
bool operator<(const HangHoa& o) const {
        return gia_ < o.gia_;
    }
    friend ostream& operator<<(ostream& os, const HangHoa& h) {
        return os << h.inTTin();
    }
};
class HangDienMay : public HangHoa {
    int baohanh_, dienAp_, congSuat_;
public:
    HangDienMay(const string& ma, const string& ten,
                const string& nsx, double gia,
                int bh, int dap, int cs)
        : HangHoa(ma, ten, nsx, gia),
          baohanh_(bh), dienAp_(dap), congSuat_(cs) {}

    string loaiHang() const override { return "Điện máy"; }

    string inTTin() const override {
        return HangHoa::inTTin()
             + " | BH: " + to_string(baohanh_) + "th"
             + " | " + to_string(dienAp_) + "V"
             + " | " + to_string(congSuat_) + "W";
    }
};
class HangSanhSu : public HangHoa {
    string nguyenLieu_;
public:
    HangSanhSu(const string& ma, const string& ten,
               const string& nsx, double gia,
               const string& nl)
        : HangHoa(ma, ten, nsx, gia), nguyenLieu_(nl) {}

    string loaiHang() const override { return "Sành sứ"; }

    string inTTin() const override {
        return HangHoa::inTTin() + " | NL: " + nguyenLieu_;
    }
};
class HangThucPham : public HangHoa {
    string ngaySX_, ngayHH_;
public:
    HangThucPham(const string& ma, const string& ten,
                 const string& nsx, double gia,
                 const string& sx, const string& hh)
        : HangHoa(ma, ten, nsx, gia), ngaySX_(sx), ngayHH_(hh) {}

    string loaiHang() const override { return "Thực phẩm"; }

    string inTTin() const override {
        return HangHoa::inTTin()
             + " | SX: " + ngaySX_ + " | HSD: " + ngayHH_;
    }
};
int main() {
    vector<unique_ptr<HangHoa>> kho;
    kho.push_back(make_unique<HangDienMay>(
        "DM01", "Tủ lạnh", "LG", 12000000, 24, 220, 150));
    kho.push_back(make_unique<HangSanhSu>(
        "SS01", "Bình hoa", "Minh Long", 350000, "Sứ cao cấp"));
    kho.push_back(make_unique<HangThucPham>(
        "TP01", "Sữa tươi", "Vinamilk", 32000,
        "2025-01-01", "2025-07-01"));
    cout << "── Đa hình: cout << *sp ──" << endl;
    for (const auto& sp : kho)
        cout << *sp << endl;     
    sort(kho.begin(), kho.end(),
         [](const auto& a, const auto& b) { return *a < *b; });
    cout << "\n── Sắp xếp theo giá ──" << endl;
    for (const auto& sp : kho)
        cout << "  " << sp->getGia() << "đ | " << sp->getTenHang() << endl;
    cout << "\n── Validation ──" << endl;
    try {
        HangDienMay loi("X", "Test", "Y", -5000, 12, 220, 50);
    } catch (const GiaKhongHopLe& e) {
        cout << "  Bắt lỗi: " << e.what() << endl;
    }
    cout << "\n── Lưu file ──" << endl;
    {   
        ofstream f("kho_hang.txt");
        for (const auto& sp : kho)
            f << *sp << "\n";
        cout << "  Đã lưu " << kho.size() << " sản phẩm" << endl;
    }   

    return 0;
}
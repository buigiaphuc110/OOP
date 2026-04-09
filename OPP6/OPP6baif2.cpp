#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <fstream>

using namespace std;

class TuoiKhongHopLe : public runtime_error {
public:
    TuoiKhongHopLe(int t)
        : runtime_error("Tuổi " + to_string(t) + " không hợp lệ (18-65)") {}
};

class BacKhongHopLe : public runtime_error {
public:
    BacKhongHopLe(int b)
        : runtime_error("Bậc " + to_string(b) + " không hợp lệ (1-10)") {}
};

class CanBo {
private:
    string hoTen_, gioiTinh_, diaChi_;
    int tuoi_;
public:
    CanBo(const string& ht, int tuoi,
          const string& gt, const string& dc)
        : hoTen_(ht), gioiTinh_(gt), diaChi_(dc) {
        setTuoi(tuoi);
    }
    
    virtual ~CanBo() = default;
    
    const string& getHoTen() const { return hoTen_; }
    int getTuoi() const { return tuoi_; }

    void setTuoi(int t) {
        if (t < 18 || t > 65) throw TuoiKhongHopLe(t);
        tuoi_ = t;
    }
    
    virtual string moTa() const = 0;
    bool operator<(const CanBo& o) const {
        return hoTen_ < o.hoTen_;
    }
    friend ostream& operator<<(ostream& os, const CanBo& cb) {
        return os << cb.hoTen_ << " | " << cb.tuoi_ << " tuổi | "
                  << cb.gioiTinh_ << " | " << cb.diaChi_
                  << " | " << cb.moTa();   // Gọi virtual → đa hình!
    }
};
class CongNhan : public CanBo {
    int bac_;
public:
    CongNhan(const string& ht, int tuoi,
             const string& gt, const string& dc, int bac)
        : CanBo(ht, tuoi, gt, dc) {
        if (bac < 1 || bac > 10) throw BacKhongHopLe(bac);
        bac_ = bac;
    }
    string moTa() const override {
        return "Công nhân bậc " + to_string(bac_);
    }
};
class KySu : public CanBo {
    string nganh_;
public:
    KySu(const string& ht, int tuoi,
         const string& gt, const string& dc,
         const string& ng)
        : CanBo(ht, tuoi, gt, dc), nganh_(ng) {}
    string moTa() const override {
        return "Kỹ sư ngành " + nganh_;
    }
};
class NhanVien : public CanBo {
    string congViec_;
public:
    NhanVien(const string& ht, int tuoi,
             const string& gt, const string& dc,
             const string& cv)
        : CanBo(ht, tuoi, gt, dc), congViec_(cv) {}
    string moTa() const override {
        return "Nhân viên — " + congViec_;
    }
};
int main() {
    vector<unique_ptr<CanBo>> ds; 
    cout << "── Validation ──" << endl;
    try { CongNhan x("X", 15, "Nam", "HN", 5); }
    catch (const TuoiKhongHopLe& e) { cout << "  " << e.what() << endl; }
    
    try { CongNhan y("Y", 25, "Nữ", "HN", 15); }
    catch (const BacKhongHopLe& e) { cout << "  " << e.what() << endl; }
    { 
        ofstream f("canbo.txt");
        ds.push_back(make_unique<CongNhan>("Nguyễn Văn A", 30, "Nam", "HN", 5));
        ds.push_back(make_unique<KySu>("Trần Thị B", 28, "Nữ", "HCM", "CNTT"));
        ds.push_back(make_unique<NhanVien>("Lê Văn C", 35, "Nam", "DN", "Kế toán"));

        cout << "\n── Đa hình ──" << endl;
        for (const auto& cb : ds) cout << *cb << endl;

        sort(ds.begin(), ds.end(),
             [](const auto& a, const auto& b) { return *a < *b; });
             
        cout << "\n── Sắp xếp theo tên ──" << endl;
        for (const auto& cb : ds) cout << "  " << cb->getHoTen() << endl;
        for (const auto& cb : ds) f << *cb << "\n";
        
        cout << "\n── Đã lưu " << ds.size() << " cán bộ vào file ──" << endl;
    }
    
    return 0;
}
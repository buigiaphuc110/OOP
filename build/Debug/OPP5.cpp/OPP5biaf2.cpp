#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const double LUONG_CO_BAN = 5000000;

class NhanVien {
protected:
    string maNV, hoTen, gioiTinh, diaChi;
    int    namSinh;
    double heSoLuong, luongToiDa;

public:
    NhanVien(string ma, string ht, int ns, string gt,
             string dc, double hs, double ltd)
        : maNV(ma), hoTen(ht), namSinh(ns), gioiTinh(gt),
          diaChi(dc), heSoLuong(hs > 0 ? hs : 1.0), luongToiDa(ltd) {}
    string getHoTen() const {
        return hoTen;
    }
    virtual double tinhLuong() const {
        return LUONG_CO_BAN * heSoLuong;
    }
    virtual void hienThi() const {
        cout << "  Mã NV     : " << maNV     << endl;
        cout << "  Họ tên    : " << hoTen    << endl;
        cout << "  Năm sinh  : " << namSinh  << endl;
        cout << "  Giới tính : " << gioiTinh << endl;
        cout << "  Địa chỉ   : " << diaChi   << endl;
        cout << "  Hệ số     : " << heSoLuong << endl;
        cout << fixed << setprecision(0);
        cout << "  Lương      : " << tinhLuong() << " VNĐ" << endl;
    }
    virtual ~NhanVien() = default;
};
class CongTacVien : public NhanVien {
private:
    string thoiHanHD; 
    double phuCapLD;
public:
    CongTacVien(string ma, string ht, int ns, string gt,
                string dc, double hs, double ltd,
                string hd, double pc)
        : NhanVien(ma, ht, ns, gt, dc, hs, ltd),
          thoiHanHD(hd), phuCapLD(pc) {}
          
    double tinhLuong() const override {
        return NhanVien::tinhLuong() + phuCapLD;
    }
    void hienThi() const override {
        cout << "═══ CỘNG TÁC VIÊN ═══" << endl;
        NhanVien::hienThi();   // C++ dùng TenLop::method() thay vì super
        cout << "  Thời hạn HĐ: " << thoiHanHD << endl;
        cout << fixed << setprecision(0);
        cout << "  Phụ cấp LĐ : " << phuCapLD << " VNĐ" << endl;
    }
};
class NVChinhThuc : public NhanVien {
private:
    string viTri;

public:
    NVChinhThuc(string ma, string ht, int ns, string gt,
                string dc, double hs, double ltd, string vt)
        : NhanVien(ma, ht, ns, gt, dc, hs, ltd), viTri(vt) {}

    // Không override tinhLuong() → dùng của lớp cha
    // Đây là ưu điểm kế thừa: code reuse!

    void hienThi() const override {
        cout << "═══ NHÂN VIÊN CHÍNH THỨC ═══" << endl;
        NhanVien::hienThi();
        cout << "  Vị trí    : " << viTri << endl;
    }
};

class TruongPhong : public NhanVien {
private:
    string ngayBatDauQL;
    double phuCapQL;

public:
    TruongPhong(string ma, string ht, int ns, string gt,
                string dc, double hs, double ltd,
                string ngay, double pc)
        : NhanVien(ma, ht, ns, gt, dc, hs, ltd),
          ngayBatDauQL(ngay), phuCapQL(pc) {}

    double tinhLuong() const override {
        return NhanVien::tinhLuong() + phuCapQL;
    }
    void hienThi() const override {
        cout << "═══ TRƯỞNG PHÒNG ═══" << endl;
        NhanVien::hienThi();
        cout << "  Ngày BĐ QL: " << ngayBatDauQL << endl;
        cout << fixed << setprecision(0);
        cout << "  Phụ cấp QL: " << phuCapQL << " VNĐ" << endl;
    }
};

int main() {
    CongTacVien ctv("CTV01", "Trần Thị B", 2000, "Nữ",
                     "Hà Nội", 1.5, 30000000,
                     "6 tháng", 1500000);

    NVChinhThuc nvct("NV01", "Lê Văn C", 1995, "Nam",
                      "Đà Nẵng", 2.0, 40000000,
                      "Kỹ sư phần mềm");

    TruongPhong tp("TP01", "Nguyễn Văn D", 1985, "Nam",
                    "TP.HCM", 3.0, 50000000,
                    "01/01/2020", 5000000);

    ctv.hienThi();  cout << endl;
    nvct.hienThi(); cout << endl;
    tp.hienThi();
    
    cout << "\n══ BẢNG LƯƠNG (Polymorphism) ══" << endl;
    NhanVien* dsNV[] = { &ctv, &nvct, &tp };
    
    for (auto nv : dsNV) {
        // Đã sửa nv->hoTen thành nv->getHoTen()
        cout << "  " << left << setw(20) << nv->getHoTen()
             << " → " << right << setw(12) << fixed << setprecision(0)
             << nv->tinhLuong() << " VNĐ" << endl;
    }
    
    return 0;
}
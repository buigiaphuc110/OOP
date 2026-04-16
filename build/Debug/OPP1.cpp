#include <iostream>
#include <string>

using namespace std;

class NhanVien {
private:
    string tenNhanVien;
    double luongCoBan;
    double heSoLuong;

public:
    // Thuộc tính tĩnh LUONG_MAX (được gạch chân trong sơ đồ)
    // Giả sử mức lương tối đa là 50 triệu để chạy thử
    static constexpr double LUONG_MAX = 50000000.0; 

    // Constructor mặc định và có tham số (bổ sung để dễ khởi tạo)
    NhanVien() : tenNhanVien(""), luongCoBan(0.0), heSoLuong(0.0) {}
    
    NhanVien(string ten, double luongCB, double heSo) 
        : tenNhanVien(ten), luongCoBan(luongCB), heSoLuong(heSo) {}

    // Yêu cầu 4: Đầy đủ Getter/Setter cho tất cả các thuộc tính
    string getTenNhanVien() const { return tenNhanVien; }
    void setTenNhanVien(const string& ten) { tenNhanVien = ten; }

    double getLuongCoBan() const { return luongCoBan; }
    void setLuongCoBan(double luongCB) { luongCoBan = luongCB; }

    double getHeSoLuong() const { return heSoLuong; }
    void setHeSoLuong(double heSo) { heSoLuong = heSo; }

    // Yêu cầu 1: Phương thức tính lương
    double tinhLuong() const {
        return luongCoBan * heSoLuong;
    }

    // Yêu cầu 2: Phương thức in thông tin
    void inTTin() const {
        cout << "--- THONG TIN NHAN VIEN ---" << endl;
        cout << "Ten nhan vien : " << tenNhanVien << endl;
        cout << "Luong co ban  : " << luongCoBan << endl;
        cout << "He so luong   : " << heSoLuong << endl;
        cout << "Luong thuc te : " << tinhLuong() << endl;
        cout << "---------------------------" << endl;
    }

    // Yêu cầu 3: Phương thức tăng lương
    // Giả sử delta là số lượng tăng thêm của Hệ số lương
    bool tangLuong(double delta) {
        double heSoLuongMoi = heSoLuong + delta;
        double luongMoi = luongCoBan * heSoLuongMoi;

        if (luongMoi > LUONG_MAX) {
            cout << "[!] Khong the tang luong. Luong moi (" << luongMoi 
                 << ") vuot qua LUONG_MAX (" << LUONG_MAX << ")." << endl;
            return false;
        } else {
            // Cập nhật hệ số lương nếu hợp lệ
            heSoLuong = heSoLuongMoi; 
            cout << "[V] Tang luong thanh cong! He so luong moi la: " << heSoLuong << endl;
            return true;
        }
    }
};

// Hàm main để chạy thử nghiệm nghiệm lớp NhanVien
int main() {
    // Khởi tạo nhân viên
    NhanVien nv1("Nguyen Van A", 10000000.0, 2.5);
    nv1.inTTin();

    // Thử tăng hệ số lương thêm 1.0 (Lương mới: 10tr * 3.5 = 35tr < 50tr) -> Hợp lệ
    nv1.tangLuong(1.0);
    nv1.inTTin();

    // Thử tăng hệ số lương thêm 2.0 (Lương mới: 10tr * 5.5 = 55tr > 50tr) -> Không hợp lệ
    nv1.tangLuong(2.0);
    nv1.inTTin();

    return 0;
}


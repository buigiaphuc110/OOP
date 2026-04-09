#include <iostream>
#include <string>
#include <vector>
#include <memory>        // unique_ptr, make_unique
#include <algorithm>     // find_if
using namespace std;

// ══════════════════════════════════════════════════════════════
//  Bài 3: Quản lý cán bộ — vector<unique_ptr> + menu
// ══════════════════════════════════════════════════════════════


// ─── Lớp cha CanBo ───────────────────────────────────────────
class CanBo {
protected:
    string hoTen, gioiTinh, diaChi;
    int    tuoi;

public:
    // Đã sửa lại thứ tự khởi tạo: hoTen -> gioiTinh -> diaChi -> tuoi 
    // cho khớp với thứ tự khai báo ở trên để hết lỗi cảnh báo
    CanBo(string ht, int t, string gt, string dc)
        : hoTen(ht), gioiTinh(gt), diaChi(dc), tuoi(t) {}

    virtual string loaiCB() const { return "Cán bộ"; }

    virtual void hienThi() const {
        cout << "  Họ tên    : " << hoTen    << endl;
        cout << "  Tuổi      : " << tuoi      << endl;
        cout << "  Giới tính : " << gioiTinh << endl;
        cout << "  Địa chỉ   : " << diaChi   << endl;
    }

    string getHoTen() const { return hoTen; }

    virtual ~CanBo() = default;
};


// ─── CongNhan ────────────────────────────────────────────────
class CongNhan : public CanBo {
private:
    int bac;  // 1-10

public:
    CongNhan(string ht, int t, string gt, string dc, int b)
        : CanBo(ht, t, gt, dc), bac(b) {
        if (b < 1 || b > 10)
            throw invalid_argument("Bậc phải từ 1 đến 10!");
    }

    string loaiCB() const override { return "Công nhân"; }

    void hienThi() const override {
        cout << "── CÔNG NHÂN ──" << endl;
        CanBo::hienThi();
        cout << "  Bậc       : " << bac << endl;
    }
};


// ─── KySu ────────────────────────────────────────────────────
class KySu : public CanBo {
private:
    string nganhDT;

public:
    KySu(string ht, int t, string gt, string dc, string ndt)
        : CanBo(ht, t, gt, dc), nganhDT(ndt) {}

    string loaiCB() const override { return "Kỹ sư"; }

    void hienThi() const override {
        cout << "── KỸ SƯ ──" << endl;
        CanBo::hienThi();
        cout << "  Ngành ĐT  : " << nganhDT << endl;
    }
};


// ─── NhanVienSX ──────────────────────────────────────────────
class NhanVienSX : public CanBo {
private:
    string congViec;

public:
    NhanVienSX(string ht, int t, string gt, string dc, string cv)
        : CanBo(ht, t, gt, dc), congViec(cv) {}

    string loaiCB() const override { return "Nhân viên"; }

    void hienThi() const override {
        cout << "── NHÂN VIÊN ──" << endl;
        CanBo::hienThi();
        cout << "  Công việc : " << congViec << endl;
    }
};


// ═════════════════════════════════════════════════════════════
//  Lớp QLCB — Quản lý cán bộ
// ═════════════════════════════════════════════════════════════
class QLCB {
private:
    // vector chứa unique_ptr → tự giải phóng bộ nhớ
    vector<unique_ptr<CanBo>> dsCanBo;

public:
    void themMoi() {
        string hoTen, gioiTinh, diaChi, extra;
        int    tuoi, loai;

        cout << "\n── THÊM CÁN BỘ MỚI ──" << endl;
        cout << "  1. Công nhân  2. Kỹ sư  3. Nhân viên" << endl;
        cout << "  Chọn loại: "; cin >> loai;
        cin.ignore();   // Xóa \n thừa trong buffer

        cout << "  Họ tên    : "; getline(cin, hoTen);
        cout << "  Tuổi      : "; cin >> tuoi; cin.ignore();
        cout << "  Giới tính : "; getline(cin, gioiTinh);
        cout << "  Địa chỉ   : "; getline(cin, diaChi);

        if (loai == 1) {
            int bac;
            cout << "  Bậc (1-10): "; cin >> bac; cin.ignore();
            dsCanBo.push_back(
                make_unique<CongNhan>(hoTen, tuoi, gioiTinh, diaChi, bac)
            );
        }
        else if (loai == 2) {
            cout << "  Ngành ĐT  : "; getline(cin, extra);
            dsCanBo.push_back(
                make_unique<KySu>(hoTen, tuoi, gioiTinh, diaChi, extra)
            );
        }
        else if (loai == 3) {
            cout << "  Công việc : "; getline(cin, extra);
            dsCanBo.push_back(
                make_unique<NhanVienSX>(hoTen, tuoi, gioiTinh, diaChi, extra)
            );
        }
        else {
            cout << "  ⚠ Loại không hợp lệ!" << endl;
            return;
        }

        cout << "  ✓ Đã thêm: " << dsCanBo.back()->loaiCB()
             << " | " << dsCanBo.back()->getHoTen() << endl;
    }

    void timKiem() {
        string tuKhoa;
        cout << "\n  Nhập họ tên cần tìm: ";
        getline(cin, tuKhoa);

        bool found = false;
        for (const auto& cb : dsCanBo) {
            // string::find trả về npos nếu không tìm thấy
            if (cb->getHoTen().find(tuKhoa) != string::npos) {
                cout << endl;
                cb->hienThi();   // Polymorphism: gọi đúng phiên bản
                found = true;
            }
        }
        if (!found)
            cout << "  Không tìm thấy!" << endl;
    }

    void hienThiDS() {
        if (dsCanBo.empty()) {
            cout << "\n  Danh sách trống!" << endl;
            return;
        }
        cout << "\n══ DANH SÁCH CÁN BỘ (" << dsCanBo.size()
             << " người) ══" << endl;
        for (size_t i = 0; i < dsCanBo.size(); i++) {
            cout << "\n--- #" << (i + 1) << " ---" << endl;
            dsCanBo[i]->hienThi();
        }
    }

    void chay() {
        int chon;
        do {
            cout << "\n╔══════════════════════════╗" << endl;
            cout << "║   QUẢN LÝ CÁN BỘ       ║" << endl;
            cout << "╠══════════════════════════╣" << endl;
            cout << "║  1. Thêm mới cán bộ     ║" << endl;
            cout << "║  2. Tìm kiếm theo tên   ║" << endl;
            cout << "║  3. Hiển thị danh sách   ║" << endl;
            cout << "║  4. Thoát                ║" << endl;
            cout << "╚══════════════════════════╝" << endl;
            cout << "  Lựa chọn: "; cin >> chon; cin.ignore();

            switch (chon) {
                case 1: themMoi();   break;
                case 2: timKiem();   break;
                case 3: hienThiDS(); break;
                case 4: cout << "  Tạm biệt! 👋" << endl; break;
                default: cout << "  ⚠ Không hợp lệ!" << endl;
            }
        } while (chon != 4);
    }
};


// ─── Main ────────────────────────────────────────────────────
int main() {
    QLCB ql;
    ql.chay();
    return 0;
}
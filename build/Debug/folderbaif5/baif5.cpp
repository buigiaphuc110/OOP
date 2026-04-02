#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =================================================================
// YÊU CẦU 1: Xây dựng các lớp CongNhan, KySu, NhanVien kế thừa CanBo
// =================================================================

// 1. Lớp cha: Cán Bộ
class CanBo {
protected:
    string hoTen;
    int tuoi;
    string gioiTinh;
    string diaChi;

public:
    CanBo(string ht, int t, string gt, string dc) 
        : hoTen(ht), tuoi(t), gioiTinh(gt), diaChi(dc) {}

    // Phương thức ảo để thể hiện tính đa hình
    virtual void hienThi() {
        cout << "Ho ten: " << hoTen << " | Tuoi: " << tuoi 
             << " | Gioi tinh: " << gioiTinh << " | Dia chi: " << diaChi;
    }

    string getHoTen() {
        return hoTen;
    }

    virtual ~CanBo() {} // Destructor ảo
};

// 2. Lớp con: Công Nhân
class CongNhan : public CanBo {
private:
    int bac; // Từ 1 đến 10

public:
    CongNhan(string ht, int t, string gt, string dc, int b) 
        : CanBo(ht, t, gt, dc), bac(b) {}

    void hienThi() override {
        cout << "[Cong Nhan] ";
        CanBo::hienThi();
        cout << " | Bac: " << bac << endl;
    }
};

// 3. Lớp con: Kỹ Sư
class KySu : public CanBo {
private:
    string nganhDaoTao;

public:
    KySu(string ht, int t, string gt, string dc, string nganh) 
        : CanBo(ht, t, gt, dc), nganhDaoTao(nganh) {}

    void hienThi() override {
        cout << "[Ky Su]     ";
        CanBo::hienThi();
        cout << " | Nganh dao tao: " << nganhDaoTao << endl;
    }
};

// 4. Lớp con: Nhân Viên
class NhanVien : public CanBo {
private:
    string congViec;

public:
    NhanVien(string ht, int t, string gt, string dc, string cv) 
        : CanBo(ht, t, gt, dc), congViec(cv) {}

    void hienThi() override {
        cout << "[Nhan Vien] ";
        CanBo::hienThi();
        cout << " | Cong viec: " << congViec << endl;
    }
};


// =================================================================
// YÊU CẦU 2: Xây dựng lớp QLCB quản lý danh sách và các chức năng
// =================================================================

class QLCB {
private:
    // Dùng vector chứa con trỏ CanBo để lưu được cả 3 lớp con
    vector<CanBo*> danhSachCB;

public:
    // Chức năng 1: Thêm mới cán bộ
    void themMoi() {
        int loai;
        cout << "\n--- THEM MOI CAN BO ---" << endl;
        cout << "1. Cong Nhan | 2. Ky Su | 3. Nhan Vien" << endl;
        cout << "Chon loai can bo (1/2/3): ";
        cin >> loai;
        cin.ignore(); // Xóa bộ đệm sau khi nhập số

        string ht, gt, dc;
        int t;

        cout << "Nhap ho ten: "; getline(cin, ht);
        cout << "Nhap tuoi: "; cin >> t; cin.ignore();
        cout << "Nhap gioi tinh (Nam/Nu/Khac): "; getline(cin, gt);
        cout << "Nhap dia chi: "; getline(cin, dc);

        if (loai == 1) {
            int b;
            cout << "Nhap bac (1-10): "; cin >> b;
            danhSachCB.push_back(new CongNhan(ht, t, gt, dc, b));
        } 
        else if (loai == 2) {
            string nganh;
            cout << "Nhap nganh dao tao: "; getline(cin, nganh);
            danhSachCB.push_back(new KySu(ht, t, gt, dc, nganh));
        } 
        else if (loai == 3) {
            string cv;
            cout << "Nhap cong viec: "; getline(cin, cv);
            danhSachCB.push_back(new NhanVien(ht, t, gt, dc, cv));
        } else {
            cout << "Loai can bo khong hop le!" << endl;
        }
        cout << "-> Da them thanh cong!" << endl;
    }

    // Chức năng 2: Tìm kiếm theo họ tên
    void timKiem() {
        if (danhSachCB.empty()) {
            cout << "\nDanh sach trong!" << endl;
            return;
        }

        string tenTimKiem;
        cout << "\nNhap ho ten can tim: ";
        getline(cin, tenTimKiem);

        bool thay = false;
        cout << "\n--- KET QUA TIM KIEM ---" << endl;
        for (CanBo* cb : danhSachCB) {
            // Hàm find giúp tìm chuỗi con (không cần gõ chính xác 100% cả tên)
            if (cb->getHoTen().find(tenTimKiem) != string::npos) {
                cb->hienThi();
                thay = true;
            }
        }

        if (!thay) {
            cout << "Khong tim thay can bo nao ten la: " << tenTimKiem << endl;
        }
    }

    // Chức năng 3: Hiển thị thông tin danh sách
    void hienThiDanhSach() {
        if (danhSachCB.empty()) {
            cout << "\nDanh sach hien tai dang trong!" << endl;
            return;
        }

        cout << "\n=== DANH SACH CAN BO (" << danhSachCB.size() << ") ===" << endl;
        for (CanBo* cb : danhSachCB) {
            cb->hienThi();
        }
    }

    // Hàm dọn dẹp bộ nhớ khi tắt chương trình
    ~QLCB() {
        for (CanBo* cb : danhSachCB) {
            delete cb;
        }
        danhSachCB.clear();
    }
};

// =================================================================
// HÀM MAIN: Chạy chương trình và hiển thị Menu
// =================================================================
int main() {
    QLCB quanLy;
    int luaChon;

    do {
        cout << "\n========== QUAN LY CAN BO ==========" << endl;
        cout << "1. Them moi can bo" << endl;
        cout << "2. Tim kiem theo ho ten" << endl;
        cout << "3. Hien thi danh sach can bo" << endl;
        cout << "4. Thoat chuong trinh" << endl;
        cout << "====================================" << endl;
        cout << "Moi ban chon (1-4): ";
        cin >> luaChon;
        cin.ignore(); // Xóa bộ đệm tránh trôi lệnh nhập chuỗi

        switch (luaChon) {
            case 1:
                quanLy.themMoi();
                break;
            case 2:
                quanLy.timKiem();
                break;
            case 3:
                quanLy.hienThiDanhSach();
                break;
            case 4:
                cout << "Da thoat chuong trinh. Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
        }
    } while (luaChon != 4);

    return 0;
}
class NhanVien:
    def __init__(self, ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da):
        self.ma_nv = ma_nv
        self.ho_ten = ho_ten
        self.nam_sinh = nam_sinh
        self.gioi_tinh = gioi_tinh
        self.dia_chi = dia_chi
        
        # Kiểm tra hệ số lương > 0
        if he_so_luong <= 0:
            raise ValueError("Hệ số lương phải lớn hơn 0")
        self.he_so_luong = he_so_luong
        self.luong_toi_da = luong_toi_da

    def tinh_luong_co_ban(self, muc_luong_co_so=2000000):
        """Tính lương dựa trên hệ số, đảm bảo không vượt quá lương tối đa"""
        luong_tinh = self.he_so_luong * muc_luong_co_so
        return min(luong_tinh, self.luong_toi_da)

    def tinh_thu_nhap(self):
        """Phương thức này sẽ được ghi đè (override) ở các lớp con"""
        return self.tinh_luong_co_ban()

    def hienThiThongTin(self):
        print(f"Mã NV: {self.ma_nv} | Họ tên: {self.ho_ten} | Thu nhập: {self.tinh_thu_nhap():,.0f} VND")


class CongTacVien(NhanVien):
    def __init__(self, ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da, thoi_han_hd, phu_cap_ld):
        super().__init__(ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da)
        
        # Kiểm tra giá trị thời hạn hợp đồng hợp lệ
        if thoi_han_hd not in ["3 tháng", "6 tháng", "1 năm"]:
            raise ValueError("Thời hạn hợp đồng chỉ nhận: '3 tháng', '6 tháng', '1 năm'")
        
        self.thoi_han_hd = thoi_han_hd
        self.phu_cap_ld = phu_cap_ld

    def tinh_thu_nhap(self):
        # Thu nhập = Lương cơ bản + Phụ cấp lao động
        return self.tinh_luong_co_ban() + self.phu_cap_ld

    def hienThiThongTin(self):
        super().hienThiThongTin()
        print(f"   -> Loại: Cộng tác viên | Hợp đồng: {self.thoi_han_hd} | Phụ cấp: {self.phu_cap_ld:,.0f} VND")


class NhanVienChinhThuc(NhanVien):
    def __init__(self, ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da, vi_tri_cv):
        super().__init__(ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da)
        self.vi_tri_cv = vi_tri_cv

    def tinh_thu_nhap(self):
        # Lương tính như thông thường
        return self.tinh_luong_co_ban()

    def hienThiThongTin(self):
        super().hienThiThongTin()
        print(f"   -> Loại: NV Chính thức | Vị trí: {self.vi_tri_cv}")


class TruongPhong(NhanVien):
    def __init__(self, ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da, ngay_bat_dau, phu_cap_ql):
        super().__init__(ma_nv, ho_ten, nam_sinh, gioi_tinh, dia_chi, he_so_luong, luong_toi_da)
        self.ngay_bat_dau = ngay_bat_dau
        self.phu_cap_ql = phu_cap_ql

    def tinh_thu_nhap(self):
        # Thu nhập = Lương cơ bản + Phụ cấp quản lý
        return self.tinh_luong_co_ban() + self.phu_cap_ql

    def hienThiThongTin(self):
        super().hienThiThongTin()
        print(f"   -> Loại: Trưởng phòng | Ngày QL: {self.ngay_bat_dau} | Phụ cấp: {self.phu_cap_ql:,.0f} VND")

# ==========================================
# TEST THỬ CHƯƠNG TRÌNH
# ==========================================
if __name__ == "__main__":
    try:
        ctv = CongTacVien("NV01", "Nguyễn Văn A", 2000, "Nam", "Hà Nội", 1.5, 5000000, "6 tháng", 500000)
        nvc = NhanVienChinhThuc("NV02", "Trần Thị B", 1995, "Nữ", "HCM", 2.5, 10000000, "Chuyên viên IT")
        tp = TruongPhong("NV03", "Lê Văn C", 1988, "Nam", "Đà Nẵng", 4.0, 15000000, "01/01/2023", 2000000)

        ctv.hienThiThongTin()
        print("-" * 30)
        nvc.hienThiThongTin()
        print("-" * 30)
        tp.hienThiThongTin()

    except ValueError as e:
        print("Lỗi dữ liệu đầu vào:", e)
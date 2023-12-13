# DoAnQuanLyVatTu
-	Đồ án môn cấu trúc dữ liệu & giải thuật.
-	Các cấu trúc dữ liệu của chương trình:
o	Danh sách VatTu : cây nhị phân tìm kiếm (MAVT, TENVT, Đơn vị tính, Số lượng tồn)
o	Danh sách NhanVien : danh sách tuyến tính là một mảng con trỏ (MANV, HO, TEN, PHAI, con trỏ dshd): con trỏ dshd sẽ trỏ đến danh sách các hóa đơn mà nhân viên đó đã lập. Danh sách nhân viên có tối đa 500 nhân viên
o	Danh sách HoaDon : danh sách liên kết đơn(SoHD, Ngày lập hóa đơn, Loai, con trỏ cthd). Lọai chỉ nhận ‘N’ (phiếu nhập) hoặc ‘X’ (phiếu xuất); con trỏ cthd sẻ trỏ đến danh sách chi tiết các vật tư của hóa đơn đó.
o	Danh sách CT_HoaDon : danh sách liên kết đơn ( MAVT, Soluong, Dongia, %VAT).
-	Các chức năng của chương trình:
o	Cập nhật thông tin vật tư (thêm, xóa, sửa thông tin dựa vào mã).
o	Xuất danh sách vật tư.
o	Nhập thông tin nhân viên
o	Nhập hóa đơn và chi tiết hóa đơn: nhập vào số hóa đơn, ngày lập, loại (chỉ nhận ký tự I hoặc O). Sau đó, tiếp tục cho phép nhập các vật tư của hóa đơn đó; Căn cứ vào loại hóa đơn, chương trình sẽ tự động cập nhật số lượng tồn. Nếu số lượng xuất không đủ hàng thì báo lỗi.
o	In danh sách nhân viên theo thứ tự tên nhân viên tăng dần, nếu trùng tên thì tăng dần theo họ ra màn hình, 1 nhân viên / dòng.
o	Xuất thông tin hóa đơn và chi tiết hóa đơn.

# DoAnQuanLyVatTu
-	Đồ án môn cấu trúc dữ liệu & giải thuật.
-	Các cấu trúc dữ liệu của chương trình:
  
    a.Danh sách VatTu : cây nhị phân tìm kiếm (MAVT, TENVT, Đơn vị tính, Số lượng tồn).

    b.	Danh sách NhanVien : danh sách tuyến tính là một mảng con trỏ (nameEmployee, employeeID, gender, con trỏ billList): con trỏ billList sẽ trỏ đến danh sách các hóa đơn mà nhân viên đó đã lập. Danh sách nhân viên có tối đa 500 nhân viên.
 	
    c.	Danh sách HoaDon : danh sách liên kết đơn(billID, createdDate, billType, con trỏ listBillDetail). Lọai chỉ nhận ‘I’ (phiếu nhập/input) hoặc ‘O’ (phiếu xuất/output); con trỏ listBillDetail sẻ trỏ đến danh sách chi tiết các vật tư của hóa đơn đó.
 	
    d.	Danh sách CT_HoaDon : danh sách liên kết đơn ( materialID, numberMaterial,unit, VAT).
 	
-	Các chức năng của chương trình:
  
    a.	Cập nhật thông tin vật tư (thêm, xóa, sửa thông tin dựa vào mã).
  
    b.	Xuất danh sách vật tư.
  
    c.	Nhập thông tin nhân viên
  
    d.	Nhập hóa đơn và chi tiết hóa đơn: nhập vào số hóa đơn, ngày lập, loại (chỉ nhận ký tự I hoặc O). Sau đó, tiếp tục cho phép nhập các vật tư của hóa đơn đó; Căn cứ vào loại hóa           đơn, chương trình sẽ tự động cập nhật số lượng tồn. Nếu số lượng xuất không đủ hàng thì báo lỗi.
  
    e.	In danh sách nhân viên theo thứ tự tên nhân viên tăng dần, nếu trùng tên thì tăng dần theo họ ra màn hình, 1 nhân viên / dòng.
  
    f.	Xuất thông tin hóa đơn và chi tiết hóa đơn.

# 🎯 Dự án: Vẽ Đường Cong B-Spline Không Đồng Nhất Bậc 3

## 📝 Mô tả
Chương trình đồ họa tương tác vẽ **đường cong B-Spline không đồng nhất bậc 3 trong không gian 3D** sử dụng **OpenGL và C++**. Người dùng có thể:
- Thêm/xóa điểm điều khiển bằng chuột.
- Điều chỉnh góc nhìn 3D.
- Lưu toàn bộ dữ liệu vào file văn bản.

---

## ✅ Tính năng chính
- ✔️ **Thêm/xóa điểm điều khiển** bằng chuột trái.
- ✔️ **Hiển thị khung điều khiển** (đa giác điều khiển) và **đường cong B-Spline** theo thời gian thực.
- ✔️ **Điều khiển camera linh hoạt**:
  - Chuột phải + rê chuột: Xoay khung nhìn (Orbit).
  - Bánh xe chuột giữa: Phóng to/thu nhỏ (Zoom).
  - Phím mũi tên: Di chuyển khung nhìn (Pan).
- ✔️ **Tự động tạo vector nút clamped** để đảm bảo đường cong đi qua điểm đầu và cuối.
- ✔️ **Lưu dữ liệu ra `file.txt`** gồm: điểm điều khiển, vector nút và điểm trên đường cong.
- ✔️ **Hiển thị HUD**: thông tin hướng dẫn và tọa độ điểm điều khiển.

---

## 🔧 Yêu cầu hệ thống
- Hệ điều hành: Windows (khuyến nghị), Linux hoặc macOS
- Trình biên dịch: Microsoft Visual Studio 2019/2022 hoặc IDE hỗ trợ C++
- Thư viện đồ họa:
  - OpenGL
  - GLUT / FreeGLUT (cài qua NuGet)

---

## 💻 Hướng dẫn cài đặt và chạy

### Bước 1: Cài đặt freeglut
- Mở Visual Studio
- Vào: `Tools → NuGet Package Manager → Manage NuGet Packages for Solution...`
- Tìm: `freeglut`
- Cài đặt gói do **GDC** phát triển vào project của bạn

### Bước 2: Thêm các file mã nguồn vào project
Thêm thư mục `Bspline3D/` và toàn bộ các file sau:
Bspline3D/
├── main.cpp
├── point3d.h
├── config.h
├── camera.h
├── camera.cpp
├── bspline.h
├── bspline.cpp
├── interaction.h
├── interaction.cpp
├── draw_utils.h
├── draw_utils.cpp

### Bước 3: Cấu hình project
- **Include path**: Đảm bảo các file `.h` có thể được include trong project.
- **Link thư viện**:
  - Vào: `Project Properties → Linker → Input → Additional Dependencies`
  - Thêm:
    ```
    opengl32.lib
    glu32.lib
    glut32.lib
    ```

### Bước 4: Biên dịch & chạy
- Nhấn `Ctrl + Shift + B` để build
- Nhấn `Ctrl + F5` để chạy chương trình

---

## 🕹️ Hướng dẫn sử dụng

| Phím / Chuột        | Chức năng                            |
|---------------------|---------------------------------------|
| Chuột trái          | Thêm hoặc xóa điểm điều khiển         |
| Chuột phải + rê     | Xoay khung nhìn (Orbit)               |
| Bánh xe chuột giữa  | Phóng to / thu nhỏ (Zoom)             |
| Phím mũi tên        | Di chuyển khung nhìn (Pan)            |
| `r`                 | Đặt lại vị trí camera                 |
| `c`                 | Xóa tất cả điểm điều khiển            |
| `s`                 | Lưu dữ liệu ra file `file.txt`        |

---

## 📄 Cấu trúc file `file.txt`
Sau khi nhấn `s`, chương trình sẽ tạo file `file.txt` gồm:
1. Danh sách điểm điều khiển (x, y, z)
2. Vector nút (knot vector)
3. Tập các điểm trên đường cong (khoảng 100 đoạn)
> Có thể mở bằng Notepad, Excel hoặc công cụ phân tích dữ liệu.

---

## 📁 Cấu trúc thư mục

Bspline3D/
├── main.cpp // Hàm chính và xử lý sự kiện
├── point3d.h // Kiểu dữ liệu Point3D
├── config.h // Hằng số cấu hình
├── camera.h & camera.cpp // Camera 3D
├── bspline.h & bspline.cpp // Tính toán đường cong B-Spline
├── interaction.h & .cpp // Xử lý tương tác chuột và tìm điểm
├── draw_utils.h & .cpp // Vẽ HUD và đối tượng đồ họa

---

## 📌 Công nghệ sử dụng
- Ngôn ngữ: **C++**
- Thư viện đồ họa: **OpenGL**
- Quản lý sự kiện & cửa sổ: **freeGLUT**
- IDE: **Visual Studio**

---

## 🛠️ Gợi ý cải tiến
- Cho phép chỉnh sửa tọa độ z (z ≠ 0)
- Tích hợp GUI nâng cao (ImGui)
- Kéo thả điểm điều khiển bằng chuột
- Hỗ trợ bề mặt B-Spline hoặc NURBS
- Tối ưu thuật toán De Boor cho dữ liệu lớn

---

## 🙋‍♂️ Tác giả
- **Sinh viên thực hiện:** Trương Lê Gia Ân
- **Lớp:** 23T_DT3
- **Giáo viên hướng dẫn:** nguyễn Tấn Khôi
- **Năm học:** 2024-2025

---

> Cảm ơn bạn đã sử dụng và ủng hộ dự án! ⭐

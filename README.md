🎯 Dự án: Vẽ Đường Cong B-Spline Không Đồng Nhất Bậc 3
Mô tả: Chương trình đồ họa tương tác vẽ đường cong B-Spline không đồng nhất bậc 3 trong không gian ba chiều bằng thư viện OpenGL và C++ . Người dùng có thể thêm/xóa điểm điều khiển, điều chỉnh góc nhìn 3D và lưu dữ liệu ra file văn bản. 

✅ Tính năng chính
Thêm/xóa điểm điều khiển bằng chuột trái.
Hiển thị khung điều khiển (đa giác điều khiển) và đường cong B-Spline theo thời gian thực.
Điều khiển camera linh hoạt:
Chuột phải + rê chuột : Xoay khung nhìn (Orbit).
Bánh xe chuột giữa : Phóng to/thu nhỏ (Zoom).
Phím mũi tên : Di chuyển khung nhìn (Pan).
Tự động tạo vector nút clamped để đảm bảo đường cong đi qua điểm đầu và cuối.
Lưu toàn bộ dữ liệu (điểm điều khiển, vector nút, các điểm trên đường cong) vào file file.txt.
Giao diện phụ trợ (HUD) hiển thị thông tin hướng dẫn và tọa độ điểm điều khiển.
🔧 Yêu cầu hệ thống
Hệ điều hành: Windows (khuyến nghị), Linux hoặc macOS
Trình biên dịch: Microsoft Visual Studio (2019/2022) hoặc bất kỳ IDE hỗ trợ C++ nào
Thư viện đồ họa:
OpenGL
GLUT / FreeGLUT – được cài đặt qua NuGet Package Manager
💻 Hướng dẫn biên dịch và chạy chương trình trên Visual Studio
Bước 1: Cài đặt freeglut thông qua NuGet
Mở Visual Studio .
Vào Tools → NuGet Package Manager → Manage NuGet Packages for Solution...
Tìm kiếm freeglut .
Chọn gói freeglut do GDC phát triển và cài đặt vào project của bạn.
Bước 2: Thêm file nguồn vào project
Thêm tất cả các file sau vào project của bạn:
Bspline3D/
├── main.cpp                  # File chính chứa hàm main và callback sự kiện
├── point3d.h                 # Định nghĩa kiểu Point3D
├── config.h                  # Hằng số cấu hình chung
├── camera.h & camera.cpp     # Quản lý trạng thái và vị trí camera
├── bspline.h & bspline.cpp  # Tính toán đường cong B-Spline
├── interaction.h & interaction.cpp # Xử lý sự kiện chuột và tìm điểm gần nhất
├── draw_utils.h & draw_utils.cpp # Vẽ đối tượng đồ họa và hiển thị HUD
Bước 3: Thiết lập include path và liên kết thư viện
Include Path:
Đảm bảo các file .h nằm trong thư mục include hoặc cùng cấp với main.cpp.
Linker Libraries:
Trong Project Properties → Linker → Input , thêm:
opengl32.lib
glu32.lib
glut32.lib
Tùy chọn khác:
Đảm bảo bạn đang sử dụng chuẩn C++11 trở lên.
Bước 4: Biên dịch và chạy chương trình
Nhấn Ctrl + Shift + B để biên dịch.
Nhấn Ctrl + F5 để chạy chương trình mà không debug.
🕹️ Hướng dẫn sử dụng
Chuột trái
Thêm điểm mới hoặc xóa điểm hiện tại gần đó
Chuột phải + rê chuột
Xoay khung nhìn (Orbit)
Bánh xe chuột giữa
Phóng to/thu nhỏ khung nhìn (Zoom)
Phím mũi tên
Di chuyển khung nhìn (Pan)
'r'
Đặt lại vị trí camera về mặc định
'c'
Xóa toàn bộ điểm điều khiển
's'
Lưu dữ liệu ra file
file.txt

📁 Cấu trúc thư mục
Bspline3D/
├── main.cpp                  // Hàm chính và callback sự kiện từ chuột/bàn phím
├── point3d.h                 // Định nghĩa kiểu dữ liệu Point3D
├── config.h                  // Hằng số như PI, bán kính điểm, kích thước trục,...
├── camera.h & camera.cpp     // Module quản lý camera và điều khiển góc nhìn
├── bspline.h & bspline.cpp  // Tính toán đường cong B-Spline và vector nút
├── interaction.h & interaction.cpp // Xử lý tương tác người dùng và tìm điểm gần nhất
├── draw_utils.h & draw_utils.cpp // Vẽ đối tượng đồ họa và hiển thị HUD
📄 Nội dung file file.txt khi lưu
Khi nhấn phím 's' , chương trình sẽ lưu ra file file.txt với nội dung gồm:

Danh sách các điểm điều khiển (x, y, z).
Vector nút (knot vector) được sinh tự động.
Tập hợp các điểm trên đường cong B-Spline (khoảng 100 đoạn).
File có thể mở bằng Notepad, Excel hoặc công cụ phân tích dữ liệu.

📌 Công nghệ sử dụng
Ngôn ngữ lập trình: C++
Thư viện đồ họa: OpenGL
Quản lý cửa sổ và sự kiện: freeGLUT
IDE đề xuất: Visual Studio (Windows)
🛠️ Gợi ý cải tiến
Hỗ trợ nhập điểm điều khiển trong không gian 3D hoàn chỉnh (z ≠ 0).
Tích hợp GUI nâng cao (ví dụ: ImGui).
Tối ưu thuật toán De Boor cho số lượng điểm lớn.
Cho phép kéo thả và di chuyển điểm điều khiển.
Mở rộng sang bề mặt B-Spline hoặc NURBS.
🙋‍♂️ Tác giả
Sinh viên thực hiện: [Tên bạn]
Lớp: [Tên lớp]
Giáo viên hướng dẫn: [Tên GVHD]
Năm học: [Năm học]

📬 Liên hệ
Nếu bạn có câu hỏi, cần hỗ trợ hoặc muốn báo lỗi, vui lòng liên hệ qua email:
📧 [Điền email của bạn]

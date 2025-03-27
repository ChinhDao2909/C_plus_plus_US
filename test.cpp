    void InputEmployeeData(string &employeeID,string &name, string &position, double &salary,int &workingHours)
    {
        int maNhanVienSo;
        string chucVuNhap;
        // Nhập mã nhân viên
        while (true) {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            cin >> maNhanVienSo;
            if (cin.fail())  // Trả về giá trị true nếu lần nhập trước thất bại
            {
                cin.clear(); // Xoá cờ lỗi
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu lỗi
                cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if ((maNhanVienSo) >= 1 && (maNhanVienSo) <= 999) {
                    if (CheckDuplicateID(maNhanVienSo))
                    {
                        cout << "Ma nhan vien da ton tai. Vui long nhap lai." << endl;
                    }
                    else
                        break;
                }
                else {
                    cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
                }
            }
            
        }

        // Nhập họ tên
        cout << "Nhap ho ten (toi da 35 ky tu): ";
        cin.ignore();
        getline(cin, name);
        while (name.length() > 35) {
            cout << "Ho ten qua dai. Vui long nhap lai: ";
            getline(cin, name);
        }

        // Nhập chức vụ
        while (true) {
            cout << "Nhap chuc vu (NV hoac QL): ";
            cin >> chucVuNhap;
            if (chucVuNhap == "NV" || chucVuNhap == "QL") {
                break;
            }
            else {
                cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập lương
        while (true) {
            cout << "Nhap luong (toi da 20,000,000 va khong am): ";
            cin >> salary;
            if (salary >= 0 && salary <= 20000000) {
                break;
            }
            else {
                cout << "Luong khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập số giờ làm
        while (true) {
            cout << "Nhap so gio lam (toi da 12): ";
            cin >> workingHours;
            if (workingHours >= 0 && workingHours <= 12) {
                break;
            }
            else {
                cout << "So gio lam khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << maNhanVienSo;
        string maNhanVienFormatted = ss.str();

        // Thêm tiền tố vào mã nhân viên dựa trên chức vụ
        if (chucVuNhap == "NV") {
            employeeID = "NV" + maNhanVienFormatted;
            position = "Nhan vien";
        }
        else {
            employeeID = "QL" + maNhanVienFormatted;
            position = "Quan ly";
        }
    }

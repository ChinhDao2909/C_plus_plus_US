#pragma once
#include "NhanVien.h"
#include "NhaCungCap.h"


// Thay đổi kích thước màn hình console
static void resizeConsole(int width, int height) //Với width là chiều rộng, heigth là chiều cao
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
// Kiểm tra giá trị chọn
static bool checkInputChoice(string& chon)
{
    // Kiểm tra có trống không
    if (chon.empty())
    {
        return true;
    }
    // Xóa khoảng trắng
    chon.erase(remove_if(chon.begin(), chon.end(), ::isspace), chon.end());

    // Kiểm tra xem có chữ cái nào không
    for (char c : chon) {
        if (isalpha(c)) {
            return true; // Tìm thấy chữ cái
        }
    }
    return false;
}
// Menu danh cho chức vụ quản lý
static void menu_QL_NhanVien(EmployeeManager &em)
{
    bool run = true;
    em.ReadFromFile();
    while (run)
    {
        string chon;
        system("cls");
        cout << "============ Quan ly nhan vien ============\n"
            << "1. Them nhan vien\n"
            << "2. Cap nhat thong tin nhan vien\n"
            << "3. Hien thi danh sach nhan vien\n"
            << "4. Tim nhan vien theo ID\n"
            << "5. Xoa nhan vien theo ID\n"
            << "6. Tim nhan vien theo word\n"
            << "7. Chua co\n"
            << "8. Thoat\n";
        cout << "Nhap lua chon: ";
        getline(cin, chon);
        if (checkInputChoice(chon))  // Trả về giá trị true nếu lần nhập trước thất bại
        {
            cout << "Lua chon khong hop le. Vui long nhap lai!\n";
            cout << "\nAN Enter de quay lai man hinh chon....";
            cin.get();
        }
        else
        {
            int state = stoi(chon);
            switch (state)
            {
            case 1:
                em.AddEmployee();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 2:
                em.EditEmployee();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 3:
                em.displayOptions();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 4:
                em.SreachEmployeeByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 5:
                em.RemoveEmployeeByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 6:
                em.SreachEmployeeByWord();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 7:
                //ql.XoaNhanVien();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 8:
                cout << "Thoat chuong trinh\n";
                run = false;
                em.WriteToFile();
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            }
        }
    }
}
static void menu_QL_NhaCungCap(SupplierManager &sm)
{
    bool run = true;
    sm.ReadFromFile();
    while (run)
    {
        string chon;
        system("cls");
        cout << "============ Quan ly nha cung cap ============\n"
            << "1. Them nha cung cap\n"
            << "2. Cap nhat thong tin nha cung cap\n"
            << "3. Hien thi danh sach nha cung cap\n"
            << "4. Tim nha cung cap theo ID\n"
            << "5. Xoa nha cung cap theo ID\n"
            << "6. Chua co\n"
            << "7. Chua co\n"
            << "8. Thoat\n";
        cout << "Nhap lua chon: ";
        getline(cin, chon);
        if (checkInputChoice(chon))  // Trả về giá trị true nếu lần nhập trước thất bại
        {
            cout << "Lua chon khong hop le. Vui long nhap lai!\n";
            cout << "\nAN Enter de quay lai man hinh chon....";
            cin.get();
        }
        else
        {
            int state = stoi(chon);
            switch (state)
            {
            case 1:
                sm.AddSupplier();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 2:
                sm.EditSupplier();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 3:
                sm.DisplayInfoAll();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 4:
                sm.SreachSupplierByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 5:
                sm.RemoveSupplierByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 6:
                //sm.TimNhanVienTheoMa();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 7:
                //sm.XoaNhanVien();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 8:
                cout << "Thoat chuong trinh\n";
                run = false;
                sm.WriteToFile();
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            }
        }
    }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>
#include <regex>
#include <Windows.h>

using namespace std;

class Supplier {
private:
	string supplierID;  // Mã nhà cung cấp
	string name;		// Tên nhà cung cấp
    string phoneNumber; // Số điện thoại
    string address;     // Địa chỉ
    string email;       // Email
	vector<string> productList; // Danh sách sản phẩm cung cấp

public:
    // Constructor
    //Supplier(string id="", string ten="", string phone="", string addr="", string mail="", vector<string> products)
    //    : supplierID(id), name(ten), phoneNumber(phone), address(addr), email(mail), productList(products) {
    //}

    Supplier(string id="", string ten="", string phone="", string addr="", string mail="")
        : supplierID(id), name(ten), phoneNumber(phone), address(addr), email(mail) {
    }

    // Getter
    string getSupplierID() const { return supplierID; }
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getAddress() const { return address; }
    string getEmail() const { return email; }
    vector<string> getProductList() const { return productList; }

    // Setter
    void setSupplierID(string id) 
    { 
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << id;
        string ID_Formatted = ss.str();
        supplierID = ID_Formatted;
    }
    void setName(string ten) { name = ten; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    void setAddress(string addr) { address = addr; }
    void setEmail(string mail) { email = mail; }
    void setProductList(vector<string> products) { productList = products; }

	// Phương thức hiện tiêu đề (static)
	static void displayHeader() {
		cout << left
			<< setw(8) << "Ma NCC"
			<< setw(40) << "Ten NCC"
			<< setw(15) << "So dien thoai"
			<< setw(40) << "Dia chi"
			<< setw(25) << "Email"
			<< endl;
		cout << setfill('-');
		cout << setw(7) << "" << " "
			<< setw(39) << "" << " "
			<< setw(14) << "" << " "
			<< setw(39) << "" << " "
			<< setw(24) << "" << endl;
		cout << setfill(' '); // Reset fill character
	}
	// Phương thức hiển thị hàng dữ liệu
	void displayRow() const {
		cout << left
			<< setw(8) << supplierID
			<< setw(40) << name
			<< setw(15) << phoneNumber
			<< setw(40) << address
			<< setw(25) << email
			<< endl;
	}

    // Phương thức kiểm tra thông tin nhập vào
    bool checkInputID(string ID)
    {
        if (ID.empty()) // Kiểm tra xem có bỏ trống không
        {
            cout << "Ma nha cung cap khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        for (char c : ID) // Kiểm tra xem có phải số không
        {
            if (isalpha(c))
            {
                cout << "Ma nha cung cap khong chua ky tu. Vui long nhap lai." << endl;
                return false;
            }
        }
        if (stoi(ID) >= 1 && stoi(ID) <= 999) // Kiểm tra xem có trong khoảng không
        {
            return true;
        }
        else
        {
            cout << "Ma nha cung cap chi tu (1 -> 999). Vui long nhap lai." << endl;
            return false;
        }
    }

    bool checkInputName(string name)
    {
        if (name.empty()) // Kiểm tra xem có bỏ trống không
        {
            cout << "Ten khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        if (name.length() > 40)
        {
            cout << "Ten qua dai (>40). Vui long nhap lai." << endl;
            return false;
        }
        return true;
    }

    bool checkInputPhoneNum(string num) {
        if (num.empty())
        {
            cout << "So dien thoai khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        // Biểu thức chính quy: Bắt đầu bằng 0, theo sau là 9 chữ số
        regex regexSoDienThoai("^0\\d{9}$");
        if (!regex_match(num, regexSoDienThoai))
        {
            cout << "So dien thoai khong hop le. Vui long nhap lai. " << endl;
            return false;
        }
        else return true;
 
    }

    bool checkInputAddress(string address) {
        if (address.empty())
        {
            cout << "Dia chi khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        // Biểu thức chính quy kiểm tra định dạng địa chỉ cơ bản
        regex regexDiaChi(R"([a-zA-Z0-9\s,./-]+)");
        if (!regex_match(address, regexDiaChi))
        {
            cout << "Dia chi khong hop le. Vui long nhap lai. " << endl;
            return false;
        }
        else if (address.length() > 40)
        {
            cout << "Dia chi nhap qua dai (>40). Vui long nhap lai.";
            return false;
        }
        else return true;
    }

    bool checkInputEmail(string email) {
        if (email.empty())
        {
            cout << "Email khong duoc de trong. Vui long nhap lai." << endl;
            return false;
        }
        // Biểu thức chính quy kiểm tra định dạng email cơ bản
        regex regexEmail(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        if (!regex_match(email, regexEmail))
        {
            cout << "Email nhap khong hop le. Vui long nhap lai. " << endl;
            return false;
        }
        else if (email.length() > 25)
        {
            cout << "Email nhap qua dai (>25). Vui long nhap lai. " << endl;
            return false;
        }
        else return true;
    }
};

class SupplierManager {
private:
	vector<Supplier> ds_ncc; // Danh sách nhà cung cấp
public:
    // Lấy dữ liệu trong file
    void ReadFromFile() {
        string filename = "Suppliers.csv";
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        bool isFirstLine = true; // Thêm biến boolean để kiểm tra dòng đầu tiên

        string line;
        while (getline(file, line)) {
            if (isFirstLine) {
                isFirstLine = false;
                continue; // Bỏ qua dòng đầu tiên
            }
            stringstream ss(line);
            string id, name, phoneNum, address, email;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, phoneNum, ',');
            getline(ss, address, ',');
            getline(ss, email);

            try {
                ds_ncc.emplace_back(id, name, phoneNum, address, email);
            }
            catch (const exception& e) {
                cerr << "Error parsing data: " << e.what() << endl;
            }
        }

        SortByID();

        file.close();
    }

    // Ghi dữ liệu vào file
    void WriteToFile() {
        string filename = "Suppliers.csv";
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        SortByID();
        file << "Ma NCC,Ten,So dien thoai, Dia chi ,email\n";

        for (const auto& supplier : ds_ncc) {
            file << supplier.getSupplierID() << ","
                << supplier.getName() << ","
                << supplier.getPhoneNumber() << ","
                << supplier.getAddress() << ","
                << supplier.getEmail() << "\n";
        }
        file.close();
    }

    // Sắp xếp danh sách theo ID
    void SortByID()
    {
        if (ds_ncc.size() > 1)
        {
            sort(ds_ncc.begin(), ds_ncc.end(), [](const Supplier& supplier1, const Supplier& supplier2)
                {
                    return stoi(supplier1.getSupplierID()) < stoi(supplier2.getSupplierID());
                });
        }
    }

    // Hiển thị danh sách
	void DisplayInfoAll() {
		Supplier::displayHeader();
		for (const auto& supplier : ds_ncc) {
			supplier.displayRow();
		}
	}

    // Kiểm tra trùng ID
    bool checkDuplicateID(const int ID)
    {
        for (const auto& supp : ds_ncc)
        {
            if (stoi(supp.getSupplierID()) == ID)
            {
                cout << "Ma nha cung cap da ton tai. Vui long nhap lai." << endl;
                return true;
            }
        }
        return false;
    }

    // Tìm vị trí của nhà cung cấp
    int SreachIndexSupplierByID(const string ID_so)
    {
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << ID_so;
        string ID_Formatted = ss.str();
        for (int i = 0; i < ds_ncc.size(); i++)
        {
            if (ds_ncc[i].getSupplierID() == ID_Formatted)
                return i;
        }
        return -1;
    }

    // Chức năng thêm nhà cung cấp
    void AddSupplier() {
        string supplierID, name, phone, address, email;
        Supplier supp;

        // Nhập ID nhà cung cấp
        bool check = false;
        while (!check)
        {
            cout << "Nhap ma nhà cung cap (toi da 3 so): ";
            getline(cin, supplierID);
            check = supp.checkInputID(supplierID) and !checkDuplicateID(stoi(supplierID));
        }


        // Nhập tên nhà cung cấp
        check = false;
        while (!check)
        {
            cout << "Nhap ten nha cung cap (toi da 20 ky tu): ";
            getline(cin, name);
            check = supp.checkInputName(name);
        }

        // Nhập số điện thoại
        check = false;
        while (!check)
        {
            cout << "Nhap so dien thoai (10 so) ";
            getline(cin, phone);
            check = supp.checkInputPhoneNum(phone);
        }


        // Nhập địa chỉ
        check = false;
        while (!check)
        {
            cout << "Nhap dia chi: ";
            getline(cin, address);
            check = supp.checkInputAddress(address);
        }

        // Nhập số giờ làm
        check = false;
        while (!check)
        {
            cout << "Nhap email nha cung cap (thongtin@tencongty): ";
            getline(cin, email);
            check = supp.checkInputEmail(email);
        }

        supp.setSupplierID(supplierID);
        supp.setName(name);
        supp.setPhoneNumber(phone);
        supp.setAddress(address);
        supp.setEmail(email);

        ds_ncc.emplace_back(supp);

        WriteToFile();
    }

    // Chức năng cập nhật thông tin nhà cung cấp
    void EidtSupplier() {
        string ID_sreach;
        cout << "Nhap ma nha cung cap can sua:";
        getline(cin, ID_sreach);

        // Tìm nhà cung cấp trong danh sách
        int viTri = SreachIndexSupplierByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nha cung cap co ma " << ID_sreach << endl;
            return;
        }

        // Hiển thị thông tin hiện tại
        cout << "Thong tin nha cung cap hien tai:" << endl;
        Supplier::displayHeader();
        ds_ncc[viTri].displayRow();
        cout << endl;

        // Cho phép sửa thông tin
        cout << "Nhap thong tin moi (nhan Enter de giu nguyen)" << endl;
        //Sửa thông tin
        string supplierID, name, phone, address, email;
        Supplier supp;

        // Nhập ID nhà cung cấp mới
        bool check = false;
        while (!check)
        {
            cout << "Nhap ma nhà cung cap (toi da 3 so): ";
            getline(cin, supplierID);
            if (!supplierID.empty())
            {
                check = supp.checkInputID(supplierID) and !checkDuplicateID(stoi(supplierID));
                if (check)
                {
                    ds_ncc[viTri].setSupplierID(supplierID);
                }
            }
            else break;
        }

        // Nhập tên nhà cung cấp mới
        check = false;
        while (!check)
        {
            cout << "Nhap ten nha cung cap (toi da 20 ky tu): ";
            getline(cin, name);
            if (!name.empty())
            {
                check = supp.checkInputName(name);
                if (check)
                {
                    ds_ncc[viTri].setName(name);
                }
            }
            else break;
        }

        // Nhập số điện thoại mới
        check = false;
        while (!check)
        {
            cout << "Nhap so dien thoai (10 so) ";
            getline(cin, phone);
            if (!phone.empty())
            {
                check = supp.checkInputPhoneNum(phone);
                if (check)
                {
                    ds_ncc[viTri].setPhoneNumber(phone);
                }
            }
            else break;
        }

        // Nhập địa chỉ mới
        check = false;
        while (!check)
        {
            cout << "Nhap dia chi: ";
            getline(cin, address);
            if (!address.empty())
            {
                check = supp.checkInputAddress(address);
                if (check)
                {
                    ds_ncc[viTri].setAddress(address);
                }
            }
            else break;
        }

        // Nhập số email mới
        check = false;
        while (!check)
        {
            cout << "Nhap email nha cung cap (thongtin@tencongty): ";
            getline(cin, email);
            if (!email.empty())
            {
                check = supp.checkInputEmail(email);
                if (check)
                {
                    ds_ncc[viTri].setEmail(email);
                }
            }
            else break;
        }

        cout << "Sua thong tin nha cung cap thanh cong. " << endl;
        WriteToFile();
    }

    // Chức năng tìm kiếm thông tin nhà cung cấp bằng ID
    void SreachSupplierByID()
    {
        string ID_sreach;
        cout << "Nhap ma nha cung cap can tim (nhap so) : ";
        cin >> ID_sreach;
        cin.ignore();
        // Tìm kiếm nhân viên trong danh sách
        int viTri = SreachIndexSupplierByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nha cung cap co ma " << ID_sreach << endl;
            return;
        }
        // Hiển thị thông tin hiện tại
        cout << "Thong tin nha cung cap can tim la:" << endl;
        Supplier::displayHeader();
        ds_ncc[viTri].displayRow();
    }

    // Chức năng xóa thông tin nhà cung cấp bằng ID
    void RemoveSupplierByID() 
    {
        string ID_sreach;
        cout << "Nhap ma nha cung cap can xoa (nhap so): ";
        cin >> ID_sreach;
        cin.ignore();
        // Tìm kiếm nhân viên trong danh sách
        int viTri = SreachIndexSupplierByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nha cung cap co ma " << ID_sreach << endl;
            return;
        }
        else {
            // Xóa nhân viên khỏi cả hai danh sách
            cout << "Xoa thanh cong nha cung cap :" << endl;
            Supplier::displayHeader();
            ds_ncc[viTri].displayRow();
            cout << endl;
            ds_ncc.erase(ds_ncc.begin() + viTri);
            WriteToFile();
        }
    }
};

// Thay đổi kích thước màn hình console
static void resizeConsole(int width, int height) //Với width là chiều rộng, heigth là chiều cao
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

bool checkInputChoice(string& chon)
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

// Menu chọn
static void menu_QL_NhaCungCap()
{
    SupplierManager sm;
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
                sm.EidtSupplier();
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

int main()
{
    resizeConsole(1280, 720);
    menu_QL_NhaCungCap();
    return 0;
}
